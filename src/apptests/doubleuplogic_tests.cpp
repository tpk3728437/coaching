#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "doubleuplogic.h"

class MockDoubleupChoiceResult : public DoubleupChoiceResult
{
public:
    MOCK_METHOD1(doubleUp, void(bool doubleup));
};

class DoubleUpLogicTest : public ::testing::Test
{
public:
    DoubleUpLogicTest() {
        userEventsInterface = &logic;
        userEventsInterface->doesUserWantToDoubleUp(result);
    }    

    DoubleUpLogic logic;
    UserEvents* userEventsInterface;
    MockDoubleupChoiceResult result;    
};

TEST_F(DoubleUpLogicTest, active_query_doubleup)
{
    EXPECT_CALL(result, doubleUp(true)).Times(1);
    EXPECT_CALL(result, doubleUp(false)).Times(0);
    
    logic.doubleUp();
}

TEST_F(DoubleUpLogicTest, active_query_doubleup_resets_on_result)
{
    EXPECT_CALL(result, doubleUp(true)).Times(1);
    EXPECT_CALL(result, doubleUp(false)).Times(0);
    
    logic.doubleUp();
    logic.cashOut();
}

TEST_F(DoubleUpLogicTest, active_query_cashout)
{
    EXPECT_CALL(result, doubleUp(true)).Times(0);
    EXPECT_CALL(result, doubleUp(false)).Times(1);
    
    logic.cashOut();
}

TEST_F(DoubleUpLogicTest, active_query_cashout_resets_on_result)
{
    EXPECT_CALL(result, doubleUp(true)).Times(0);
    EXPECT_CALL(result, doubleUp(false)).Times(1);
    
    logic.cashOut();
    logic.doubleUp();
}
