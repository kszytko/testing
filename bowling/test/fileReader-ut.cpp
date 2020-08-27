#include <gtest/gtest.h>
#include <functional>
#include "LaneReader.hpp"
#include "folderReader.hpp"

using TestDirectory = std::tuple<std::string, bool>;

struct FolderReaderTest : public ::testing::Test
{
    std::string invalidDirectory = "t.e.s.t";
    std::string notExistingDirectory = "notexistingdirectory";
    std::string inputTestDirectory = "C:\\Users\\RWSwiss\\Documents\\workshop\\testing\\bowling\\test\\inputTestDirectory";


    void validatePlayer(Lane::Player & player, std::string name, std::string game) {
        EXPECT_EQ(player.name, name);
        EXPECT_EQ(player.game, game);
    }

};

TEST_F(FolderReaderTest, WhenDirectoryIsInvalid_ShouldThrowError) {
    ASSERT_ANY_THROW(new FolderReader(invalidDirectory));
}

TEST_F(FolderReaderTest, WhenDirectoryNotExists_ShouldThrowError) {
    ASSERT_ANY_THROW(new FolderReader(notExistingDirectory));
}

TEST_F(FolderReaderTest, WhenDirectoryExists_ShouldPass) {
    ASSERT_NO_THROW(new FolderReader(inputTestDirectory));
}


TEST(LaneTest, shouldParseLine_whenGivenValidData){
    Lane lane("lane1");

    std::string input = "name:values";
    lane.addPlayer(input);

    EXPECT_FALSE(lane.getPlayers().empty());
    auto player = lane.getPlayers().front();

    EXPECT_EQ(player.name, "name");
    EXPECT_EQ(player.game, "values");
}

TEST(LaneTest, shouldParseLine_whenNoNameOfPLayer){
    Lane lane("lane1");

    std::string input = ":values";
    lane.addPlayer(input);

    EXPECT_FALSE(lane.getPlayers().empty());
    auto player = lane.getPlayers().front();

    EXPECT_EQ(player.name, "");
    EXPECT_EQ(player.game, "values");
}

TEST(LaneTest, shouldNotParseLine_whenNoFrames){
    Lane lane("lane1");

    std::string input = "name:";
    lane.addPlayer(input);

    EXPECT_TRUE(lane.getPlayers().empty());
}


TEST_F(FolderReaderTest, ShouldHaveValidName_IfValidFiles) {
    // GIVEN
    FolderReader fr(inputTestDirectory);
    LaneReader laneReader(&fr);

    // WHEN
    auto lanes = laneReader.getLanes();
}

TEST_F(FolderReaderTest, ShouldHaveValidLines_IfValidFiles) {
    // GIVEN
    FolderReader fr(inputTestDirectory);
    LaneReader laneReader(&fr);

    // WHEN
    auto lanes = laneReader.getLanes();
    auto players = lanes[0]->getPlayers();

    //then
    EXPECT_EQ(players.size(), 3);
    validatePlayer(players[0], "Name1", "X|4-|3");
    validatePlayer(players[1], "Name2", "34|X|0-");
    validatePlayer(players[2], "", "X|22|33");

    //AND
    EXPECT_EQ(lanes[1]->getName(), "lane2");
    EXPECT_EQ(lanes[1]->getPlayers().size(), 0);
    EXPECT_EQ(lanes[2]->getName(), "lane3");
    EXPECT_EQ(lanes[2]->getPlayers().size(), 2);
}


