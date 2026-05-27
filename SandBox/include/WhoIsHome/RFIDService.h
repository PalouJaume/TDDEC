#ifndef D_RFIDSERVICE_H
#define D_RFIDSERVICE_H

typedef enum RFID_EVENT_TYPE
{
    IN_RANGE = 0,
    OUT_RANGE = 1,
    UNKNOWN
} RFID_EVENT_TYPE;

typedef struct RFID_EVENT
{
    int id;
    RFID_EVENT_TYPE kind;
} RFID_EVENT;

#endif /* D_RFIDSERVICE_H */