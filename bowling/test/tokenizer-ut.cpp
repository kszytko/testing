#include <gtest/gtest.h>
#include "tokenizer.hpp"

using StringPairVector = std::vector<std::pair<std::string, std::string>>;

const StringPairVector testingValuesGetName = {{"Andrzej:7/|9-|X|-8|8/|-6|X|X|X||", "Andrzej"},
                                               {"Janusz:7/|9-|X|-8|8/|-6|X|X|X||", "Janusz"},
                                               {":7/|9-|X|-8|8/|-6|X|X|X||", ""},
                                               {"7/|9-|X|-8|8/|-6|X|X|X||", ""}};

const StringPairVector testingValuesGetSequence = {{"Andrzej:7/|9-|X|-8|8/|-6|X|X|X||", "7/9-X-88/-6XXX"},
                                                   {"Janusz:7/|9-|X|-8|8/", "7/9-X-88/"},
                                                   {":7/|9-", "7/9-"},
                                                   {":X|X|X||", "XXX"}};

class GetNameSuite : public testing::TestWithParam<std::pair<std::string, std::string>> {};
class GetSeqSuite : public testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(GetNameSuite, TestReadNameReturnsPartOfTheStringToColonSign) {
    size_t pos = 0;
    auto [param, expected] = GetParam();
    ASSERT_EQ(Tokenizer::readName(param, pos), expected);
}

TEST_P(GetSeqSuite, TestReadSequenceReturnsStringWithoutNameAndDelimiter) {
    auto [param, expected] = GetParam();
    size_t pos = 0;
    size_t next = param.find(":");
    pos = next;

    ASSERT_EQ(Tokenizer::readSequence(param, pos), expected);
}

INSTANTIATE_TEST_SUITE_P(TokenizerTestGroup, GetNameSuite, testing::ValuesIn(testingValuesGetName));
INSTANTIATE_TEST_SUITE_P(TokenizerTestGroup, GetSeqSuite, testing::ValuesIn(testingValuesGetSequence));
