#ifndef D_ALARMCLOCK_H
#define D_ALARMCLOCK_H

#include "ClockService.h"

typedef void (*AlarmCallback)(void);

void AlarmClock_Create(void);
void AlarmClock_Destroy(void);
void AlarmClock_WakeUp(void);
void AlarmClock_SetAlarm(AlarmCallback, int ms);
void AlarmClock_RemoveAlarm(AlarmCallback, int ms);

#endif /* D_ALARMCLOCK_H */