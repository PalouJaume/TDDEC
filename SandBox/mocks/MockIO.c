#include "MockIO.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "unity_fixture.h"

typedef struct Expectation
{
    int kind;
    ioAddress addr;
    ioData value;
} Expectation;

static char *report_expect_write_was_read =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "        But was IO_Read(0x%x)";
static char *report_read_wrong_address =
    "Expected IO_Read(0x%x) returns 0x%x;\n"
    "        But was IO_Read(0x%x)";
static char *report_expect_read_was_write =
    "Expected IO_Read(0x%x) would return 0x%x)\n"
    "        But was IO_Write(0x%x, 0x%x)";
static char *report_write_does_not_match =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "        But was IO_Write(0x%x, 0x%x)";
static char *report_too_many_write_expectations =
    "MockIO_Expect_IO_Write: Too many expectations";
static char *report_too_many_read_expectations =
    "MockIO_Expect_IO_Read: Too many expectations";
static char *report_MockIO_not_initialized =
    "MockIO not initialized, call MockIO_Create()";
static char *report_write_but_out_of_expectations =
    "IO_Write(0x%x, 0x%x)";
static char *report_read_but_out_of_expectations =
    "IO_Read(0x%x)";
static const char *report_no_more_expectations =
    "R/W %d: No more expectations but was ";
static const char *report_expectation_number =
    "R/W %d: ";

enum
{
    FLASH_READ,
    FLASH_WRITE,
    NoExpectedValue = -1
};

static Expectation *expectations = NULL;
static int setExpectationCount;
static int getExpectationCount;
static int maxExpectationCount;
static int failureAlreadyReported = 0;

static Expectation expected;
static Expectation actual;

static void recordExpectation(int kind, ioAddress addr, ioData value)
{
    expectations[setExpectationCount].kind = kind;
    expectations[setExpectationCount].addr = addr;
    expectations[setExpectationCount].value = value;
    setExpectationCount++;

    return;
}

static void fail(char *msg)
{
    failureAlreadyReported = 1;
    TEST_FAIL_MESSAGE(msg);
}

static void failWhenNotInitialized(void)
{
    if (expectations == NULL)
        fail(report_MockIO_not_initialized);
}

static void failWhenNoRoomForExpectations(char *msg)
{
    failWhenNotInitialized();
    if (setExpectationCount >= maxExpectationCount)
        fail(msg);
}

static void failWhenNoUnusedExpectations(char *fmt)
{
    char msg[100];
    int size = sizeof msg - 1;

    if (getExpectationCount >= setExpectationCount)
    {
        int offset = snprintf(msg,
                              size,
                              report_no_more_expectations,
                              getExpectationCount + 1);
        snprintf(msg + offset, size - offset,
                 fmt, actual.addr, actual.value);
        fail(msg);
    }
}

static void failWhenNotAllExpectationsUsed(void)
{
    char fmt[] = "Expected %d reads/writes but got %d";
    char msg[sizeof fmt + 5 + 5];

    if (getExpectationCount == setExpectationCount)
        return;

    snprintf(msg,
             sizeof msg,
             fmt,
             setExpectationCount,
             getExpectationCount);
    fail(msg);
}

static void setExpectedAndActual(ioAddress addr, ioData value)
{
    expected.addr = expectations[getExpectationCount].addr;
    expected.value = expectations[getExpectationCount].value;
    actual.addr = addr;
    actual.value = value;
}

static void failExpectation(char *expectationFailMessage)
{
    char msg[100];
    int size = sizeof msg - 1;
    int offset = snprintf(msg,
                          size,
                          report_expectation_number,
                          getExpectationCount + 1);
    snprintf(msg + offset,
             size - offset,
             expectationFailMessage,
             expected.addr,
             expected.value,
             actual.addr,
             actual.value);
    fail(msg);
}

static void failWhen(int condition, char *expectationFailMessage)
{
    if (condition)
        failExpectation(expectationFailMessage);
}

static int expectationIsNot(int kind)
{
    return kind != expectations[getExpectationCount].kind;
}

static int expectedAddressIsNot(ioAddress addr)
{
    return expected.addr != addr;
}

static int expectedDataIsNot(ioData data)
{
    return expected.value != data;
}

void IO_Write(ioAddress addr, ioData value)
{
    setExpectedAndActual(addr, value);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_write_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_WRITE), report_expect_read_was_write);
    failWhen(expectedAddressIsNot(addr), report_write_does_not_match);
    failWhen(expectedDataIsNot(value), report_write_does_not_match);
    getExpectationCount++;
}

ioData IO_Read(ioAddress addr)
{
    setExpectedAndActual(addr, NoExpectedValue);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_read_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_READ), report_expect_write_was_read);
    failWhen(expectedAddressIsNot(addr), report_read_wrong_address);

    return expectations[getExpectationCount++].value;
}

void MockIO_Create(int maxExpectations)
{
    expectations = calloc(maxExpectations, sizeof(Expectation));
    setExpectationCount = 0;
    getExpectationCount = 0;
    maxExpectationCount = maxExpectations;
    failureAlreadyReported = 0;
}

void MockIO_Destroy(void)
{
    if (expectations)
        free(expectations);
    expectations = NULL;
}

void MockIO_Expect_Write(ioAddress addr, ioData value)
{
    failWhenNoRoomForExpectations(report_too_many_write_expectations);
    recordExpectation(FLASH_WRITE, addr, value);
}

void MockIO_Expect_ReadThenReturn(ioAddress addr, ioData value)
{
    failWhenNoRoomForExpectations(report_too_many_read_expectations);
    recordExpectation(FLASH_READ, addr, value);
}

void MockIO_Verify_Complete(void)
{
    if (failureAlreadyReported)
        return;
    failWhenNotAllExpectationsUsed();
}
