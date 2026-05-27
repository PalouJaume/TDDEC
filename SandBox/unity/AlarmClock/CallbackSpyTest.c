#include "unity_fixture.h"

#include "CallbackSpy.h"

TEST_GROUP(CallbackSpy);

TEST_SETUP(CallbackSpy)
{
    CallbackSpy_Create();
}

TEST_TEAR_DOWN(CallbackSpy)
{
    CallbackSpy_Destroy();
}

TEST(CallbackSpy, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(CallbackSpy, NotRun)
{
    LONGS_EQUAL(CALLBACK_NOEXECUTED, CallbackSpy_GetStatus());
}

TEST(CallbackSpy, Run)
{
    CallbackSpy_Run();

    LONGS_EQUAL(CALLBACK_EXECUTED, CallbackSpy_GetStatus());
}

TEST(CallbackSpy, MultipleRuns)
{
    CallbackSpy_Run();
    CallbackSpy_Run();

    LONGS_EQUAL(2, CallbackSpy_GetStatus());
}