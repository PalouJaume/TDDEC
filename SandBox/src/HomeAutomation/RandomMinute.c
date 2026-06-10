#include "RandomMinute.h"

#include "stdlib.h"

static int bound_priv = 0;

void RandomMinute_Create(int bound)
{
    bound_priv = bound;
}

int RandomMinute_GetImpl(void)
{
    return bound_priv - rand() % (bound_priv * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;