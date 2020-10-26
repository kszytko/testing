#include <gtest/gtest.h>
#include <functional>
#include "filesReader.hpp"

using TestDirectory = std::pair<std::string, bool>;

struct FilesReaderTestFixture : public ::testing::TestWithParam<TestDirectory> {};

TEST_P(FilesReaderTestFixture, ShouldValidateInputDirectory) {
    // GIVEN
    auto [path, isValid] = GetParam();

    if (isValid) {
        // WHEN, THEN
        ASSERT_NO_THROW(FilesReader filesReader(path));
    } else {
        // WHEN, THEN
        ASSERT_THROW(FilesReader filesReader(path), std::invalid_argument);
    }
}

INSTANTIATE_TEST_SUITE_P(SomeDirectories,
                         FilesReaderTestFixture,
                         ::testing::Values(TestDirectory{"nonexistingPath", false},
                                           TestDirectory{"./bin/bowling-ut", false},
                                           TestDirectory{"..", true}));

TEST(FilesReaderTest, ShouldReadFiles) {
    // GIVEN
    std::string inputDirectory = "../test/inputTestDirectory";

    // WHEN
    FilesReader filesReader(inputDirectory);

    // THEN
    auto lanes = filesReader.getLanes();

    EXPECT_EQ(filesReader.getLanesNum(), 3);

    EXPECT_EQ(lanes[0].name_, "lane1");
    EXPECT_EQ(lanes[0].players_.size(), 3);

    EXPECT_EQ(lanes[0].players_[0].name_, "Name1");
    EXPECT_EQ(lanes[0].players_[0].game_, "X|4-|3");

    EXPECT_EQ(lanes[0].players_[1].name_, "Name2");
    EXPECT_EQ(lanes[0].players_[1].game_, "34|X|0-");

    EXPECT_EQ(lanes[0].players_[2].name_, "");
    EXPECT_EQ(lanes[0].players_[2].game_, "X|22|33");

    EXPECT_EQ(lanes[1].name_, "lane2");
    EXPECT_EQ(lanes[1].players_.size(), 0);
    EXPECT_EQ(lanes[2].name_, "lane3");
    EXPECT_EQ(lanes[2].players_.size(), 2);
}
