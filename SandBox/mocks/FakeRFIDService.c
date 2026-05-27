#include "FakeRFIDService.h"

RFID_EVENT FakeRFIDService_GetEvent(int id, RFID_EVENT_TYPE kind)
{
    RFID_EVENT event = {.id = id, .kind = kind};

    return event;
}