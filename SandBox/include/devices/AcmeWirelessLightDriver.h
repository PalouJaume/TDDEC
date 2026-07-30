#ifndef D_AcmeWirelessLightDriver_H
#define D_AcmeWirelessLightDriver_H

#include "LightDriver.h"

LightDriver AcmeWirelessLightDriver_Create(int lightId, const char * ssid, const char * key, int channel);
void AcmeWirelessLightDriver_Destroy(LightDriver);
void AcmeWirelessLightDriver_TurnOn(LightDriver);
void AcmeWirelessLightDriver_TurnOff(LightDriver);

#endif
