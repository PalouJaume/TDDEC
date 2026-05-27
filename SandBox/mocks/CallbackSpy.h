#ifndef D_CALLBACKSPY_H
#define D_CALLBACKSPY_H

typedef enum CALLBACK_STATUS
{
    CALLBACK_NOEXECUTED = -1,
    CALLBACK_EXECUTED = 1,
} CALLBACK_STATUS;

void CallbackSpy_Create(void);
void CallbackSpy_Destroy(void);
void CallbackSpy_Run(void);
CALLBACK_STATUS CallbackSpy_GetStatus(void);

#endif /* D_CALLBACKSPY_H */