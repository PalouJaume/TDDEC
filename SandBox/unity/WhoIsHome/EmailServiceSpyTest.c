#include "unity_fixture.h"

#include "EmailServiceSpy.h"

TEST_GROUP(EmailServiceSpy);

static void checkEmail(EMAILSPY_STATUS status, char *to, char *subject, char *body)
{
    EMAIL_PACK *recv_email = NULL;
    LONGS_EQUAL(status, EmailServiceSpy_GetEmail(&recv_email));
    if (status != EMPTY_MAIL)
    {
        STRCMP_EQUAL(to, recv_email->to);
        STRCMP_EQUAL(subject, recv_email->subject);
        STRCMP_EQUAL(body, recv_email->body);
    }
}

TEST_SETUP(EmailServiceSpy)
{
    EmailService_Create();
}

TEST_TEAR_DOWN(EmailServiceSpy)
{
    EmailService_Destroy();
}

TEST(EmailServiceSpy, StartHere)
{
    // TEST_FAIL_MESSAGE("Start Here");
}

TEST(EmailServiceSpy, Create)
{
    checkEmail(EMPTY_MAIL, NULL, NULL, NULL);
}

TEST(EmailServiceSpy, Get)
{
    EMAIL_PACK email = {.to = "Eduardo",
                        .subject = "Update",
                        .body = "1234"};

    EmailService_Send(email);

    checkEmail(RECV_MAIL, "Eduardo", "Update", "1234");
}