#ifndef D_RandomNumber_H
#define D_RandomNumber_H

typedef struct RandomNumberStruct *RandomNumber;

typedef struct RandomNumberInterfaceStruct *RandomNumberInterface;

int RandomNumber_Get(RandomNumber);
void RandomNumber_Destroy(RandomNumber);

#include "RandomNumberPrivate.h"

#endif /* D_RandomNumber_H */