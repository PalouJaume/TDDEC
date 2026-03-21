#include "unity_fixture.h"
#include "CircularBuffer.h"
#include "stdint.h"
#include "stdlib.h"

TEST_GROUP(CircularBuffer);
static struct CircularBuffer *circularBuffer = NULL;

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
   // TEST_FAIL_MESSAGE("Start here");
}

TEST(CircularBuffer, CircularBufferCreate)
{
   struct CircularBuffer *emptycircularBuffer = NULL;
   emptycircularBuffer = CircularBuffer_Create();
   TEST_ASSERT_NOT_EQUAL(NULL, emptycircularBuffer);
   free(emptycircularBuffer);
}

TEST(CircularBuffer, CircularBufferWriteOne)
{
   TEST_ASSERT_EQUAL_INT(0, CircularBuffer_Write(circularBuffer, 1));
}

TEST(CircularBuffer, MultipleWritesTest)
{
   CircularBuffer_Write(circularBuffer, 1);
   CircularBuffer_Write(circularBuffer, 2);
   CircularBuffer_Write(circularBuffer, 3);

   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(3, CircularBuffer_Read(circularBuffer));
}

TEST(CircularBuffer, OverwriteTest)
{
   for (int8_t i = 0; i < 6; i++)
   {
      CircularBuffer_Write(circularBuffer, i);
      TEST_ASSERT_EQUAL_UINT8(0, circularBuffer->head);
      TEST_ASSERT_EQUAL_UINT8((uint8_t)((i+1)%5), circularBuffer->tail);
   }
   TEST_ASSERT_EQUAL_INT(5, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(3, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(4, CircularBuffer_Read(circularBuffer));
}

TEST(CircularBuffer, CircularBufferPeekOne)
{
   CircularBuffer_Write(circularBuffer, 1);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Peek(circularBuffer));
}

TEST(CircularBuffer, InmutablePeekTest)
{
   CircularBuffer_Write(circularBuffer, 1);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Peek(circularBuffer));
   CircularBuffer_Write(circularBuffer, 2);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Peek(circularBuffer));
}

TEST(CircularBuffer, CircularBufferReadOne)
{
   CircularBuffer_Write(circularBuffer, 1);
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Read(circularBuffer));
}

TEST(CircularBuffer, IsEmptyTest)
{
   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_IsEmpty(circularBuffer));
   CircularBuffer_Write(circularBuffer, 0);
   TEST_ASSERT_EQUAL_INT(0, CircularBuffer_IsEmpty(circularBuffer));

   // Fill Buffer
   for (int i = 1; i < 5; i++)
      CircularBuffer_Write(circularBuffer, i);
      
   TEST_ASSERT_EQUAL_INT(0, CircularBuffer_IsEmpty(circularBuffer));

   // Empty Buffer
   for (int i = 5; i > 0; i--)
      CircularBuffer_Read(circularBuffer);

   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_IsEmpty(circularBuffer));   
}

TEST(CircularBuffer, IsFullTest)
{
   TEST_ASSERT_EQUAL_INT(0, CircularBuffer_IsFull(circularBuffer));

   // Fill Buffer
   for (int i = 0; i < 5; i++)
      CircularBuffer_Write(circularBuffer, i);

   TEST_ASSERT_EQUAL_INT(1, CircularBuffer_IsFull(circularBuffer));
}

TEST(CircularBuffer, ReadEmptyBufferTest)
{
   TEST_ASSERT_EQUAL_INT(0, CircularBuffer_Read(circularBuffer));
   TEST_ASSERT_EQUAL_INT(0, circularBuffer->head);
   TEST_ASSERT_EQUAL_INT(0, circularBuffer->tail);
   TEST_ASSERT_EQUAL_INT(0, circularBuffer->cnt);
}