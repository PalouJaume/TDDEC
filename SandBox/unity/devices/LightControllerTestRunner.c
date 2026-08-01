#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightController)
{
    RUN_TEST_CASE(LightController, TurnOn);
    RUN_TEST_CASE(LightController, TurnOff);
    RUN_TEST_CASE(LightController, AddingDriverDestroysPrevious);
    RUN_TEST_CASE(LightController, AllDriversDestroyed);
    RUN_TEST_CASE(LightController, ValidIdLowerRange);
    RUN_TEST_CASE(LightController, ValidIdUpperRange);
    RUN_TEST_CASE(LightController, InvalidIdBeyondUpperRange);
    RUN_TEST_CASE(LightController, NonAddedLightDoesNothing);
    RUN_TEST_CASE(LightController, turnOnDifferentDriverTypes);
}