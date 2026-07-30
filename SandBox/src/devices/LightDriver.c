#include "LightDriver.h"

#include "common.h"
#include <stdlib.h>

static LightDriverInterface interface = NULL;

static BOOL isValid(LightDriver self)
{
    return interface && self;
}

void LightDriver_SetInterface(LightDriverInterface i)
{
    interface = i;
}

void LightDriver_TurnOn(LightDriver self)
{
    if (isValid(self))
        interface->TurnOn(self);
}

void LightDriver_TurnOff(LightDriver self)
{
    if (isValid(self))
        interface->TurnOff(self);
}

void LightDriver_Destroy(LightDriver self)
{
    if (isValid(self))
        interface->Destroy(self);
}