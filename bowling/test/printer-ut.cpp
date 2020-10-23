#include <gtest/gtest.h>
#include <functional>
#include <filesystem>

#include "printer.hpp"
#include "consoleStream.hpp"
#include "fileStream.hpp"

struct PrinterTest : public ::testing::Test
{
    void SetUp() override{
        oss = new ConsoleStream();
        printer = new Printer(oss);
    }

    void TearDown() override {
        delete oss;
        delete printer;
    }
    
    ConsoleStream * oss;
    Printer* printer;
    std::vector<LaneStruct> lanes;
};

TEST_F(PrinterTest, GivenEmptyOutputFile_ShouldPrintData) {
    auto data = oss->str();
    ASSERT_EQ(data, "");
}

TEST_F(PrinterTest, GivenEmptyStruct_ShouldPrintNoData) {
    LaneStruct lane;
    lanes.push_back(lane);

    printer->print(lanes);

    auto output = "### :  ###\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::NO_GAME);

    printer->print(lanes);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::FINISHED);

    printer->print(lanes);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes[0].players_.emplace_back("Name1", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "Name1 30\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes[0].players_.emplace_back("", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "30\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, givenMultipleLanes_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", Status::IN_PROGRESS);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "### Lane 2: game in progress ###\n"
                  "### Lane 3: game in progress ###\n";
    ASSERT_EQ(oss->str(), output);
}

TEST_F(PrinterTest, givenMultipleLanesWithMultiplePlayers_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", Status::IN_PROGRESS);

    lanes[0].players_.emplace_back("Name1", 10);
    lanes[1].players_.emplace_back("Name2", 20);
    lanes[2].players_.emplace_back("Name3", 30);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n"
                  "Name1 10\n"
                  "### Lane 2: game in progress ###\n"
                  "Name2 20\n"
                  "### Lane 3: game in progress ###\n"
                  "Name3 30\n";

    ASSERT_EQ(oss->str(), output);
}

struct PrinterIntoFileTest : public ::testing::Test
{
    Printer* printer;
    std::vector<LaneStruct> lanes;
    std::ostringstream oss;
};


TEST_F(PrinterIntoFileTest, givenData_ShouldPrintIntoFile) {
    std::string fileName = "testFile.txt";
    FileStream* fstr = new FileStream(fileName);
    printer = new Printer(fstr);

    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", Status::IN_PROGRESS);

    lanes[0].players_.emplace_back("Name1", 10);
    lanes[1].players_.emplace_back("Name2", 20);
    lanes[2].players_.emplace_back("Name3", 30);

    printer->print(lanes);

    // auto output = "### Lane 1: game in progress ###\n"
    //               "Name1 10\n"
    //               "### Lane 2: game in progress ###\n"
    //               "Name2 20\n"
    //               "### Lane 3: game in progress ###\n"
    //               "Name3 30\n";

    ASSERT_TRUE(std::filesystem::exists(fileName));
    delete fstr;
    delete printer;
}

// struct DISABLED_PrinterIntoFileTest : public ::testing::Test
// {
//     Printer* printer;
//     std::vector<LaneStruct> lanes;
//     std::ostringstream oss;
// };

// TEST_F(DISABLED_PrinterIntoFileTest, givenWrongFileName_ShouldTrowError) {
//     std::string fileName = "IsItPossible?";
//     printer = new Printer(new FileStream(fileName));

//     printer->print(lanes);

//     ASSERT_FALSE(std::filesystem::exists(fileName));
// }