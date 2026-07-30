#include "unity_fixture.h"

#include "LightController.h"
#include "LightDriverSpy.h"

TEST_GROUP(LightController);

LightDriver spy;

TEST_SETUP(LightController)
{
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
    LightDriverSpy_InstallInterface();
    LightDriverSpy_Reset();
}

TEST_TEAR_DOWN(LightController)
{
    LightController_Destroy();
}

TEST(LightController, TurnOn)
{
    LightController_On(7);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
}

TEST(LightController, TurnOff)
{
    LightController_Off(1);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightController, AddingDriverDestroysPrevious)
{
    spy = LightDriverSpy_Create(1);
    LightController_Add(1, spy);
    LightController_Destroy();
}

TEST(LightController, AllDriversDestroyed)
{
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        spy = LightDriverSpy_Create(i);
        LONGS_EQUAL(TRUE, LightController_Add(i, spy));
    }
}

TEST(LightController, ValidIdLowerRange)
{
    spy = LightDriverSpy_Create(0);
    LONGS_EQUAL(TRUE, LightController_Add(0, spy));
}

TEST(LightController, ValidIdUpperRange)
{
    spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(TRUE, LightController_Add(MAX_LIGHTS - 1, spy));
}

TEST(LightController, InvalidIdBeyondUpperRange)
{
    spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(FALSE, LightController_Add(MAX_LIGHTS, spy));
    LightDriver_Destroy(spy);
}

TEST(LightController, NonAddedLightDoesNothing)
{
    LightController_Add(1, NULL);
    LightController_On(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
    LightController_Off(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}
