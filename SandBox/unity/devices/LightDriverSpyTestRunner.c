#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightDriverSpy)
{
    RUN_TEST_CASE(LightDriverSpy, StartHere);
    RUN_TEST_CASE(LightDriverSpy, On);
    RUN_TEST_CASE(LightDriverSpy, Off);
    RUN_TEST_CASE(LightDriverSpy, Destroy);
    RUN_TEST_CASE(LightDriverSpy, DefaultBrightLevel);
    RUN_TEST_CASE(LightDriverSpy, Brighten);
    RUN_TEST_CASE(LightDriverSpy, BrightenSaturates);
    RUN_TEST_CASE(LightDriverSpy, BrightenMultipleLights);
    RUN_TEST_CASE(LightDriverSpy, Dim);
    RUN_TEST_CASE(LightDriverSpy, DimSaturates);
    RUN_TEST_CASE(LightDriverSpy, Strobe);
    RUN_TEST_CASE(LightDriverSpy, PartialInterface);
}