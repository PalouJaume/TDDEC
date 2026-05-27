#ifndef D_EMAILSERVICE_H
#define D_EMAILSERVICE_H

#define MAX_SUBJECT_LEN 256
#define MAX_BODY_LEN 100

typedef struct EMAIL_PACK
{
    char *to;
    char *subject;
    char *body;
} EMAIL_PACK;

void EmailService_Create();
void EmailService_Destroy();
void EmailService_Send(EMAIL_PACK email);

#endif /* D_EMAILSERVICE_H */