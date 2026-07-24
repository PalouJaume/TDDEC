#ifndef D_M28W160ECT_H
#define D_M28W160ECT_H

#define FLASH_WRITE_TIMEOUT_IN_MICROSENDS 3000

typedef enum
{
    CommandRegister = 0x0,
    StatusRegister = 0x0
} Flash_Registers;

typedef enum
{
    ProgramCommand = 0x40,
	ReadArrayCommand = 0xFF,
	EraseSetupCommand = 0x20,
	EraseConfirmCommand = 0xD0,
	ProgramEraseSuspendCommand = 0xB0,
	ProgramEraseResumeCommand = 0xD0,
	ReadStatusCommand = 0x70,
	ClearStatusCommand = 0x50,
	CFIQueryCommand = 0x98
} Flash_Command;

typedef enum
{
	ReadyBit = 1<<7,
	EraseSuspendBit = 1<<6,
	EraseErrorBit = 1<<5,
	ProgramErrorBit = 1<<4,
	VppErrorBit = 1<<3,
	ProgramSuspendBit = 1<<2,
	BlockProtectionErrorBit = 1<<1,
	ReservedBit = 1
} StatusRegisterBits;

typedef enum
{
	ANY_ADDRESS = 0xFF,
} Addresses;

#endif /* D_M28W160ECT_H */