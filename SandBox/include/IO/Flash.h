#ifndef D_FLASH_H
#define D_FLASH_H

#include "IO.h"
#include "m28w160ect.h"
#include "MicroTime.h"

typedef enum
{
    FLASH_SUCCESS,
    FLASH_ERROR,
    FLASH_VPP_ERROR,
    FLASH_PROGRAM_ERROR,
    FLASH_PROTECTED_BLOCK_ERROR,
    FLASH_READ_BACK_ERROR,
    FLASH_UNKNOWN_PROGRAM_ERROR,
    FLASH_TIMEOUT_ERROR,
    FLASH_ERASE_SUSPENDED = 8
} FLASH_STATUS;

struct cfi_IdentificationString
{
    uint16_t MC;
    uint16_t DC;
    uint16_t QUAS[3];
    uint16_t PACSCII[2];
    uint16_t APAEQT[2];
    uint16_t AVCSCIIC[2];
    uint16_t AAAEQT[2];
};

void Flash_Create(void);
void Flash_Destroy(void);

int Flash_Write(ioAddress address, ioData data);
int Flash_CFI_Identification(struct cfi_IdentificationString *id);
int Flash_EraseSuspend(void);
int Flash_EraseResume(void);

#endif /* D_FLASH_H */