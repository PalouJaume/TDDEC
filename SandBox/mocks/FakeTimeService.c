#include "stdlib.h"
#include "FakeTimeService.h"

static int minuteOfDay;
static int dayOfWeek;
static WakeUpCallback callback;
static int period;

void TimeService_Create()
{
    minuteOfDay = TIME_UNKNOWN;
    dayOfWeek = TIME_UNKNOWN;
}

void TimeService_Destroy()
{
}

void TimeService_GetTime(Time *time)
{
    time->minuteOfDay = minuteOfDay;
    time->dayOfWeek = dayOfWeek;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    if (cb == callback && period == seconds)
    {
        callback = NULL;
        period = 0;
    }
}

void FakeTimeService_SetMinute(int minute)
{
    minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
    dayOfWeek = day;
}

WakeUpCallback FakeTimeService_GetAlarmCallback()
{
    return callback;
}

int FakeTimeService_GetAlarmPeriod()
{
    return period;
}

