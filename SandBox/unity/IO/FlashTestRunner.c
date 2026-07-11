#include "unity_fixture.h"

TEST_GROUP_RUNNER(Flash)
{
    RUN_TEST_CASE(Flash, StartHere);
    RUN_TEST_CASE(Flash, WriteSucceds_ReadyImmediately);
    RUN_TEST_CASE(Flash, WriteSucceds_NotImmediatelyReady);
    RUN_TEST_CASE(Flash, WriteFails_VppError);
    RUN_TEST_CASE(Flash, WriteFails_ProgramError);
    RUN_TEST_CASE(Flash, WriteFails_ProtectedBlockError);
    RUN_TEST_CASE(Flash, WriteFails_FalshReadBackError);
    RUN_TEST_CASE(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady);
    RUN_TEST_CASE(Flash, WriteFails_Timeout);
    RUN_TEST_CASE(Flash, WriteFails_TimeoutAtEndOfTime);
}