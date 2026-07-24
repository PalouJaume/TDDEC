#include "Flash.h"

static FLASH_STATUS writeError(ioData status)
{
    IO_Write(CommandRegister, ReadArrayCommand);

    if (status & VppErrorBit)
        return FLASH_VPP_ERROR;

    if (status & ProgramErrorBit)
        return FLASH_PROGRAM_ERROR;

    if (status & BlockProtectionErrorBit)
        return FLASH_PROTECTED_BLOCK_ERROR;

    return FLASH_UNKNOWN_PROGRAM_ERROR;
}

void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

int Flash_Write(ioAddress address, ioData data)
{
    ioData status = 0;
    uint32_t timestamp = MicroTime_Get();

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
    {
        uint32_t cur = MicroTime_Get();

        if ((cur - timestamp >= FLASH_WRITE_TIMEOUT_IN_MICROSENDS) || (cur < timestamp))
            return FLASH_TIMEOUT_ERROR;

        status = IO_Read(StatusRegister);
    }

    if (status != ReadyBit)
        return writeError(status);

    if (data != IO_Read(address))
        return FLASH_READ_BACK_ERROR;

    return FLASH_SUCCESS;
}

int Flash_CFI_Identification(struct cfi_IdentificationString *id)
{
    IO_Write(CommandRegister, CFIQueryCommand);

    id->MC = IO_Read(0x00);
    id->DC = IO_Read(0x01);

    id->QUAS[0] = IO_Read(0x10);
    id->QUAS[1] = IO_Read(0x11);
    id->QUAS[2] = IO_Read(0x12);

    id->PACSCII[0] = IO_Read(0x13);
    id->PACSCII[1] = IO_Read(0x14);

    id->APAEQT[0] = IO_Read(0x15);
    id->APAEQT[1] = IO_Read(0x16);

    id->AVCSCIIC[0] = IO_Read(0x17);
    id->AVCSCIIC[1] = IO_Read(0x18);

    id->AAAEQT[0] = IO_Read(0x19);
    id->AAAEQT[1] = IO_Read(0x1A);

    IO_Write(CommandRegister, ReadArrayCommand);

    return FLASH_SUCCESS;
}

int Flash_EraseSuspend(void)
{
    ioData status = 0;
    uint32_t timestamp = MicroTime_Get();

    IO_Write(CommandRegister, ProgramEraseSuspendCommand);
    IO_Write(CommandRegister, ReadStatusCommand);
    do
    {
        uint32_t cur = MicroTime_Get();
        if ((cur - timestamp >= FLASH_WRITE_TIMEOUT_IN_MICROSENDS) || (cur < timestamp))
            return FLASH_TIMEOUT_ERROR;

        status = IO_Read(StatusRegister);
    } while ((status & ReadyBit) == 0);

    IO_Write(CommandRegister, ReadArrayCommand);

    return (status & EraseSuspendBit) == 0 ? FLASH_SUCCESS : FLASH_ERASE_SUSPENDED;
}

int Flash_EraseResume(void)
{
    ioData status = 0;

    IO_Write(CommandRegister, ReadStatusCommand);
    status = IO_Read(StatusRegister);

    if (status & EraseSuspendBit)
        IO_Write(CommandRegister, ProgramEraseResumeCommand);

    return FLASH_SUCCESS;
}