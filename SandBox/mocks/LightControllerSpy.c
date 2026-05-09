#include "LightControllerSpy.h"

static int lastId;
static int lastState;
static int lights[128];

void LightController_Create(void)
{
    lastId = LIGHT_STATE_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    
    for (int i = 0; i < 128; i++)
    {
        lights[i] = LIGHT_STATE_UNKNOWN;
    }
}

void LightController_Destroy(void)
{
}

void LightController_On(int id)
{
    lights[id] = LIGHT_ON;
    lastId = id;
    lastState = LIGHT_ON;
}

void LightController_Off(int id)
{
    lights[id] = LIGHT_OFF;
    lastId = id;
    lastState = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
    return lights[id];
}