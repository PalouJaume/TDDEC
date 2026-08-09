#include "unity_fixture.h"

TEST_GROUP_RUNNER(FakeRandomNumber)
{
    RUN_TEST_CASE(FakeRandomNumber, StartHere);
    RUN_TEST_CASE(FakeRandomNumber, Get);
    RUN_TEST_CASE(FakeRandomNumber, MultipleGets);
}