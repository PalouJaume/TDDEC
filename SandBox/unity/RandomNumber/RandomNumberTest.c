#include "unity_fixture.h"

#include "RandomNumber.h"

TEST_GROUP(RandomNumber);

TEST_SETUP(RandomNumber)
{
}

TEST_TEAR_DOWN(RandomNumber)
{
}

/* START: nullDriver */
static RandomNumberStruct testRandom =
    {
        .vtable = NULL};
/* END: nullDriver */

TEST(RandomNumber, StartHere)
{
    TEST_FAIL_MESSAGE("Start Here");
}

/* START: nullRandomTest */
TEST(RandomNumber, NullRandomDoesNotCrash)
{
    RandomNumber_Get(NULL);
    RandomNumber_Destroy(NULL);
}
/* END: nullRandomTest */

/* START: nullInterfaceTest */
TEST(RandomNumber, NullInterfaceDoesNotCrash)
{
    RandomNumber_Get(&testRandom);
    RandomNumber_Destroy(&testRandom);
}