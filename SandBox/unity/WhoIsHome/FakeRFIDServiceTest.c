#include "unity_fixture.h"

#include "FakeRFIDService.h"

TEST_GROUP(FakeRFIDService);

TEST_SETUP(FakeRFIDService)
{
}

TEST_TEAR_DOWN(FakeRFIDService)
{
}

TEST(FakeRFIDService, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(FakeRFIDService, GenerateOneEvent)
{
    RFID_EVENT evt;
    evt = FakeRFIDService_GetEvent(23241, IN_RANGE);

    LONGS_EQUAL(1, evt.id);
    LONGS_EQUAL(IN_RANGE, evt.kind);
}