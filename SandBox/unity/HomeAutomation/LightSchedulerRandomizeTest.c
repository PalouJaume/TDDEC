#include "unity_fixture.h"
#include "LightScheduler.h"

#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"

// TODO: Complete FakeRandomminute

TEST_GROUP(LightSchedulerRandomize);

int (*savedRandomMinute_Get)(void);

static void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

static void checkLightState(int id, int level)
{
    if (id == LIGHT_ID_UNKNOWN)
    {
        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    }
    else
        LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
}

TEST_SETUP(LightSchedulerRandomize)
{
    LightController_Create();
    LightScheduler_Create();
    TimeService_Create();

    UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
}

TEST_TEAR_DOWN(LightSchedulerRandomize)
{
    LightController_Destroy();
    LightScheduler_Destroy();
    TimeService_Destroy();

    RandomMinute_Get = savedRandomMinute_Get;
}

TEST(LightSchedulerRandomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);

    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);

    LightScheduler_Randomize(4, EVERYDAY, 600);

    setTimeTo(MONDAY, 600 - 10);

    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_ON);
}