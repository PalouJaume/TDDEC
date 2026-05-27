#ifndef D_WHOISHOME_H
#define D_WHOISHOME_H

#include "RFIDService.h"
#include "EmailService.h"

#define EMAIL_MANAGER "edu.nopersonal@gmail.com"

void WhoIsHome_Create(void);
void WhoIsHome_Destroy(void);
void WhoIsHome_Update(RFID_EVENT *events, int eventc);

#endif /* D_WHOISHOME_H */