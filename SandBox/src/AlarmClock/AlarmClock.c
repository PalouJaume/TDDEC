#include "AlarmClock.h"
#include "stdlib.h"

#define MAX_EVENTS 10

struct AlarmEvent
{
    int ms;
    AlarmCallback cb;
};

typedef struct AlarmEvent AlarmEvent;

AlarmEvent events[MAX_EVENTS];

void AlarmClock_Create(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        events[i].ms = 0;
        events[i].cb = NULL;
    }
}

void AlarmClock_Destroy(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        events[i].ms = 0;
        events[i].cb = NULL;
    }
}

void AlarmClock_WakeUp(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (events[i].ms == ClockService_Getms())
        {
            events[i].cb();
        }
    }
}

void AlarmClock_SetAlarm(AlarmCallback cb, int ms)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (events[i].cb == NULL)
        {
            events[i].ms = ms;
            events[i].cb = cb;
            return;
        }
    }
}

void AlarmClock_RemoveAlarm(AlarmCallback cb, int ms)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (events[i].cb == cb && events[i].ms == ms)
        {
            events[i].ms = 0;
            events[i].cb = NULL;
        }
    }    
}