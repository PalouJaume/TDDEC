#include "unity_fixture.h"
#include "FakeTimeService.h"

#include "LightScheduler.h"

TEST_GROUP(FakeTimeService);

TEST_SETUP(FakeTimeService)
{
    TimeService_Create();
}

TEST_TEAR_DOWN(FakeTimeService)
{
    TimeService_Destroy();
}

TEST(FakeTimeService, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(FakeTimeService, Create)
{
    Time time;
    TimeService_GetTime(&time);
    LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    LONGS_EQUAL(42, time.minuteOfDay);
    LONGS_EQUAL(SATURDAY, time.dayOfWeek);
}