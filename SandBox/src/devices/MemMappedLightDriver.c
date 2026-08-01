#include "MemMappedLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

typedef struct MemMappedLightDriverStruct *MemMappedLightDriver;
typedef struct MemMappedLightDriverStruct
{
    LightDriverStruct base;
    uint32_t *address;
} MemMappedLightDriverStruct;

static void MemMappedLightDriver_Destroy(LightDriver super);
static void MemMappedLightDriver_TurnOn(LightDriver super);
static void MemMappedLightDriver_TurnOff(LightDriver super);

static LightDriverInterfaceStruct interface =
    {
        .TurnOn = MemMappedLightDriver_TurnOn,
        .TurnOff = MemMappedLightDriver_TurnOff,
        .Destroy = MemMappedLightDriver_Destroy};

LightDriver MemMappedLightDriver_Create(int id, uint32_t *address)
{
    MemMappedLightDriver self = calloc(1, sizeof(MemMappedLightDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "MemoryMapped";
    self->base.id = id;
    self->address = address;
    return (LightDriver)self;
}

static void MemMappedLightDriver_Destroy(LightDriver super)
{
    free(super);
}

static void MemMappedLightDriver_TurnOn(LightDriver super)
{
    explodesInTestEnvironment(super);
}

static void MemMappedLightDriver_TurnOff(LightDriver super)
{
    explodesInTestEnvironment(super);
}
