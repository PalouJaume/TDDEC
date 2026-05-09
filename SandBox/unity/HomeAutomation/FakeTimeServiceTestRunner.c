#include "unity_fixture.h"

TEST_GROUP_RUNNER(FakeTimeService)
{
    //RUN_TEST_CASE(FakeTimeService, StartHere);
    RUN_TEST_CASE(FakeTimeService, Create);
    RUN_TEST_CASE(FakeTimeService, Set);
}