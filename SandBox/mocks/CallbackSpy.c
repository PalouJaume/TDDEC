#include "CallbackSpy.h"

static int spy_state;

void CallbackSpy_Create(void)
{
    spy_state = CALLBACK_NOEXECUTED;
}

void CallbackSpy_Destroy(void)
{
    spy_state = CALLBACK_NOEXECUTED;
}

void CallbackSpy_Run(void)
{
    spy_state = (spy_state == CALLBACK_NOEXECUTED) ? CALLBACK_EXECUTED : (spy_state + 1);
}

CALLBACK_STATUS CallbackSpy_GetStatus(void)
{
    return spy_state;
}
