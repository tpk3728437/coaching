#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "headsortailsgame.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using ::testing::Invoke;


class HeadsOrTailsGameTest : public ::testing::Test
{
public:

public:
};

TEST_F(HeadsOrTailsGameTest, lose_with_two_tails)
{    
}
