#include "unity_fixture.h"

#include "LightDriverSpy.h"

TEST_GROUP(LightDriverSpy);

LightDriver lightDriverSpy;

TEST_SETUP(LightDriverSpy)
{
    LightDriverSpy_Reset();
    lightDriverSpy = LightDriverSpy_Create(1);
}

TEST_TEAR_DOWN(LightDriverSpy)
{
    LightDriver_Destroy(lightDriverSpy);
}

TEST(LightDriverSpy, StartHere)
{
    // TEST_FAIL_MESSAGE("Start Here");
}

TEST(LightDriverSpy, On)
{
    LightDriver_TurnOn(lightDriverSpy);
    // LightDriverSpy_TurnOn(lightDriverSpy);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, Off)
{
    LightDriver_TurnOff(lightDriverSpy);
    // LightDriverSpy_TurnOff(lightDriverSpy);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, Destroy)
{
    LightDriver spy = LightDriverSpy_Create(1);

    LightDriver_Destroy(spy);
    // LightDriverSpy_Destroy(spy);
}
