#include <gtest/gtest.h>
#include <filesystem>
#include <functional>

#include "printer.hpp"
#include "lane.hpp"

struct PrinterTest : public ::testing::Test {
    void SetUp() override {
        stream.clear();
        printer = std::make_shared<Printer>(stream);
    }

    std::stringstream stream;
    std::shared_ptr<Printer> printer;
    std::vector<Lane> lanes;
};

TEST_F(PrinterTest, GivenEmptyOutputFile_ShouldPrintData) {
    auto data = stream.str();
    ASSERT_EQ(data, "");
}

TEST_F(PrinterTest, GivenEmptyStruct_ShouldPrintNoData) {
    Lane lane;
    lanes.push_back(lane);

    printer->printLanes(lanes);

    ASSERT_EQ(stream.str(), "### :  ###\n");
}

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    lanes.push_back({"Lane 1", Status::IN_PROGRESS, {}});

    printer->printLanes(lanes);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    lanes.push_back({"Lane 1", Status::NO_GAME, {}});

    printer->printLanes(lanes);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {
    lanes.push_back({"Lane 1", Status::FINISHED, {}});

    printer->printLanes(lanes);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    lanes.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    lanes[0].players_.push_back({"Name1", "", 30});

    printer->printLanes(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {
    lanes.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    lanes[0].players_.push_back({"", "", 30});

    printer->printLanes(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanes_ShouldPrintValidHeaders) {
    lanes.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    lanes.push_back({"Lane 2", Status::IN_PROGRESS, {}});
    lanes.push_back({"Lane 3", Status::IN_PROGRESS, {}});

    printer->printLanes(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "### Lane 2: game in progress ###\n"
        "### Lane 3: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanesWithMultiplePlayers_ShouldPrintValidHeaders) {
    lanes.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    lanes.push_back({"Lane 2", Status::IN_PROGRESS, {}});
    lanes.push_back({"Lane 3", Status::IN_PROGRESS, {}});

    lanes[0].players_.push_back({"Name1", "", 10});
    lanes[1].players_.push_back({"Name2", "", 20});
    lanes[2].players_.push_back({"Name3", "", 30});

    printer->printLanes(lanes);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 10\n"
        "### Lane 2: game in progress ###\n"
        "Name2 20\n"
        "### Lane 3: game in progress ###\n"
        "Name3 30\n";

    ASSERT_EQ(stream.str(), output);
}
