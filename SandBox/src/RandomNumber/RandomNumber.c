#include "RandomNumber.h"

int RandomNumber_Get(RandomNumber self)
{
    if (self && self->vtable && self->vtable->Get)
        return self->vtable->Get(self);

    return 0;
}

void RandomNumber_Destroy(RandomNumber self)
{
    if (self && self->vtable && self->vtable->Destroy)
        return self->vtable->Destroy(self);
}