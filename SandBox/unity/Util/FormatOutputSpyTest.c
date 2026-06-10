#include "unity_fixture.h"

#include "FormatOutputSpy.h"

TEST_GROUP(FormatOutputSpy);

TEST_SETUP(FormatOutputSpy)
{
    UT_PTR_SET(FormatOutput, FormatOutputSpy);
}

TEST_TEAR_DOWN(FormatOutputSpy)
{
    FormatOutputSpy_Destroy();
}

TEST(FormatOutputSpy, StartHere)
{
    TEST_FAIL_MESSAGE("Start Here");
}

TEST(FormatOutputSpy, HelloWorld)
{
    FormatOutputSpy_Create(20);

    FormatOutput("Hello, World\n");

    STRCMP_EQUAL("Hello, World\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, LimitTheOutputBufferSize)
{
    FormatOutputSpy_Create(4);

    FormatOutput("Hello, World\n");

    STRCMP_EQUAL("Hell", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleTimes)
{
    FormatOutputSpy_Create(25);

    FormatOutput("Hello");
    FormatOutput(", World\n");

    STRCMP_EQUAL("Hello, World\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleOutputsPastFull)
{
    FormatOutputSpy_Create(12);
    FormatOutput("12345");
    FormatOutput("67890");
    FormatOutput("ABCDEF");
    STRCMP_EQUAL("1234567890AB", FormatOutputSpy_GetOutput());
}