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

#include "unity_fixture.h"
#include "LedDriver.h"
#include "stdint.h"

#include "unity_fixture.h"
#include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver);
static uint16_t virtualLeds;

#define LOGIC_TYPE NORMAL_LOGIC
#define LED_ORDER  REVERSE_ORDER

static uint16_t reverse_order(uint16_t value)
{
    uint16_t res = 0;
    for(unsigned i = 0; i < sizeof(uint16_t)*8; i++)
    {
        if (value & (1 << i))
            res |= 1 << ((sizeof(uint16_t)*8 - 1) - i);
    }

    return res;
}

static uint16_t result(uint16_t expected)
{
    uint16_t res = 0x0000;

    if(LED_ORDER == REVERSE_ORDER)
        res = reverse_order(expected);
    else 
        res = expected; 

    return (LOGIC_TYPE == NORMAL_LOGIC) ? res : (uint16_t)~res;
}

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&virtualLeds, LOGIC_TYPE, LED_ORDER);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, StartHere)
{
   //TEST_FAIL_MESSAGE("Start here");
   //TEST_ASSERT_EQUAL_HEX16(0x8000, reverse_order(0x0001));
}

TEST(LedDriver, LedsOffAfterCreate)
{
    uint16_t virtualleds = 0xffff;
    LedDriver_Create(&virtualleds, LOGIC_TYPE, LED_ORDER);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualleds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(
         result(0x0001),
         virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
    LedDriver_TurnOn(9); // virtualLeds <= 16'b0000_0001_0000_0000
    LedDriver_TurnOn(8); // virtualLeds <= 16'b0000_0001_1000_0000
    TEST_ASSERT_EQUAL_HEX16(
         result(0x180),
         virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(
        result(0xff7f),
         virtualLeds);
}

TEST(LedDriver, AllOn)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(
         result(0xffff),
         virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
    virtualLeds = 0xffff;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0080),
         virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x8001),
         virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
    LedDriver_TurnOn(0);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
    LedDriver_TurnOn(17);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
    LedDriver_TurnOn(33);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffChangesNothing)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    TEST_ASSERT_EQUAL_HEX16(
        result(0xffff),
         virtualLeds);
    LedDriver_TurnOff(17);
    TEST_ASSERT_EQUAL_HEX16(
        result(0xffff),
         virtualLeds);
    LedDriver_TurnOff(33);
    TEST_ASSERT_EQUAL_HEX16(
        result(0xffff),
         virtualLeds);    
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(
        result(0xffff),
         virtualLeds);    
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", 
            RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
    /* TODO: what should we do during runtime? */
}

TEST(LedDriver, IsOn)
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsOff(17));
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff)
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(12));
    LedDriver_TurnOn(12);
    TEST_ASSERT_FALSE(LedDriver_IsOff(12));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(
        result((~0x0180)&0xffff),
         virtualLeds);
}

TEST(LedDriver, AllOff)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(
        result(0x0000),
         virtualLeds);    
}