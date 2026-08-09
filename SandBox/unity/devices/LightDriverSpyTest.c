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

TEST(LightDriverSpy, DefaultBrightLevel)
{
    LONGS_EQUAL(50, LightDriverSpy_GetBright(1));
}

TEST(LightDriverSpy, Brighten)
{
    LightDriver_Brighten(lightDriverSpy);

    LONGS_EQUAL(60, LightDriverSpy_GetBright(1));
}

TEST(LightDriverSpy, BrightenSaturates)
{
    for (int i = 0; i < 3; i++)
        LightDriver_Brighten(lightDriverSpy);

    LONGS_EQUAL(80, LightDriverSpy_GetBright(1));

    for (int i = 0; i < 10; i++)
        LightDriver_Brighten(lightDriverSpy);

    LONGS_EQUAL(100, LightDriverSpy_GetBright(1));
}

TEST(LightDriverSpy, BrightenMultipleLights)
{
    LightDriver spy = LightDriverSpy_Create(3);

    LightDriver_Brighten(lightDriverSpy);

    LONGS_EQUAL(60, LightDriverSpy_GetBright(1));
    LONGS_EQUAL(50, LightDriverSpy_GetBright(3));

    LightDriver_Destroy(spy);
}

TEST(LightDriverSpy, Dim)
{
    LightDriver_Dim(lightDriverSpy);

    LONGS_EQUAL(40, LightDriverSpy_GetBright(1));
}

TEST(LightDriverSpy, DimSaturates)
{
    for (int i = 0; i < 3; i++)
        LightDriver_Dim(lightDriverSpy);

    LONGS_EQUAL(20, LightDriverSpy_GetBright(1));

    for (int i = 0; i < 10; i++)
        LightDriver_Dim(lightDriverSpy);

    LONGS_EQUAL(0, LightDriverSpy_GetBright(1));
}

TEST(LightDriverSpy, Strobe)
{
    LightDriver_Strobe(lightDriverSpy);
    LONGS_EQUAL(LIGHT_STROBE, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, PartialInterface)
{
    LightDriver spy = LightDriverSpy_PartialCreate(1);

    LightDriver_Brighten(spy);
    LONGS_EQUAL(50, LightDriverSpy_GetBright(1));

    LightDriver_Dim(spy);
    LONGS_EQUAL(50, LightDriverSpy_GetBright(1));

    LightDriver_Strobe(spy);
    LONGS_EQUAL(LIGHT_STROBE, LightDriverSpy_GetState(1));

    LightDriver_Destroy(spy);
}