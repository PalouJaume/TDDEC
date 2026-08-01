#ifndef D_LightDriver_H
#define D_LightDriver_H

typedef struct LightDriverStruct *LightDriver;

typedef struct LightDriverInterfaceStruct *LightDriverInterface;

void LightDriver_Destroy(LightDriver);
void LightDriver_TurnOn(LightDriver);
void LightDriver_TurnOff(LightDriver);
const char *LightDriver_GetType(LightDriver);
int LightDriver_GetId(LightDriver);

#include "LightDriverPrivate.h"

#endif /* D_LightDriver_H */