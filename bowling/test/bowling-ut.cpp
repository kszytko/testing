#include <gtest/gtest.h>
#include <vector>

#include "game.hpp"

class GameTest : public ::testing::Test {
public:
    std::vector<size_t> rolls;

    void roll(size_t number) { rolls.push_back(number); }

    void gutterGame() { rollMany(20, 0); }
    void allOnes() { rollMany(20, 1); }
    void rollSpare() {
        roll(5);
        roll(5);
    }
    void rollStrike() { roll(10); }
    void rollMany(size_t n, size_t pins) {
        for (size_t i = 0; i < n; ++i) {
            roll(pins);
        }
    }
};

TEST_F(GameTest, GutterGame) {
    gutterGame();
    Game game(rolls);
    ASSERT_EQ(0, game.getScore());
}
TEST_F(GameTest, AllOnes) {
    allOnes();
    Game game(rolls);
    ASSERT_EQ(20, game.getScore());
}
TEST_F(GameTest, OneSpare) {
    rollSpare();
    roll(3);
    rollMany(17, 0);
    Game game(rolls);
    ASSERT_EQ(16, game.getScore());
}
TEST_F(GameTest, OneStrike) {
    rollStrike();
    roll(3);
    roll(4);
    rollMany(16, 0);
    Game game(rolls);
    ASSERT_EQ(24, game.getScore());
}
TEST_F(GameTest, PerfectGame) {
    rollMany(12, 10);
    Game game(rolls);
    ASSERT_EQ(300, game.getScore());
}
