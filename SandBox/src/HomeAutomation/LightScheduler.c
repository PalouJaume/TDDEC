#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include "RandomMinute.h"

typedef struct
{
    int id;
    int minuteOfDay;
    int day;
    EVENT_TYPE event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    if (id < 0 || id > 31)
        return 2;

    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            scheduledEvents[i].day = day;
            return 0;
        }
    }
    return 1;
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

static int DoesLightRespondToday(Time *time, int reactionDay)
{
    switch (reactionDay)
    {
    case WEEKEND:
        if (time->dayOfWeek != SATURDAY && time->dayOfWeek != SUNDAY)
            return 0;
        break;
    case EVERYDAY:
        break;
    case WEEKDAY:
        if (time->dayOfWeek < MONDAY && time->dayOfWeek > FRIDAY)
            return 0;
        break;
    default:
        if (reactionDay != time->dayOfWeek)
            return 0;
    }

    return 1;
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;

    if (!DoesLightRespondToday(time, lightEvent->day))
        return;

    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

void LightScheduler_Create(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
                                          LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

RES_STATUS LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    switch (scheduleEvent(id, day, minuteOfDay, TURN_ON))
    {
        case 1:
            return LS_TOO_MANY_EVENTS;
        case 2:
            return LS_ID_OUT_OF_BOUNDS;
        default:
            return LS_OK;
    }
}

RES_STATUS LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    switch (scheduleEvent(id, day, minuteOfDay, TURN_OFF))
    {
        case 1:
            return LS_TOO_MANY_EVENTS;
        case 2:
            return LS_ID_OUT_OF_BOUNDS;
        default:
            return LS_OK;
    }
}

void LightScheduler_RemoveSchedule(int id, Day day, int minuteOfDay)
{
    ScheduledLightEvent *cur;
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        cur = &scheduledEvents[i];
        if (cur->id != UNUSED)
        {
            if (cur->id == id &&
                cur->day == day &&
                cur->minuteOfDay == minuteOfDay)
            {
                cur->id = UNUSED;
            }
        }
    }
}

void LightScheduler_WakeUp(void)
{
    Time time;
    TimeService_GetTime(&time);

    for (int i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }
}

void LightScheduler_Randomize(int id, Day day, int minuteOfDay)
{
    ScheduledLightEvent *cur;
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        cur = &scheduledEvents[i];
        if (cur->id != UNUSED)
        {
            if (cur->id == id &&
                cur->day == day &&
                cur->minuteOfDay == minuteOfDay)
            {
                cur->minuteOfDay += RandomMinute_Get();
            }
        }
    }
}