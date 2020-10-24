#include <gtest/gtest.h>
#include <filesystem>
#include <functional>

#include "printer.hpp"

struct PrinterTest : public ::testing::Test {
    void SetUp() override {
        stream.clear();
        printer = std::make_shared<Printer>(stream);
    }

    std::stringstream stream;
    std::shared_ptr<Printer> printer;
    std::vector<LaneStruct> lanes;
};

TEST_F(PrinterTest, GivenEmptyOutputFile_ShouldPrintData) {
    auto data = stream.str();
    ASSERT_EQ(data, "");
}

TEST_F(PrinterTest, GivenEmptyStruct_ShouldPrintNoData) {
    LaneStruct lane;
    lanes.push_back(lane);

    printer->print(lanes);

    ASSERT_EQ(stream.str(), "### :  ###\n");
}

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);

    printer->print(lanes);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::NO_GAME);

    printer->print(lanes);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {
    lanes.emplace_back("Lane 1", Status::FINISHED);

    printer->print(lanes);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes[0].players_.emplace_back("Name1", 30);

    printer->print(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes[0].players_.emplace_back("", 30);

    printer->print(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanes_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", Status::IN_PROGRESS);

    printer->print(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "### Lane 2: game in progress ###\n"
        "### Lane 3: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanesWithMultiplePlayers_ShouldPrintValidHeaders) {
    lanes.emplace_back("Lane 1", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 2", Status::IN_PROGRESS);
    lanes.emplace_back("Lane 3", Status::IN_PROGRESS);

    lanes[0].players_.emplace_back("Name1", 10);
    lanes[1].players_.emplace_back("Name2", 20);
    lanes[2].players_.emplace_back("Name3", 30);

    printer->print(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 10\n"
        "### Lane 2: game in progress ###\n"
        "Name2 20\n"
        "### Lane 3: game in progress ###\n"
        "Name3 30\n";

    ASSERT_EQ(stream.str(), output);
}
