#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(LightScheduler);
    RUN_TEST_GROUP(TimeService);
}

int main(int ac, char* av[])
{
    return UnityMain(ac, av, RunAllTests);
}