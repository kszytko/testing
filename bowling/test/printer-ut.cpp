#include <gtest/gtest.h>
#include <functional>
#include <ostream>
#include <filesystem>

#include "Printer.h"
struct PrinterTest : public ::testing::Test
{
    void SetUp() override{
        printer = new Printer(oss);

    }

    Printer* printer;
    std::vector<LaneStruct> lanes;
    std::ostringstream oss;
};



TEST_F(PrinterTest, GivenEmptyOutputFile_ShouldPrintData) {
    ASSERT_EQ(oss.str(), "");
}

TEST_F(PrinterTest, GivenEmptyStruct_ShouldPrintNoData) {
    LaneStruct lane;
    lanes.push_back(lane);

    printer->print(lanes);

    ASSERT_EQ(oss.str(), "### :  ###\n");
}

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::NO_GAME);

    printer->print(lanes);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::FINISHED);

    printer->print(lanes);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);
    lanes[0].players.emplace_back("Name1", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "Name1 30\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);
    lanes[0].players.emplace_back("", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "30\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, givenMultipleLines_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", LaneStruct::Status::IN_PROGRESS);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "### Lane 2: game in progress ###\n"
                  "### Lane 3: game in progress ###\n";
    ASSERT_EQ(oss.str(), output);
}

TEST_F(PrinterTest, givenMultipleLinesWithMultiplePlayers_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", LaneStruct::Status::IN_PROGRESS);

    lanes[0].players.emplace_back("Name1", 10);
    lanes[1].players.emplace_back("Name2", 20);
    lanes[2].players.emplace_back("Name3", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "Name1 10\n"
                  "### Lane 2: game in progress ###\n"
                  "Name2 20\n"
                  "### Lane 3: game in progress ###\n"
                  "Name3 30\n";

    ASSERT_EQ(oss.str(), output);
}

struct PrinterIntoFileTest : public ::testing::Test
{
    Printer* printer;
    std::vector<LaneStruct> lanes;
    std::ostringstream oss;
};


TEST_F(PrinterIntoFileTest, givenData_ShouldPrintIntoFile) {
    std::string fileName = "testFile.txt";
    printer = new Printer(fileName);

    lanes.emplace_back("Lane 1", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", LaneStruct::Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", LaneStruct::Status::IN_PROGRESS);

    lanes[0].players.emplace_back("Name1", 10);
    lanes[1].players.emplace_back("Name2", 20);
    lanes[2].players.emplace_back("Name3", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "Name1 10\n"
                  "### Lane 2: game in progress ###\n"
                  "Name2 20\n"
                  "### Lane 3: game in progress ###\n"
                  "Name3 30\n";

    ASSERT_TRUE(std::filesystem::exists(fileName));
}

struct DISABLED_PrinterIntoFileTest : public ::testing::Test
{
    Printer* printer;
    std::vector<LaneStruct> lanes;
    std::ostringstream oss;
};

TEST_F(DISABLED_PrinterIntoFileTest, givenWrongFileName_ShouldTrowError) {
    std::string fileName = "IsItPossible?";
    printer = new Printer(fileName);

    printer->print(lanes);

    ASSERT_FALSE(std::filesystem::exists(fileName));
}