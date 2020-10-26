#include <gtest/gtest.h>

#include "lane.hpp"
#include "reader.hpp"
#include "scoreCounter.hpp"

class MockReader : public Reader {
public:
    std::vector<Lane> getLanes() const override { return lanes_; };
    std::vector<Lane> lanes_;
};

struct ScoreTest : public ::testing::Test {
    void SetUp() override {
        Lane lane{"Lane 1", Status::IN_PROGRESS, {}};
        lane.players_.push_back({"Name1", "", 0});
        mockReader.lanes_.push_back(lane);
    }

    void assertScore(const std::string& game, size_t score) {
        mockReader.lanes_[0].players_[0].game_ = game;
        ScoreCounter counter(mockReader);

        auto newLanes = counter.getLanes();
        auto calculatedScore = newLanes[0].players_[0].score_;

        ASSERT_EQ(calculatedScore, score);
    }

    MockReader mockReader;
};

TEST_F(ScoreTest, GivenPerfectGame_ShouldCalculateMaxScore) {
    auto game = "X|X|X|X|X|X|X|X|X|X||XX";
    auto score = 300;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenGutterGame_ShouldCalculateZero) {
    auto game = "0-|0-|0-|0-|0-|0-|0-|0-|0-|0-||";
    auto score = 0;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenGutterGame_ShouldCalculateValidScore) {
    auto game = "11|11|11|11|11|11|11|11|11|11||";
    auto score = 20;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenOneSpare_ShouldCalculateValidScore) {
    auto game = "55|3-|0-|0-|0-|0-|0-|0-|0-|0-||";
    auto score = 16;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenOneStrike_ShouldCalculateValidScore) {
    auto game = "X|34|0-|0-|0-|0-|0-|0-|0-|0-||";
    auto score = 24;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenAllNines_ShouldCalculateValidScore) {
    auto game = "9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||";
    auto score = 90;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenAllFifeSpares_ShouldCalculateValidScore) {
    auto game = "5/|5/|5/|5/|5/|5/|5/|5/|5/|5/||5";
    auto score = 150;

    assertScore(game, score);
}

TEST_F(ScoreTest, GivenNotFinished_ShouldCalculateValidScore) {
    auto game1 = "X|4-|3";
    auto game2 = "34|X|0-";
    auto game3 = "X|22|33";

    assertScore(game1, 21);
    assertScore(game2, 17);
    assertScore(game3, 24);
}
