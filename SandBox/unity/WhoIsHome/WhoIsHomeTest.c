#include "unity_fixture.h"

#include "WhoIsHome.h"
#include "FakeRFIDService.h"
#include "EmailServiceSpy.h"

#include "stdlib.h"

TEST_GROUP(WhoIsHome);

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

TEST_SETUP(WhoIsHome)
{
    EmailService_Create();
    WhoIsHome_Create();
}

TEST_TEAR_DOWN(WhoIsHome)
{
    EmailService_Destroy();
}

TEST(WhoIsHome, StartHere)
{
    // TEST_FAIL_MESSAGE("Start Here");
}

TEST(WhoIsHome, Create)
{
    checkEmail(EMPTY_MAIL, NULL, NULL, NULL);
}

TEST(WhoIsHome, RFIDEventInRange)
{
    RFID_EVENT event = FakeRFIDService_GetEvent(12, IN_RANGE);

    WhoIsHome_Update(&event, 1);

    checkEmail(RECV_MAIL, "edu.nopersonal@gmail.com",
               "1 RFID in range, 0 RFID out range",
               "IN RANGE RFIDs: 12\n OUT RANGE RFIDs: None");
}

TEST(WhoIsHome, RFIDEventOutRange)
{
    RFID_EVENT event = FakeRFIDService_GetEvent(12, OUT_RANGE);

    WhoIsHome_Update(&event, 1);

    checkEmail(RECV_MAIL, "edu.nopersonal@gmail.com",
               "0 RFID in range, 1 RFID out range",
               "IN RANGE RFIDs: None\n OUT RANGE RFIDs: 12");
}

TEST(WhoIsHome, REFIDEventsInRangeOutRange)
{
    RFID_EVENT event[2];

    event[0] = FakeRFIDService_GetEvent(12, IN_RANGE);
    event[1] = FakeRFIDService_GetEvent(13, OUT_RANGE);

    WhoIsHome_Update(event, 2);

    checkEmail(RECV_MAIL, "edu.nopersonal@gmail.com",
               "1 RFID in range, 1 RFID out range",
               "IN RANGE RFIDs: 12\n OUT RANGE RFIDs: 13");    
}
