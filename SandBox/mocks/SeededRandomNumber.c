#include "SeededRandomNumber.h"

#include <stdlib.h>

typedef struct SeededRandomNumberStruct *SeededRandomNumber;
typedef struct SeededRandomNumberStruct
{
    RandomNumberStruct base;
    unsigned seed;
} SeededRandomNumberStruct;

static int SeededRandomNumber_Get(RandomNumber super);
static void SeededRandomNumber_Destroy(RandomNumber super);

static RandomNumberInterfaceStruct interface =
    {
        .Get = SeededRandomNumber_Get,
        .Destroy = SeededRandomNumber_Destroy};

RandomNumber SeededRandomNumber_Create(unsigned seed)
{
    SeededRandomNumber self = calloc(1, sizeof(SeededRandomNumberStruct));
    self->base.vtable = &interface;
    self->seed = seed;

    return (RandomNumber)self;
}

static void SeededRandomNumber_Destroy(RandomNumber super)
{
    SeededRandomNumber self = (SeededRandomNumber)super;
    free(self);
}

static int SeededRandomNumber_Get(RandomNumber super)
{
    SeededRandomNumber self = (SeededRandomNumber)super;
    return rand_r(&self->seed);
}

