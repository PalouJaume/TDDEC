#ifndef D_LightController_H
#define D_LightController_H

#include "common.h"
#include "LightDriver.h"

enum {MAX_LIGHTS = 32};
void LightController_Create();
void LightController_Destroy();
BOOL LightController_Add(int id, LightDriver);
void LightController_On(int id);
void LightController_Off(int id);

#endif /* D_LightController_H */