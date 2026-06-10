#include "FakeRandomMinute.h"

static int fakeValue;
static int fakeInc;

int FakeRandomMinute_Get(void)
{
    int res = fakeValue;
    fakeValue += fakeInc;

    return res;
}

void FakeRandomMinute_SetFirstAndIncrement(int first, int inc)
{
    fakeValue = first;
    fakeInc = inc;
}