#include "unity_fixture.h"

TEST_GROUP_RUNNER(EmailServiceSpy)
{
    RUN_TEST_CASE(EmailServiceSpy, StartHere);
    RUN_TEST_CASE(EmailServiceSpy, Create);
    RUN_TEST_CASE(EmailServiceSpy, Get);
}