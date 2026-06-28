#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
    RUN_TEST_CASE(CircularBuffer, StartHere);
    RUN_TEST_CASE(CircularBuffer, CircularBufferCreate);
    RUN_TEST_CASE(CircularBuffer, CircularBufferWriteOne);
    RUN_TEST_CASE(CircularBuffer, MultipleWritesTest);
    RUN_TEST_CASE(CircularBuffer, OverwriteTest);
    RUN_TEST_CASE(CircularBuffer, CircularBufferPeekOne);
    RUN_TEST_CASE(CircularBuffer, InmutablePeekTest);
    RUN_TEST_CASE(CircularBuffer, CircularBufferReadOne);
    RUN_TEST_CASE(CircularBuffer, ReadEmptyBufferTest);

    RUN_TEST_CASE(CircularBuffer, IsEmptyTest);
    RUN_TEST_CASE(CircularBuffer, IsFullTest);
}

TEST_GROUP_RUNNER(CircularBufferPrint)
{
    RUN_TEST_CASE(CircularBufferPrint, StartHere);
    RUN_TEST_CASE(CircularBufferPrint, PrintEmpty);
    RUN_TEST_CASE(CircularBufferPrint, PrintAfterOneIsPut);
    RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedOrFull);
    RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedAndIsFull);
    RUN_TEST_CASE(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull); 
    RUN_TEST_CASE(CircularBufferPrint, PrintFixColumnSize);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipleLines);
    RUN_TEST_CASE(CircularBufferPrint, Addcharacter);  
}

TEST_GROUP_RUNNER(BufferFormatter)
{
    RUN_TEST_CASE(BufferFormatter, StartHere);
    RUN_TEST_CASE(BufferFormatter, OneBlancSpace);
    RUN_TEST_CASE(BufferFormatter, TwoBlancSpace);
    RUN_TEST_CASE(BufferFormatter, ThreeBlancSpace);
}