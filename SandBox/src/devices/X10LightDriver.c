#include "X10LightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

#define MAX_X10_MESSAGE_LENGTH 100

typedef struct X10LightDriverStruct *X10LightDriver;

typedef struct X10LightDriverStruct
{
    LightDriverStruct base;
    X10_HouseCode house;
    int unit;
    char message[MAX_X10_MESSAGE_LENGTH];
} X10LightDriverStruct;

static void X10LightDriver_Destroy(LightDriver self);
static void X10LightDriver_TurnOn(LightDriver base);
static void X10LightDriver_TurnOff(LightDriver base);

static LightDriverInterfaceStruct interface =
    {
        .TurnOn = X10LightDriver_TurnOn,
        .TurnOff = X10LightDriver_TurnOff,
        .Destroy = X10LightDriver_Destroy};

LightDriver X10LightDriver_Create(int id, X10_HouseCode house, int unit)
{
    X10LightDriver self = calloc(1, sizeof(X10LightDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "X10";
    self->base.id = id;
    self->house = house;
    self->unit = unit;

    return (LightDriver)self;
}

static void X10LightDriver_Destroy(LightDriver self)
{
    free(self);
}

static void formatTurnOnMessage(X10LightDriver self)
{
    explodesInTestEnvironment(self);
}

static void formatTurnOffMessage(X10LightDriver self)
{
    explodesInTestEnvironment(self);
}

static void sendMessage(X10LightDriver self)
{
    explodesInTestEnvironment(self);
}

static void X10LightDriver_TurnOn(LightDriver base)
{
    X10LightDriver self = (X10LightDriver)base;
    formatTurnOnMessage(self);
    sendMessage(self);
}

static void X10LightDriver_TurnOff(LightDriver base)
{
    X10LightDriver self = (X10LightDriver)base;
    formatTurnOffMessage(self);
    sendMessage(self);
}