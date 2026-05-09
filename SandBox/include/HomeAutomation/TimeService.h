#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct time
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

typedef void (*WakeUpCallback)(void);

void TimeService_Create();
void TimeService_Destroy();
void TimeService_GetTime(Time *time);
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb);

#endif /* D_TimeService_H */