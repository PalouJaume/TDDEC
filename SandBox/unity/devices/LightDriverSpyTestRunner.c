#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightDriverSpy)
{
    RUN_TEST_CASE(LightDriverSpy, StartHere);
    RUN_TEST_CASE(LightDriverSpy, On);
    RUN_TEST_CASE(LightDriverSpy, Off);
    RUN_TEST_CASE(LightDriverSpy, Destroy);
}