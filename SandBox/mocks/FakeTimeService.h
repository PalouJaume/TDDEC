#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum
{
    TIME_UNKNOWN = -1
};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(int day);
WakeUpCallback FakeTimeService_GetAlarmCallback();
int FakeTimeService_GetAlarmPeriod();

#endif /* D_FakeTimeService_H */