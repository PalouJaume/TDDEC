#ifndef D_X10LightDriver_H
#define D_X10LightDriver_H

#include "LightDriver.h"

typedef enum X10_HouseCode
{
    X10_A,X10_B,X10_C,X10_D,X10_E,X10_F,
    X10_G,X10_H,X10_I,X10_J,X10_K,X10_L,
    X10_M,X10_N,X10_O,X10_P
} X10_HouseCode;

LightDriver X10LightDriver_Create(int id, X10_HouseCode code, int unit);

#endif /* D_X10LightDriver_H */