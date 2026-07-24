#include "unity_fixture.h"

#include "Flash.h"
#include "MockIO.h"
#include "FakeMicroTime.h"
#include "string.h"

TEST_GROUP(Flash);

ioAddress address;
ioData data;
int result;

TEST_SETUP(Flash)
{
    address = 0x1000;
    data = 0xBEEF;
    result = -1;

    MockIO_Create(20);
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
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
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
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_ProgramError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | ProgramErrorBit);
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_ProtectedBlockError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | BlockProtectionErrorBit);
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

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

TEST(Flash, ReadCFIQueryIdentificationString)
{
    struct cfi_IdentificationString id;

    MockIO_Expect_Write(CommandRegister, CFIQueryCommand);
    MockIO_Expect_ReadThenReturn(0x00, 0x0020);
    MockIO_Expect_ReadThenReturn(0x01, 0x88CE);
    MockIO_Expect_ReadThenReturn(0x10, 0x0051);
    MockIO_Expect_ReadThenReturn(0x11, 0x0052);
    MockIO_Expect_ReadThenReturn(0x12, 0x0059);
    MockIO_Expect_ReadThenReturn(0x13, 0x0003);
    MockIO_Expect_ReadThenReturn(0x14, 0x0000);
    MockIO_Expect_ReadThenReturn(0X15, 0x0035);
    MockIO_Expect_ReadThenReturn(0x16, 0x0000);
    MockIO_Expect_ReadThenReturn(0x17, 0x0000);
    MockIO_Expect_ReadThenReturn(0x18, 0x0000);
    MockIO_Expect_ReadThenReturn(0x19, 0x0000);
    MockIO_Expect_ReadThenReturn(0x1A, 0x0000);
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

    result = Flash_CFI_Identification(&id);

    LONGS_EQUAL(FLASH_SUCCESS, result);

    TEST_ASSERT_EQUAL_HEX16(0x0020, id.MC);
    TEST_ASSERT_EQUAL_HEX16(0x88CE, id.DC);

    TEST_ASSERT_EQUAL_HEX16(0x0051, id.QUAS[0]);
    TEST_ASSERT_EQUAL_HEX16(0x0052, id.QUAS[1]);
    TEST_ASSERT_EQUAL_HEX16(0x0059, id.QUAS[2]);

    TEST_ASSERT_EQUAL_HEX16(0x0003, id.PACSCII[0]);
    TEST_ASSERT_EQUAL_HEX16(0x0000, id.PACSCII[1]);

    TEST_ASSERT_EQUAL_HEX16(0x0035, id.APAEQT[0]);
    TEST_ASSERT_EQUAL_HEX16(0x0000, id.APAEQT[1]);

    TEST_ASSERT_EQUAL_HEX16(0x0000, id.AVCSCIIC[0]);
    TEST_ASSERT_EQUAL_HEX16(0x0000, id.AVCSCIIC[1]);

    TEST_ASSERT_EQUAL_HEX16(0x0000, id.AAAEQT[0]);
    TEST_ASSERT_EQUAL_HEX16(0x0000, id.AAAEQT[1]);
}

TEST(Flash, EraseSuspendAndResume_EraseComplete)
{
    MockIO_Expect_Write(CommandRegister, ProgramEraseSuspendCommand);
    MockIO_Expect_Write(CommandRegister, ReadStatusCommand);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

    result = Flash_EraseSuspend();

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, EraseSuspendAndResume_EraseSuspended)
{
    MockIO_Expect_Write(CommandRegister, ProgramEraseSuspendCommand);
    MockIO_Expect_Write(CommandRegister, ReadStatusCommand);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | EraseSuspendBit);
    MockIO_Expect_Write(CommandRegister, ReadArrayCommand);

    result = Flash_EraseSuspend();

    LONGS_EQUAL(FLASH_ERASE_SUSPENDED, result);
}

TEST(Flash, EraseSuspendAndResume_SuspendResume)
{
    MockIO_Expect_Write(CommandRegister, ReadStatusCommand);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | EraseSuspendBit);
    MockIO_Expect_Write(CommandRegister, ProgramEraseResumeCommand);

    result = Flash_EraseResume();

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, EraseSuspendAndResume_NoSuspendResume)
{
    MockIO_Expect_Write(CommandRegister, ReadStatusCommand);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit );

    result = Flash_EraseResume();

    LONGS_EQUAL(FLASH_SUCCESS, result);
}