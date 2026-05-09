#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#define MAX_EVENTS 128

enum Day
{
    NONE = -1,
    EVERYDAY = 10,
    WEEKDAY,
    WEEKEND,
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

typedef enum Day Day;

typedef enum ID_STATUS
{
    UNUSED = -1
} ID_STATUS;

typedef enum EVENT_TYPE
{
    TURN_ON,
    TURN_OFF,
} EVENT_TYPE;

typedef enum RES_STATUS
{
    LS_OK = 0,
    LS_ID_OUT_OF_BOUNDS,
    LS_TOO_MANY_EVENTS = -1
} RES_STATUS;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
RES_STATUS LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
RES_STATUS LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_RemoveSchedule(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);

#endif /* D_LightScheduler_H */