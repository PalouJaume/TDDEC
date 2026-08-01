#include "LightDriver.h"

#include "common.h"
#include <stdlib.h>

static BOOL isValid(LightDriver self)
{
    return self && self->vtable;
}

void LightDriver_TurnOn(LightDriver self)
{
    if (isValid(self))
        self->vtable->TurnOn(self);
}

void LightDriver_TurnOff(LightDriver self)
{
    if (isValid(self))
        self->vtable->TurnOff(self);
}

void LightDriver_Destroy(LightDriver self)
{
    if (isValid(self))
        self->vtable->Destroy(self);
}