#ifndef D_CountingLightDriver_H
#define D_CountingLightDriver_H

#include "LightDriver.h"

LightDriver CountingLightDriver_Create(int id);

/* Functions just needed by the spy */
int CountingLightDriver_GetCallCount(LightDriver base);

#endif /* D_CountingLightDriver_H */