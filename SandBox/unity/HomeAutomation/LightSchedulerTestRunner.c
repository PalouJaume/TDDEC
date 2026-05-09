#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightScheduler)
{
    //RUN_TEST_CASE(LightScheduler, StartHere);
    RUN_TEST_CASE(LightScheduler, NoChangeToLightsDuringInitialization);
    RUN_TEST_CASE(LightScheduler, NoScheduleNothingHappens);
    RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayNotTimeYet);
    RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOffEverydayItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleTuesdayButItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleTuesdayAndItsTuesday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsFriday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSaturday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSunday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekDayItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleTwoEventsAtTheSameTime);
    RUN_TEST_CASE(LightScheduler, RejectsTooManyEvents);
    RUN_TEST_CASE(LightScheduler, RemoveRecyclesScheduleSlot);
    RUN_TEST_CASE(LightScheduler, RemoveMultipleScheduledEvent);
    RUN_TEST_CASE(LightScheduler, AcceptsValidLightIds);
    RUN_TEST_CASE(LightScheduler, RejectsInvalidLightIds);

    RUN_TEST_CASE(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm);
    RUN_TEST_CASE(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm);
}