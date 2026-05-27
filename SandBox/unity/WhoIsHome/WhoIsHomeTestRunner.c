#include "unity_fixture.h"

TEST_GROUP_RUNNER(WhoIsHome)
{
    RUN_TEST_CASE(WhoIsHome, StartHere);
    RUN_TEST_CASE(WhoIsHome, Create);
    RUN_TEST_CASE(WhoIsHome, RFIDEventInRange);
    RUN_TEST_CASE(WhoIsHome, RFIDEventOutRange);
    RUN_TEST_CASE(WhoIsHome, REFIDEventsInRangeOutRange);
}