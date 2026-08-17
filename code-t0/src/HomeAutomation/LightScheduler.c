/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
 ***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "RandomMinute.h"
#include <stdlib.h>
#include <string.h>

enum
{
    TURN_ON,
    TURN_OFF,
    DIM,
    RANDOM_ON,
    RANDOM_OFF
};

enum
{
    MAX_EVENTS = 128,
    UNUSED = -1
};

typedef struct
{
    int id;
    Day day;
    int minuteOfDay;
    int event;
    int randomize;
    int randomMinutes;

} ScheduledLightEvent;

static ScheduledLightEvent eventList[MAX_EVENTS];

static int AddEvent(int id, Day day, int minuteOfDay, int kind)
{
    int i;

    if (id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minuteOfDay = minuteOfDay;
            eventList[i].event = kind;
            eventList[i].randomize = RANDOM_OFF;
            eventList[i].randomMinutes = 0;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

static ScheduledLightEvent *GetEvent(int id, Day day, int minuteOfDay)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent *event = &eventList[i];
        if (event->id == id && event->day == day &&
            event->minuteOfDay == minuteOfDay)
        {
            return event;
        }
    }

    return NULL;
}

static int NeedsUpdate(ScheduledLightEvent *event, Time time)
{
    int min;
    Day day;

    min = TimeService_GetMinute(time);
    day = event->day;

    if (min != event->minuteOfDay + event->randomMinutes)
        return 0;

    if (TimeService_MatchesDayOfWeek(time, day))
        return 1;

    return 0;
}

static void UpdateEvent(ScheduledLightEvent *event, Time time)
{
    if (NeedsUpdate(event, time))
    {
        if (TURN_ON == event->event)
            LightController_TurnOn(event->id);
        else if (TURN_OFF == event->event)
            LightController_TurnOff(event->id);

        if (event->randomize == RANDOM_ON)
            event->randomMinutes = RandomMinute_Get();
        else
            event->randomMinutes = 0;
    }
    return;
}

void LightScheduler_Create(void)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        eventList[i].id = UNUSED;
    }
}

void LightScheduler_Destroy(void)
{
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    return AddEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    return AddEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_Randomize(int id, Day day, int minuteOfDay)
{
    ScheduledLightEvent *event = GetEvent(id, day, minuteOfDay);

    if (event != NULL)
    {
        event->randomize = RANDOM_ON;
        event->randomMinutes = RandomMinute_Get();
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    ScheduledLightEvent *event = GetEvent(id, day, minuteOfDay);

    if (event != NULL)
        event->id = UNUSED;
}

void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    time = TimeService_GetTime();

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent *scheduled_event = &eventList[i];

        if (scheduled_event->id == UNUSED)
            continue;

        UpdateEvent(scheduled_event, time);
    }

    TimeService_FreeTime(time);
}
