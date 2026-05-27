#include "EmailServiceSpy.h"

#include "string.h"
#include "stdlib.h"

static EMAIL_PACK *spy_email = NULL;
static EMAILSPY_STATUS spy_status = EMPTY_MAIL;

static void EmailService_Clean()
{
    if (spy_email != NULL)
    {
        if (spy_email->to != NULL)
            free(spy_email->to);
        if (spy_email->subject != NULL)
            free(spy_email->subject);
        if (spy_email->body != NULL)
            free(spy_email->body);

        free(spy_email);
        spy_email = NULL;
    }
    spy_status = EMPTY_MAIL;
}

static void EmailService_Copy(EMAIL_PACK email)
{
    size_t len;

    EmailService_Clean();

    spy_email = malloc(sizeof(EMAIL_PACK));
    if (spy_email == NULL)
    {
        goto error;
    }

    len = (strlen(email.to) + 1 > MAX_LEN) ? MAX_LEN : strlen(email.to) + 1;
    spy_email->to = malloc(len * sizeof(char));
    if (spy_email->to == NULL)
    {
        goto error;
    }
    strncpy(spy_email->to, email.to, len);
    spy_email->to[len - 1] = '\0';

    len = (strlen(email.subject) + 1 > MAX_LEN) ? MAX_LEN : strlen(email.subject) + 1;
    spy_email->subject = malloc(len * sizeof(char));
    if (spy_email->subject == NULL)
    {
        goto error;
    }
    strncpy(spy_email->subject, email.subject, len);
    spy_email->subject[len - 1] = '\0';

    len = (strlen(email.body) + 1 > MAX_LEN) ? MAX_LEN : strlen(email.body) + 1;
    spy_email->body = malloc(len * sizeof(char));
    if (spy_email->body == NULL)
    {
        goto error;
    }
    strncpy(spy_email->body, email.body, len);
    spy_email->body[len - 1] = '\0';

    return;
error:
    EmailService_Clean();
    return;
}

void EmailService_Create(void)
{
    spy_email = NULL;
}

void EmailService_Destroy(void)
{
    EmailService_Clean();
}

EMAILSPY_STATUS EmailServiceSpy_GetEmail(EMAIL_PACK **email)
{
    *email = spy_email;

    return spy_status;
}

void EmailService_Send(EMAIL_PACK email)
{
    EmailService_Copy(email);
    spy_status = RECV_MAIL;
}