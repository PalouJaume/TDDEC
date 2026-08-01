#include "AcmeWirelessLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

typedef struct AcmeWirelessLightDriverStruct *AcmeWirelessLightDriver;
typedef struct AcmeWirelessLightDriverStruct
{
    LightDriverStruct base;
    const char *ssid;
    const char *key;
    int channel;
} AcmeWirelessLightDriverStruct;

static void AcmeWirelessLightDriver_Destroy(LightDriver super);
static void AcmeWirelessLightDriver_TurnOn(LightDriver super);
static void AcmeWirelessLightDriver_TurnOff(LightDriver super);

static LightDriverInterfaceStruct interface =
    {
        .TurnOn = AcmeWirelessLightDriver_TurnOn,
        .TurnOff = AcmeWirelessLightDriver_TurnOff,
        .Destroy = AcmeWirelessLightDriver_Destroy};

LightDriver
AcmeWirelessLightDriver_Create(int id, const char *ssid, const char *key, int channel)
{
    AcmeWirelessLightDriver self = calloc(1, sizeof(AcmeWirelessLightDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "AcmeWireless";
    self->base.id = id;
    self->ssid = ssid;
    self->key = key;
    self->channel = channel;
    return (LightDriver)self;
}

static void AcmeWirelessLightDriver_Destroy(LightDriver super)
{
    free(super);
}

static void AcmeWirelessLightDriver_TurnOn(LightDriver super)
{
    explodesInTestEnvironment(super);
}

static void AcmeWirelessLightDriver_TurnOff(LightDriver super)
{
    explodesInTestEnvironment(super);
}
