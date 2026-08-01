#include "CountingLightDriver.h"

#include <stdlib.h>

typedef struct CountingLightDriverStruct *CountingLightDriver;

typedef struct CountingLightDriverStruct
{
    LightDriverStruct base;
    int counter;
} CountingLightDriverStruct;

static void count(LightDriver base);
static void destroy(LightDriver base);

static LightDriverInterfaceStruct interface =
    {
        .TurnOn = count,
        .TurnOff = count,
        .Destroy = destroy
    };

static void count(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    self->counter++;
}

static void destroy(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    free(self);
}

LightDriver CountingLightDriver_Create(int id)
{
    CountingLightDriver self = calloc(1, sizeof(CountingLightDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "CountingLightDriver";
    self->base.id = id;
    return (LightDriver)self;
}

int CountingLightDriver_GetCallCount(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    return self->counter;
}

