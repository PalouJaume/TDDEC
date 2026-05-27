#ifndef D_FAKECLOCKSERVICE_H
#define D_FAKECLOCKSERVICE_H

#include "ClockService.h"

typedef enum FAKECLOCKSERVICE_STATE
{
    UNKNOWN_MS = -1,
} FAKECLOCKSERVICE_STATE;

void FakeClockService_Create(void);
void FakeClockService_Destroy(void);
void FakeClockService_Setms(int ms);

#endif /* D_FAKECLOCKSERVICE_H */