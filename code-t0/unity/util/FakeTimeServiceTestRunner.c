#include "unity_fixture.h"

TEST_GROUP_RUNNER(TimeService)
{
    RUN_TEST_CASE(TimeService, Create);
    RUN_TEST_CASE(TimeService, Set);
}