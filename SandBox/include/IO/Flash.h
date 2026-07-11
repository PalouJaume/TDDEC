#ifndef D_FLASH_H
#define D_FLASH_H

#include "IO.h"
#include "m28w160ect.h"
#include "MicroTime.h"

typedef enum
{
    FLASH_SUCCESS = 0,
    FLASH_ERROR = 1,
    FLASH_VPP_ERROR = 2,
    FLASH_PROGRAM_ERROR = 3,
    FLASH_PROTECTED_BLOCK_ERROR = 4,
    FLASH_READ_BACK_ERROR = 5,
    FLASH_UNKNOWN_PROGRAM_ERROR = 6,
    FLASH_TIMEOUT_ERROR = 7,
} FLASH_STATUS;

void Flash_Create(void);
void Flash_Destroy(void);

int Flash_Write(ioAddress address, ioData data);

#endif /* D_FLASH_H */