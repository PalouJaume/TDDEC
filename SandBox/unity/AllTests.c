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

static void RunAllTests(void)
{
    //RUN_TEST_GROUP(LedDriver);
    //RUN_TEST_GROUP(CircularBuffer);
    //RUN_TEST_GROUP(CircularBufferPrint);
    //RUN_TEST_GROUP(BufferFormatter);
    //RUN_TEST_GROUP(LightControllerSpy);
    //RUN_TEST_GROUP(FakeTimeService);
    //RUN_TEST_GROUP(LightScheduler);
    //RUN_TEST_GROUP(FakeClockService);
    //RUN_TEST_GROUP(CallbackSpy);
    //RUN_TEST_GROUP(AlarmClock);
    //RUN_TEST_GROUP(FakeRFIDService);
    //RUN_TEST_GROUP(EmailServiceSpy);
    //RUN_TEST_GROUP(WhoIsHome);
    //RUN_TEST_GROUP(RandomMinute);
    //RUN_TEST_GROUP(LightSchedulerRandomize);
    //RUN_TEST_GROUP(FormatOutputSpy);
    //RUN_TEST_GROUP(Flash);
    //RUN_TEST_GROUP(LightController);
    //RUN_TEST_GROUP(LightDriverSpy);
    //RUN_TEST_GROUP(LightDriver);
    //RUN_TEST_GROUP(Thread);
    RUN_TEST_GROUP(RandomNumber);
    RUN_TEST_GROUP(FakeRandomNumber);
    RUN_TEST_GROUP(SeededRandomNumber);
}

int main(int ac, char* av[])
{
    return UnityMain(ac, av, RunAllTests);
}
