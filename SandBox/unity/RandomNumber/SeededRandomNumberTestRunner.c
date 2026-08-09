#include "unity_fixture.h"

TEST_GROUP_RUNNER(SeededRandomNumber)
{
    RUN_TEST_CASE(SeededRandomNumber, StartHere);
    RUN_TEST_CASE(SeededRandomNumber, Get);
}