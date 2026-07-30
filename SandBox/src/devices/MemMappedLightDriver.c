#include "MemMappedLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

typedef struct MemMappedLightDriverStruct * MemMappedLightDriver;
typedef struct MemMappedLightDriverStruct
{
    LightDriverStruct base;
    uint32_t * address;
} MemMappedLightDriverStruct;

LightDriver MemMappedLightDriver_Create(int id, uint32_t * address)
{
     MemMappedLightDriver self = calloc(1, sizeof(MemMappedLightDriverStruct));
     self->base.type = MemoryMapped;
     self->base.id = id;
     self->address = address;
     return (LightDriver)self;
}

void MemMappedLightDriver_Destroy(LightDriver super)
{
    free(super);
}

void MemMappedLightDriver_TurnOn(LightDriver super)
{
    explodesInTestEnvironment(super);
}

void MemMappedLightDriver_TurnOff(LightDriver super)
{
    explodesInTestEnvironment(super);
}

