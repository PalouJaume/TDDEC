#include "unity_fixture.h"

TEST_GROUP_RUNNER(AlarmClock)
{
    RUN_TEST_CASE(AlarmClock, StartHere);
    RUN_TEST_CASE(AlarmClock, Create);
    RUN_TEST_CASE(AlarmClock, OneCallbackWrongTimeNoExecution);
    RUN_TEST_CASE(AlarmClock, OneCallbackRightTimeExecution);
    RUN_TEST_CASE(AlarmClock, MultipleCallbackExecution);
    RUN_TEST_CASE(AlarmClock, RemoveOneCallback);
    RUN_TEST_CASE(AlarmClock, RemoveMultipleCallbacks);
    RUN_TEST_CASE(AlarmClock, TwoCallbacksDifferentTimesOnlyOneExecutes);
}