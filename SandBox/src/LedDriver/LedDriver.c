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

#include "LedDriver.h"
#include "RuntimeError.h"

#include <stdlib.h>
#include <memory.h>

static uint16_t* ledsAddress;
static uint16_t ledsImage;
static enum LOGIC_TYPE logicType;
static enum LED_ORDER orderType;

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {FIRST_LED = 1, LAST_LED = 16};

static BOOL IsLedOutOfBounds(int ledNumber)
{
    return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}

static uint16_t convertLedNumberToBit(int ledNumber)
{

    return (orderType == NORMAL_ORDER) ? 1 << (ledNumber - 1) : 1 << (sizeof(uint16_t)*8 - 1 - ledNumber + 1);
}

static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}

static void setLedImageBit(int ledNumber)
{
    if (logicType == NORMAL_LOGIC)
        ledsImage |= convertLedNumberToBit(ledNumber);
    else 
        ledsImage &= ~(convertLedNumberToBit(ledNumber)); 
}

static void clearLedImageBit(int ledNumber)
{
    if (logicType == NORMAL_LOGIC)
        ledsImage &= ~(convertLedNumberToBit(ledNumber));
    else 
        ledsImage |= convertLedNumberToBit(ledNumber);
}


void LedDriver_Create(uint16_t* address, enum LOGIC_TYPE logic, enum LED_ORDER order)
{
    ledsAddress = address;
    ledsImage = (logicType == NORMAL_LOGIC) ? ALL_LEDS_OFF : (uint16_t)~ALL_LEDS_OFF;
    logicType = logic;
    orderType = order;
    updateHardware();
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }

    setLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    clearLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = (logicType == NORMAL_LOGIC) ? ALL_LEDS_ON : ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = (logicType == NORMAL_LOGIC) ? ALL_LEDS_OFF : ALL_LEDS_ON;
    updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return (logicType == NORMAL_LOGIC) ? ledsImage & (convertLedNumberToBit(ledNumber)) : !(ledsImage & (convertLedNumberToBit(ledNumber)));
}

BOOL LedDriver_IsOff(int ledNumber)
{
    return !LedDriver_IsOn(ledNumber);
}

