#include "FakeRandomNumber.h"

#include <stdlib.h>

typedef struct FakeRandomNumberStruct *FakeRandomNumber;
typedef struct FakeRandomNumberStruct
{
    RandomNumberStruct base;
    int fakeValue;
    int fakeInc;
} FakeRandomNumberStruct;

static int FakeRandomNumber_Get(RandomNumber super);
static void FakeRandomNumber_Destroy(RandomNumber super);

static RandomNumberInterfaceStruct interface =
    {
        .Get = FakeRandomNumber_Get,
        .Destroy = FakeRandomNumber_Destroy};

RandomNumber FakeRandomNumber_Create(int first, int inc)
{
    FakeRandomNumber self = calloc(1, sizeof(FakeRandomNumberStruct));
    self->base.vtable = &interface;
    self->fakeValue = first;
    self->fakeInc = inc;

    return (RandomNumber)self;
}

static void FakeRandomNumber_Destroy(RandomNumber super)
{
    FakeRandomNumber self = (FakeRandomNumber)super;
    free(self);
}

static int FakeRandomNumber_Get(RandomNumber super)
{
    FakeRandomNumber self = (FakeRandomNumber)super;
    int res = self->fakeValue;
    self->fakeValue += self->fakeInc;

    return res;
}