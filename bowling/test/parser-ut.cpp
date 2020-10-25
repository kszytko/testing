#include <gtest/gtest.h>
#include "frameParser.hpp"

using stringParsedFrameVector = std::vector<std::pair<std::string, parsedFrame>>;

const stringParsedFrameVector testingValuesParse = {
    {"7/|9-|X|-8|8/|-6|X|X|X||81", {7, 3, 9, 0, 10, 0, 8, 8, 2, 0, 6, 10, 10, 10, 8, 1}},
    {"7/|9-|X|-8|8/", {7, 3, 9, 0, 10, 0, 8, 8, 2}},
    {"8/|9-|X|-8|8/", {8, 2, 9, 0, 10, 0, 8, 8, 2}},
};

class FrameParserSuite : public testing::TestWithParam<std::pair<std::string, parsedFrame>> {};

TEST_P(FrameParserSuite, TestParseProducesPairWithNameAndNumericValuesVectorOfTrials) {
    auto [param, expected] = GetParam();
    ASSERT_EQ(FrameParser::parse(param), expected);
}

INSTANTIATE_TEST_SUITE_P(FrameParserTestGroup, FrameParserSuite, testing::ValuesIn(testingValuesParse));

//---------------------------------------------------------

using laneStringAndSequenceCompletenessFlag = std::vector<std::pair<std::string, bool>>;

const laneStringAndSequenceCompletenessFlag testingValuesCompleteness = {{"7/|9-|X|-8|8/|-6|X|X|X||81", true},
                                                                         {"7/|9-|X|-8|8/|-6|X|X|X||8", false},
                                                                         {"7/|9-|X|-8|8/|-6|X|X|X||", false},
                                                                         {"7/|9-|X|-8|8/|-6|X|X|8/||2", true},
                                                                         {"7/|9-|X|-8|8/|-6|X|X|8/||", false},
                                                                         {"7/|9-|X|-8|8/|-6|X|X|82||", true},
                                                                         {"7/|9-|X|-8|8/", false},
                                                                         {"8/|9-|X|-8|8/", false}};

class SequenceCompletenessSuite : public testing::TestWithParam<std::pair<std::string, bool>> {};

TEST_P(SequenceCompletenessSuite, TestChecksSequencesCompleteness) {
    auto [param, expected] = GetParam();
    ASSERT_EQ(FrameParser::isSequenceComplete(param), expected);
}

INSTANTIATE_TEST_SUITE_P(SequenceCompletenessTestGroup,
                         SequenceCompletenessSuite,
                         testing::ValuesIn(testingValuesCompleteness));
