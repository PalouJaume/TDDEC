#include "unity_fixture.h"

TEST_GROUP_RUNNER(RandomMinute)
{
    RUN_TEST_CASE(RandomMinute, GetIsInRange);
    RUN_TEST_CASE(RandomMinute, AllValuesPossible);
}