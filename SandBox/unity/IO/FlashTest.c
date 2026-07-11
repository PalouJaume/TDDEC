#include "unity_fixture.h"

#include "Flash.h"
#include "MockIO.h"
#include "FakeMicroTime.h"

TEST_GROUP(Flash);

ioAddress address;
ioData data;
int result;

TEST_SETUP(Flash)
{
    address = 0x1000;
    data = 0xBEEF;
    result = -1;

    MockIO_Create(10);
    Flash_Create();
}

TEST_TEAR_DOWN(Flash)
{
    Flash_Destroy();
    MockIO_Verify_Complete();
    MockIO_Destroy();
}

TEST(Flash, StartHere)
{
    // TEST_FAIL_MESSAGE("Start here");
}

TEST(Flash, WriteSucceds_ReadyImmediately)
{
    MockIO_Expect_Write(0, 0x40);
    MockIO_Expect_Write(0x1000, 0xBEEF);
    MockIO_Expect_ReadThenReturn(0, 1 << 7);
    MockIO_Expect_ReadThenReturn(0x1000, 0xBEEF);

    result = Flash_Write(0x1000, 0xBEEF);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteSucceds_NotImmediatelyReady)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(address, data);

    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_VppError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | VppErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_ProgramError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | ProgramErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_ProtectedBlockError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | BlockProtectionErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROTECTED_BLOCK_ERROR, result);
}

TEST(Flash, WriteFails_FalshReadBackError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(address, data - 1);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(address, data);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_Timeout)
{
    FakeMicroTime_Init(0, 500);

    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    for (int i = 0; i < 5; i++)
        MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

TEST(Flash, WriteFails_TimeoutAtEndOfTime)
{
    FakeMicroTime_Init(0xFFFFFFFF, 500);

    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    for (int i = 0; i < 0; i++)
        MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);

    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}