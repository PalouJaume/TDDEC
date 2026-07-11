#include "FakeMicroTime.h"

static uint32_t time;
static uint32_t increment;
static uint32_t totalDelay;

void FakeMicroTime_Init(uint32_t start, uint32_t incr)
{
    time = start;
    increment = incr;
    totalDelay = 0;
}

uint32_t MicroTime_Get(void)
{
    uint32_t t = time;
    time += increment;
    return t;
}