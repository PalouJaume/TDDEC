#include "unity_fixture.h"

#include "LightDriverSpy.h"

TEST_GROUP(LightDriver);

TEST_SETUP(LightDriver)
{
}

TEST_TEAR_DOWN(LightDriver)
{
}

/* START: nullDriver */
#define NONSENSE_POINTER (LightDriver) ~0
static LightDriver savedDriver = NONSENSE_POINTER;
static void shouldNotBeCalled(LightDriver self) { savedDriver = self; }

static LightDriverInterfaceStruct interface =
    {
        shouldNotBeCalled,
        shouldNotBeCalled,
        shouldNotBeCalled};

static LightDriverStruct testDriver =
    {
        TestLightDriver,
        13};
/* END: nullDriver */

TEST(LightDriver, StartHere)
{
    TEST_FAIL_MESSAGE("Start Here");
}

/* START: nullDriverTest */
TEST(LightDriver, NullDriverDoesNotCrash)
{
    LightDriver_SetInterface(&interface);
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
    TEST_ASSERT_EQUAL_PTR(NONSENSE_POINTER, savedDriver);
}
/* END: nullDriverTest*/

/* START: nullInterfaceTest */
TEST(LightDriver, NullInterfaceDoesNotCrash)
{
    LightDriver_SetInterface(NULL);
    LightDriver_TurnOn(&testDriver);
    LightDriver_TurnOff(&testDriver);
    LightDriver_Destroy(&testDriver);
    TEST_ASSERT_EQUAL_PTR(NONSENSE_POINTER, savedDriver);
}
/* END: nullInterfaceTest */
