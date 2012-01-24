#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "doubleuplogic.h"

class MockDoubleupChoiceResult : public DoubleupChoiceResult
{
public:
    MOCK_METHOD1(DoubleUp, void(bool doubleup));
};

class DoubleUpLogicTest : public ::testing::Test
{
public:
    DoubleUpLogicTest() {
        userEventsInterface = &logic;
        userEventsInterface->DoesUserWantToDoubleUp(result);
    }    

    DoubleUpLogic logic;
    UserEvents* userEventsInterface;
    MockDoubleupChoiceResult result;    
};

TEST_F(DoubleUpLogicTest, active_query_doubleup)
{
    EXPECT_CALL(result, DoubleUp(true)).Times(1);
    EXPECT_CALL(result, DoubleUp(false)).Times(0);
    
    logic.DoubleUp();
}

TEST_F(DoubleUpLogicTest, active_query_doubleup_resets_on_result)
{
    EXPECT_CALL(result, DoubleUp(true)).Times(1);
    EXPECT_CALL(result, DoubleUp(false)).Times(0);
    
    logic.DoubleUp();
    logic.CashOut();
}

TEST_F(DoubleUpLogicTest, active_query_cashout)
{
    EXPECT_CALL(result, DoubleUp(true)).Times(0);
    EXPECT_CALL(result, DoubleUp(false)).Times(1);
    
    logic.CashOut();
}

TEST_F(DoubleUpLogicTest, active_query_cashout_resets_on_result)
{
    EXPECT_CALL(result, DoubleUp(true)).Times(0);
    EXPECT_CALL(result, DoubleUp(false)).Times(1);
    
    logic.CashOut();
    logic.DoubleUp();
}
