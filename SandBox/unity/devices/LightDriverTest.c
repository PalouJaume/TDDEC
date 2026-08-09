#include "unity_fixture.h"

#include "LightDriver.h"

TEST_GROUP(LightDriver);

TEST_SETUP(LightDriver)
{
}

TEST_TEAR_DOWN(LightDriver)
{
}

/* START: nullDriver */
static LightDriverStruct testDriver =
    {
        .vtable = NULL,
        .type = "TestLightDriver",
        .id = 13};
/* END: nullDriver */

TEST(LightDriver, StartHere)
{
    TEST_FAIL_MESSAGE("Start Here");
}

/* START: nullDriverTest */
TEST(LightDriver, NullDriverDoesNotCrash)
{
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
}
/* END: nullDriverTest*/

/* START: nullInterfaceTest */
TEST(LightDriver, NullInterfaceDoesNotCrash)
{
    LightDriver_TurnOn(&testDriver);
    LightDriver_TurnOff(&testDriver);
    LightDriver_Destroy(&testDriver);
}
/* END: nullInterfaceTest */
