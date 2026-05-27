#include "FakeClockService.h"

static int fake_ms;

void FakeClockService_Create(void)
{
    fake_ms = UNKNOWN_MS;
}

void FakeClockService_Destroy(void)
{
}

void FakeClockService_Setms(int ms)
{
    fake_ms = ms;
}

int ClockService_Getms(void)
{
    return fake_ms;
}