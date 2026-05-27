#ifndef D_EMAILSERVICESPY_H
#define D_EMAILSERVICESPY_H

#include "EmailService.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_LEN 512

typedef enum EMAILSPY_STATUS {
    EMPTY_MAIL = 0,
    RECV_MAIL,
} EMAILSPY_STATUS;

EMAILSPY_STATUS EmailServiceSpy_GetEmail(EMAIL_PACK **email);

#endif /* D_EMAILSERVICESPY_H */