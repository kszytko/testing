#include <gtest/gtest.h>

#include "game.hpp"

class GameTest : public ::testing::Test {
public:
    Game game;

    void gutterGame() { rollMany(20, 0); }
    void allOnes() { rollMany(20, 1); }
    void rollSpare() {
        game.roll(5);
        game.roll(5);
    }
    void rollStrike() { game.roll(10); }
    void rollMany(size_t n, size_t pins) {
        for (size_t i = 0; i < n; ++i) {
            game.roll(pins);
        }
    }
};

TEST_F(GameTest, GutterGame) {
    game.reset();
    gutterGame();
    ASSERT_EQ(0, game.score());
}
TEST_F(GameTest, AllOnes) {
    game.reset();
    allOnes();
    ASSERT_EQ(20, game.score());
}
TEST_F(GameTest, OneSpare) {
    game.reset();
    rollSpare();
    game.roll(3);
    rollMany(17, 0);
    ASSERT_EQ(16, game.score());
}
TEST_F(GameTest, OneStrike) {
    game.reset();
    rollStrike();
    game.roll(3);
    game.roll(4);
    rollMany(16, 0);
    ASSERT_EQ(24, game.score());
}
TEST_F(GameTest, PerfectGame) {
    game.reset();
    rollMany(12, 10);
    ASSERT_EQ(300, game.score());
}
