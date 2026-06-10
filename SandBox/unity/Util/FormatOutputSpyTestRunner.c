#include "unity_fixture.h"

TEST_GROUP_RUNNER(FormatOutputSpy)
{
    //RUN_TEST_CASE(FormatOutputSpy, StartHere);
    RUN_TEST_CASE(FormatOutputSpy, HelloWorld);
    RUN_TEST_CASE(FormatOutputSpy, LimitTheOutputBufferSize);
    RUN_TEST_CASE(FormatOutputSpy, PrintMultipleTimes);
    RUN_TEST_CASE(FormatOutputSpy, PrintMultipleOutputsPastFull);
}