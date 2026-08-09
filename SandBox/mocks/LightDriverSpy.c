/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
 ***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include <stdlib.h>
#include <memory.h>
#include "LightDriverSpy.h"
#include "common.h"

typedef struct LightDriverSpyStruct *LightDriverSpy;
typedef struct LightDriverSpyStruct
{
    LightDriverStruct base;
} LightDriverSpyStruct;

static void LightDriverSpy_TurnOn(LightDriver super);
static void LightDriverSpy_TurnOff(LightDriver super);
static void LightDriverSpy_Destroy(LightDriver super);
static void LightDriverSpy_Brighten(LightDriver super);
static void LightDriverSpy_Dim(LightDriver super);
static void LightDriverSpy_Strobe(LightDriver super);

static LightDriverInterfaceStruct interface =
    {
        .TurnOn = LightDriverSpy_TurnOn,
        .TurnOff = LightDriverSpy_TurnOff,
        .Destroy = LightDriverSpy_Destroy,
        .Brighten = LightDriverSpy_Brighten,
        .Dim = LightDriverSpy_Dim,
        .Strobe = LightDriverSpy_Strobe,
};

static LightDriverInterfaceStruct partial_interface =
    {
        .TurnOn = LightDriverSpy_TurnOn,
        .TurnOff = LightDriverSpy_TurnOff,
        .Destroy = LightDriverSpy_Destroy,
        .Strobe = LightDriverSpy_Strobe,
};

static int states[MAX_LIGHTS];
static int brightLevels[MAX_LIGHTS];
static int lastId;
static int lastState;

void LightDriverSpy_Reset(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        states[i] = LIGHT_STATE_UNKNOWN;
        brightLevels[i] = DEFAULT_BRIGHT_LEVEL;
    }

    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightDriverSpy_AddSpiesToController(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver spy = (LightDriver)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
}

static LightDriver create(int id, LightDriverInterface i)
{
    LightDriverSpy self = calloc(1, sizeof(LightDriverSpyStruct));
    self->base.vtable = i;
    self->base.type = "Spy";
    self->base.id = id;
    return (LightDriver)self;
}

LightDriver LightDriverSpy_Create(int id)
{
    return create(id, &interface);
}

LightDriver LightDriverSpy_PartialCreate(int id)
{
    return create(id, &partial_interface);
}

static void LightDriverSpy_Destroy(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    states[self->base.id] = LIGHT_STATE_UNKNOWN;
    brightLevels[self->base.id] = DEFAULT_BRIGHT_LEVEL;
    free(self);
}

static void save(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}

static void LightDriverSpy_TurnOn(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_ON);
}

static void LightDriverSpy_TurnOff(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_OFF);
}

static void LightDriverSpy_Brighten(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    int id = self->base.id;

    brightLevels[id] += brightLevels[id] < 100 ? 10 : 0;
}

static void LightDriverSpy_Dim(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    int id = self->base.id;

    brightLevels[id] -= brightLevels[id] > 0 ? 10 : 0;
}

static void LightDriverSpy_Strobe(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_STROBE);
}

int LightDriverSpy_GetState(int id)
{
    return states[id];
}

int LightDriverSpy_GetBright(int id)
{
    return brightLevels[id];
}

int LightDriverSpy_GetLastId(void)
{
    return lastId;
}

int LightDriverSpy_GetLastState(void)
{
    return lastState;
}
