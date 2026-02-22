#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
    RUN_TEST_CASE(CircularBuffer, StartHere);
    RUN_TEST_CASE(CircularBuffer, CircularBufferCreate);
    RUN_TEST_CASE(CircularBuffer, CircularBufferWriteOne);
    RUN_TEST_CASE(CircularBuffer, CircularBufferPeekOne);
    RUN_TEST_CASE(CircularBuffer, CircularBufferReadOne);
}