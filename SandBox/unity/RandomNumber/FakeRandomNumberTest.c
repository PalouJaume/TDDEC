#include "unity_fixture.h"

#include "FakeRandomNumber.h"

TEST_GROUP(FakeRandomNumber);

RandomNumber fakeRandomNumber;
int randomNumber = 0;

TEST_SETUP(FakeRandomNumber)
{
    fakeRandomNumber = FakeRandomNumber_Create(10, 5);
}

TEST_TEAR_DOWN(FakeRandomNumber)
{
    RandomNumber_Destroy(fakeRandomNumber);
}

TEST(FakeRandomNumber, StartHere)
{
    // TEST_FAIL_MESSAGE("Start Here");
}

TEST(FakeRandomNumber, Get)
{
    randomNumber = RandomNumber_Get(fakeRandomNumber);

    LONGS_EQUAL(10, randomNumber);
}

TEST(FakeRandomNumber, MultipleGets)
{
    RandomNumber_Get(fakeRandomNumber);
    RandomNumber_Get(fakeRandomNumber);
    randomNumber = RandomNumber_Get(fakeRandomNumber);

    LONGS_EQUAL(20, randomNumber);
}
