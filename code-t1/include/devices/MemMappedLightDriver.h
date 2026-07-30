#ifndef D_MemMappedLightDriver_H
#define D_MemMappedLightDriver_H

#include "LightDriver.h"
#include <stdint.h>

LightDriver MemMappedLightDriver_Create(int lightId, uint32_t *address);
void MemMappedLightDriver_Destroy(LightDriver);
void MemMappedLightDriver_TurnOn(LightDriver);
void MemMappedLightDriver_TurnOff(LightDriver);

#endif /* D_MemMappedLightDriver_H */
