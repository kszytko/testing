#include <gtest/gtest.h>
#include "frameParser.hpp"

using stringParsedFrameVector = std::vector<std::pair<std::string, parsedFrame>>;

const stringParsedFrameVector testingValuesParse = {
    {"Andrzej:7/|9-|X|-8|8/|-6|X|X|X||81", {"Andrzej", {7, 3, 9, 0, 10, 0, 8, 8, 2, 0, 6, 10, 10, 10, 8, 1}}},
    {"Janusz:7/|9-|X|-8|8/", {"Janusz", {7, 3, 9, 0, 10, 0, 8, 8, 2}}},
    {":8/|9-|X|-8|8/", {"", {8, 2, 9, 0, 10, 0, 8, 8, 2}}},
};

class FrameParserSuite : public testing::TestWithParam<std::pair<std::string, parsedFrame>> {};

TEST_P(FrameParserSuite, TestParseProducesPairWithNameAndNumericValuesVectorOfTrials) {
    auto [param, expected] = GetParam();
    ASSERT_EQ(FrameParser::parse(param), expected);
}

INSTANTIATE_TEST_SUITE_P(FrameParserTestGroup, FrameParserSuite, testing::ValuesIn(testingValuesParse));
