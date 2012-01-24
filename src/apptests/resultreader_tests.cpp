#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "resultreader.h"
#include <sstream>

TEST(ResultReaderTest, read_empty_stream)
{
    std::stringstream ss;
    ResultReader reader(ss);
    EXPECT_EQ(0, reader.results().size());
}

TEST(ResultReaderTest, read_one_tail)
{
    std::stringstream input;
    input << "tail";
    ResultReader reader(input);
    EXPECT_EQ(1, reader.results().size());
    EXPECT_EQ("tail", reader.results()[0]);
}

TEST(ResultReaderTest, read_two_tails)
{
    std::stringstream input;
    input << "tail\ntail";
    ResultReader reader(input);
    EXPECT_EQ(2, reader.results().size());
    EXPECT_EQ("tail", reader.results()[0]);
    EXPECT_EQ("tail", reader.results()[1]);
}

TEST(ResultReaderTest, read_head_tail_tail)
{
    std::stringstream input;
    input << "head\ntail\ntail";
    ResultReader reader(input);
    EXPECT_EQ(3, reader.results().size());
    EXPECT_EQ("head", reader.results()[0]);
    EXPECT_EQ("tail", reader.results()[1]);
    EXPECT_EQ("tail", reader.results()[2]);
}

TEST(ResultReaderTest, invalid_input)
{
	std::stringstream input;
	input << "foo\nbar";
	ResultReader reader(input);
	EXPECT_EQ(0, reader.results().size());
}
