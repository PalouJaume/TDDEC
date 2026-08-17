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

#include "FakeTimeService.h"

#include "stdlib.h"

static int theMinute;
static int theDay;

struct Time
{
    int usec;
    int sec;
    int minuteOfDay;
    int minuteOfHour;
    Day dayOfWeek;
    int dayOfMonth;
    Month month;
};

void TimeService_Create(void)
{
    theMinute = MINUTE_UNKNOWN;
    theDay = DAY_UNKNOWN;
}

void TimeService_Destroy(void)
{
}

Time TimeService_GetTime(void)
{
    Time time = calloc(1, sizeof(struct Time));

    time->dayOfWeek = theDay;
    time->minuteOfDay = theMinute;

    return time;
}

void TimeService_FreeTime(Time time)
{
    if (time != NULL)
        free(time);
}

int TimeService_GetMinute(Time time)
{
    return time->minuteOfDay;
}

int TimeService_GetDay(Time time)
{
    return time->dayOfWeek;
}

BOOL TimeService_MatchesDayOfWeek(const Time time, Day day)
{
    Day today = time->dayOfWeek;

    if (day == EVERYDAY)
        return 1;

    if (day == today)
        return 1;

    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return 1;

    if (day == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return 1;

    return 0;
}

void FakeTimeService_SetMinute(int minute)
{
    theMinute = minute;
}

void FakeTimeService_SetDay(int day)
{
    theDay = day;
}
