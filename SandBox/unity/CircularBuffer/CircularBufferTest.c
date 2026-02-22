#include "unity_fixture.h"
#include "CircularBuffer.h"
#include "stdint.h"
#include "stdlib.h"

#include "unity_fixture.h"

TEST_GROUP(CircularBuffer);
static struct CircularBuffer* circularBuffer = NULL;
TEST_SETUP(CircularBuffer)
{
   circularBuffer = CircularBuffer_Create();
}

TEST_TEAR_DOWN(CircularBuffer)
{
   free(circularBuffer);
}

TEST(CircularBuffer, StartHere)
{
   //TEST_FAIL_MESSAGE("Start here");
}

TEST(CircularBuffer, CircularBufferCreate)
{
   struct CircularBuffer* emptycircularBuffer = NULL;
   emptycircularBuffer = CircularBuffer_Create();
   TEST_ASSERT_NOT_EQUAL(NULL, emptycircularBuffer);
   free(emptycircularBuffer);
}

TEST(CircularBuffer, CircularBufferWriteOne)
{
   TEST_ASSERT_EQUAL(1, CircularBuffer_Write(circularBuffer, 1));
}

TEST(CircularBuffer, CircularBufferPeekOne)
{
   CircularBuffer_Write(circularBuffer, 1);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Peek(circularBuffer));
}

TEST(CircularBuffer, CircularBufferReadOne)
{
   CircularBuffer_Write(circularBuffer, 1);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Read(circularBuffer));
}