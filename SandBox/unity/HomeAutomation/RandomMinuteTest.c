#include "unity_fixture.h"

#include "stdlib.h"
#include "string.h"

#include "RandomMinute.h"

TEST_GROUP(RandomMinute);

enum
{
    BOUND = 30
};

int minute;

void AssertMinuteIsInRange(void)
{
    if (minute < -BOUND || minute > BOUND)
    {
        printf("bad minute value: %d\n", minute);
        TEST_FAIL_MESSAGE("Minute out of range");
    }
}

TEST_SETUP(RandomMinute)
{
    RandomMinute_Create(BOUND);
    srand(1);
}

TEST_TEAR_DOWN(RandomMinute)
{
}

TEST(RandomMinute, GetIsInRange)
{
    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
    }
}

TEST(RandomMinute, AllValuesPossible)
{
    int hit[2 * BOUND + 1];
    memset(hit, 0, sizeof(hit));
    int i;
    for(i = 0; i < 400; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
        hit[minute + BOUND]++;
    }
    for (i = 0; i < 2* BOUND + 1; i++)
    {
        CHECK(hit[i] > 0);
    }
}