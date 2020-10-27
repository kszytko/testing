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

TEST_F(PrinterTest, laneInProgress_ShouldPrintValidHeader) {
    Lane lane{"Lane 1"};
    lane.status_ = Status::IN_PROGRESS;
    mockScoreCounter.lanes_.push_back(lane);

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneNoGame_ShouldPrintValidHeader) {
    Lane lane{"Lane 1"};
    mockScoreCounter.lanes_.push_back(lane);

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: no game ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, laneFinished_ShouldPrintValidHeader) {    
    Lane lane{"Lane 1"};
    lane.status_ = Status::FINISHED;
    mockScoreCounter.lanes_.push_back(lane);

    printer->print(mockScoreCounter);

    auto output = "### Lane 1: game finished ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenOnePLayer_ShouldPrintValidData) {
    Lane lane{"Lane 1"};
    lane.status_ = Status::IN_PROGRESS;
    mockScoreCounter.lanes_.push_back(lane);
    mockScoreCounter.lanes_[0].players_.push_back({"Name1", "", 30});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "Name1 30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenPlayerWithoutName_ShouldPrintOnlyScore) {    
    Lane lane{"Lane 1"};
    lane.status_ = Status::IN_PROGRESS;
    mockScoreCounter.lanes_.push_back(lane);
    mockScoreCounter.lanes_[0].players_.push_back({"", "", 30});

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "30\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanes_ShouldPrintValidHeaders) {
    Lane lane1{"Lane 1"};
    Lane lane2{"Lane 2"};
    Lane lane3{"Lane 3"};
    lane1.status_ = Status::IN_PROGRESS;
    lane2.status_ = Status::IN_PROGRESS;
    lane3.status_ = Status::IN_PROGRESS;
    mockScoreCounter.lanes_.push_back(lane1);
    mockScoreCounter.lanes_.push_back(lane2);
    mockScoreCounter.lanes_.push_back(lane3);

    printer->print(mockScoreCounter);

    auto output =
        "### Lane 1: game in progress ###\n"
        "### Lane 2: game in progress ###\n"
        "### Lane 3: game in progress ###\n";
    ASSERT_EQ(stream.str(), output);
}

TEST_F(PrinterTest, givenMultipleLanesWithMultiplePlayers_ShouldPrintValidHeaders) {
    Lane lane1{"Lane 1"};
    Lane lane2{"Lane 2"};
    Lane lane3{"Lane 3"};
    lane1.status_ = Status::IN_PROGRESS;
    lane2.status_ = Status::IN_PROGRESS;
    lane3.status_ = Status::IN_PROGRESS;
    mockScoreCounter.lanes_.push_back(lane1);
    mockScoreCounter.lanes_.push_back(lane2);
    mockScoreCounter.lanes_.push_back(lane3);

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
