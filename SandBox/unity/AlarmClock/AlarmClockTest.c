#include "unity_fixture.h"

#include "AlarmClock.h"
#include "FakeClockService.h"
#include "CallbackSpy.h"

TEST_GROUP(AlarmClock);

TEST_SETUP(AlarmClock)
{
    CallbackSpy_Create();
    AlarmClock_Create();
}

TEST_TEAR_DOWN(AlarmClock)
{
    CallbackSpy_Destroy();
    AlarmClock_Destroy();
}

TEST(AlarmClock, StartHere)
{
    // TEST_FAIL_MESSAGE("Start Here");
}

TEST(AlarmClock, Create)
{
    FakeClockService_Setms(300);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_NOEXECUTED, CallbackSpy_GetStatus());
}

TEST(AlarmClock, OneCallbackWrongTimeNoExecution)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);

    FakeClockService_Setms(300);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_NOEXECUTED, CallbackSpy_GetStatus());
}

TEST(AlarmClock, OneCallbackRightTimeExecution)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);

    FakeClockService_Setms(500);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_EXECUTED, CallbackSpy_GetStatus());
}

TEST(AlarmClock, MultipleCallbackExecution)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);

    FakeClockService_Setms(500);

    AlarmClock_WakeUp();

    LONGS_EQUAL(3, CallbackSpy_GetStatus());
}

TEST(AlarmClock, RemoveOneCallback)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);

    FakeClockService_Setms(500);

    AlarmClock_RemoveAlarm(CallbackSpy_Run, 500);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_NOEXECUTED, CallbackSpy_GetStatus());
}

TEST(AlarmClock, RemoveMultipleCallbacks)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 100);
    AlarmClock_SetAlarm(CallbackSpy_Run, 100);
    AlarmClock_SetAlarm(CallbackSpy_Run, 100);
    AlarmClock_SetAlarm(CallbackSpy_Run, 100);

    FakeClockService_Setms(100);

    AlarmClock_RemoveAlarm(CallbackSpy_Run, 100);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_NOEXECUTED, CallbackSpy_GetStatus());
}

TEST(AlarmClock, TwoCallbacksDifferentTimesOnlyOneExecutes)
{
    AlarmClock_SetAlarm(CallbackSpy_Run, 300);
    AlarmClock_SetAlarm(CallbackSpy_Run, 500);

    FakeClockService_Setms(300);

    AlarmClock_WakeUp();

    LONGS_EQUAL(CALLBACK_EXECUTED, CallbackSpy_GetStatus());
}