#ifndef D_RandomNumberPrivate_H
#define D_RandomNumberPrivate_H

#include "RandomNumber.h"

typedef struct RandomNumberStruct
{
    RandomNumberInterface vtable;
} RandomNumberStruct;

typedef struct RandomNumberInterfaceStruct
{
    int (*Get)(RandomNumber);
    void (*Destroy)(RandomNumber);
} RandomNumberInterfaceStruct;

#endif /* D_RandomNumberPrivate_H */