#include "unity_fixture.h"

#include "TimeService.h"
#include "FakeTimeService.h"

TEST_GROUP(TimeService);

static Time time = NULL;

TEST_SETUP(TimeService)
{
    TimeService_Create();
}

TEST_TEAR_DOWN(TimeService)
{
    TimeService_Destroy();
    TimeService_FreeTime(time);
}

TEST(TimeService, Create)
{
    time = TimeService_GetTime();

    LONGS_EQUAL(-1, TimeService_GetMinute(time));
    LONGS_EQUAL(-1, TimeService_GetDay(time));
}

TEST(TimeService, Set)
{
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(3);

    time = TimeService_GetTime();
    
    LONGS_EQUAL(42, TimeService_GetMinute(time));
    LONGS_EQUAL(3, TimeService_GetDay(time));
}