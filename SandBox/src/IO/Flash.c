#include "Flash.h"

static FLASH_STATUS writeError(ioData status)
{
    IO_Write(CommandRegister, Reset);

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