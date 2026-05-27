#include "unity_fixture.h"

#include "FakeClockService.h"

TEST_GROUP(FakeClockService);

TEST_SETUP(FakeClockService)
{
}

TEST_TEAR_DOWN(FakeClockService)
{
}

TEST(FakeClockService, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(FakeClockService, Create)
{
    FakeClockService_Create();
    LONGS_EQUAL(UNKNOWN_MS, ClockService_Getms());    
}

TEST(FakeClockService, Set)
{
    FakeClockService_Setms(1000);

    LONGS_EQUAL(1000, ClockService_Getms());
}