#include "unity_fixture.h"

TEST_GROUP_RUNNER(FakeClockService)
{
    RUN_TEST_CASE(FakeClockService, StartHere);
    RUN_TEST_CASE(FakeClockService, Create);
    RUN_TEST_CASE(FakeClockService, Set);
}