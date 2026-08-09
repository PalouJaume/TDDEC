#include "unity_fixture.h"

TEST_GROUP_RUNNER(RandomNumber)
{
    //RUN_TEST_CASE(RandomNumber, StartHere);
    RUN_TEST_CASE(RandomNumber, NullRandomDoesNotCrash);
    RUN_TEST_CASE(RandomNumber, NullInterfaceDoesNotCrash);
}