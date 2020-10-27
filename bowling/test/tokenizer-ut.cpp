#include <gtest/gtest.h>
#include "tokenizer.hpp"

using StringPairVector = std::vector<std::pair<std::string, std::string>>;

const StringPairVector testingValuesGetSequence = {{"7/|9-|X|-8|8/|-6|X|X|X||", "7/9-X-88/-6XXX"},
                                                   {"7/|9-|X|-8|8/", "7/9-X-88/"},
                                                   {"X|X|X||", "XXX"}};

class GetSeqSuite : public testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(GetSeqSuite, TestReadSequenceReturnsStringWithoutNameAndDelimiter) {
    auto [param, expected] = GetParam();
    ASSERT_EQ(Tokenizer::readSequence(param), expected);
}

INSTANTIATE_TEST_SUITE_P(TokenizerTestGroup, GetSeqSuite, testing::ValuesIn(testingValuesGetSequence));
