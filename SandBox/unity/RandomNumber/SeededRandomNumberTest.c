#include "unity_fixture.h"

#include "SeededRandomNumber.h"

TEST_GROUP(SeededRandomNumber);

static RandomNumber seededRandomNumber;

TEST_SETUP(SeededRandomNumber)
{
    seededRandomNumber = SeededRandomNumber_Create(1);
}

TEST_TEAR_DOWN(SeededRandomNumber)
{
    RandomNumber_Destroy(seededRandomNumber);
}

TEST(SeededRandomNumber, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(SeededRandomNumber, Get)
{
    LONGS_EQUAL(476707713, RandomNumber_Get(seededRandomNumber));
}