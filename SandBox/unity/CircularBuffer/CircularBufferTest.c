#include "unity_fixture.h"
#include "CircularBuffer.h"
#include "stdint.h"
#include "stdlib.h"

TEST_GROUP(CircularBuffer);
static struct CircularBuffer *circularBuffer = NULL;

TEST_SETUP(CircularBuffer)
{
   circularBuffer = CircularBuffer_Create(5);
}

TEST_TEAR_DOWN(CircularBuffer)
{
   CircularBuffer_Destroy(circularBuffer);
}

TEST(CircularBuffer, StartHere)
{
   // TEST_FAIL_MESSAGE("Start here");
}

TEST(CircularBuffer, CircularBufferCreate)
{
   struct CircularBuffer *emptycircularBuffer = NULL;

   emptycircularBuffer = CircularBuffer_Create(10);

   TEST_ASSERT_NOT_EQUAL(NULL, emptycircularBuffer);

   CircularBuffer_Destroy(emptycircularBuffer);
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
      TEST_ASSERT_EQUAL_UINT8((uint8_t)((i + 1) % 5), circularBuffer->tail);
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

#include "FormatOutputSpy.h"

TEST_GROUP(CircularBufferPrint);

CircularBuffer *buffer;
const char *expectedOutput;
const char *actualOutput;

TEST_SETUP(CircularBufferPrint)
{
   UT_PTR_SET(FormatOutput, FormatOutputSpy);
   FormatOutputSpy_Create(100);
   actualOutput = FormatOutputSpy_GetOutput();
   buffer = CircularBuffer_Create(10);
}

TEST_TEAR_DOWN(CircularBufferPrint)
{
   CircularBuffer_Destroy(buffer);
   FormatOutputSpy_Destroy();
}

TEST(CircularBufferPrint, StartHere)
{
   // TEST_FAIL_MESSAGE("Start here");
}

TEST(CircularBufferPrint, PrintEmpty)
{
   expectedOutput = "Circular buffer content:\n<>\n";
   CircularBuffer_Print(buffer);
   STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
   expectedOutput = "Circular buffer content:\n<17>\n";
   CircularBuffer_Write(buffer, 17);
   CircularBuffer_Print(buffer);
   STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull)
{
   expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
   CircularBuffer_Write(buffer, 10);
   CircularBuffer_Write(buffer, 20);
   CircularBuffer_Write(buffer, 30);
   CircularBuffer_Print(buffer);
   STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull)
{
   expectedOutput = "Circular buffer content:\n"
                    "<31, 41, 59, 26, 53>\n";

   CircularBuffer *b = CircularBuffer_Create(5);
   CircularBuffer_Write(b, 31);
   CircularBuffer_Write(b, 41);
   CircularBuffer_Write(b, 59);
   CircularBuffer_Write(b, 26);
   CircularBuffer_Write(b, 53);

   CircularBuffer_Print(b);

   STRCMP_EQUAL(expectedOutput, actualOutput);
   CircularBuffer_Destroy(b);
}

TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull)
{
   expectedOutput =
      "Circular buffer content:\n"
      "<20, 30, 40, 99>\n";

   CircularBuffer *b = CircularBuffer_Create(5);
   CircularBuffer_Write(b, 10);
   CircularBuffer_Write(b, 20);
   CircularBuffer_Write(b, 30);
   CircularBuffer_Write(b, 40);
   CircularBuffer_Read(b);
   CircularBuffer_Write(b, 99);

   CircularBuffer_Print(b);

   STRCMP_EQUAL(expectedOutput, actualOutput);
   CircularBuffer_Destroy(b);
}