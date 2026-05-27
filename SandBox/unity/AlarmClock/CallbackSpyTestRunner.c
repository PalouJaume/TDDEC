#include "unity_fixture.h"

TEST_GROUP_RUNNER(CallbackSpy)
{
    RUN_TEST_CASE(CallbackSpy, StartHere);
    RUN_TEST_CASE(CallbackSpy, NotRun);
    RUN_TEST_CASE(CallbackSpy, Run);
    RUN_TEST_CASE(CallbackSpy, MultipleRuns);
}