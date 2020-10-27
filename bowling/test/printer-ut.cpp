#include <gtest/gtest.h>
#include <filesystem>
#include <functional>

#include "lane.hpp"
#include "printer.hpp"

class MockScoreCounter : public ILane {
public:
    std::vector<Lane> getLanes() const override { return lanes_; };
    std::vector<Lane> lanes_;
};

struct PrinterTest : public ::testing::Test {
    void SetUp() override {
        stream.clear();
        printer = std::make_shared<Printer>(stream);
    }

    std::stringstream stream;
    std::shared_ptr<Printer> printer;

    MockScoreCounter mockScoreCounter;
};

TEST_F(PrinterTest, GivenEmptyOutputFile_ShouldPrintData) {
    auto data = stream.str();
    ASSERT_EQ(data, "");
}

TEST_F(PrinterTest, GivenEmptyStruct_ShouldPrintNoData) {
    Lane lane;
    mockScoreCounter.lanes_.push_back(lane);

    printer->print(mockScoreCounter);

    ASSERT_EQ(stream.str(), "### :  ###\n");
}

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::IN_PROGRESS, {}});

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::NO_GAME, {}});

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::FINISHED, {}});

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_[0].players_.push_back({"Name1", "", 30});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_[0].players_.push_back({"", "", 30});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanes_ShouldPrintValidHeaders) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_.push_back({"Lane 2", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_.push_back({"Lane 3", Status::IN_PROGRESS, {}});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "### Lane 2: game in progress ###\n"
        "### Lane 3: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanesWithMultiplePlayers_ShouldPrintValidHeaders) {
    mockScoreCounter.lanes_.push_back({"Lane 1", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_.push_back({"Lane 2", Status::IN_PROGRESS, {}});
    mockScoreCounter.lanes_.push_back({"Lane 3", Status::IN_PROGRESS, {}});

    mockScoreCounter.lanes_[0].players_.push_back({"Name1", "", 10});
    mockScoreCounter.lanes_[1].players_.push_back({"Name2", "", 20});
    mockScoreCounter.lanes_[2].players_.push_back({"Name3", "", 30});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 10\n"
        "### Lane 2: game in progress ###\n"
        "Name2 20\n"
        "### Lane 3: game in progress ###\n"
        "Name3 30\n";

    ASSERT_EQ(stream.str(), output);
}
