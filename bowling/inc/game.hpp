#pragma once

#include <array>
#include <iostream>
#include <vector>

constexpr size_t MAX_PINS{10};
constexpr size_t MAX_FRAMES{10};
constexpr size_t MAX_ROLLS{21};
constexpr size_t MAX_FRAME_SCORE{MAX_PINS};

class Game {
public:
    Game(const std::vector<size_t>& rolls);
    size_t getScore() const { return score_; };

private:
    std::array<size_t, MAX_ROLLS> rolls_{};
    size_t score_{};

    size_t calculateScore();

    bool isSpare(size_t firstFrameThrow);
    bool isStrike(size_t firstFrameThrow);
    size_t nextTwoBallsForStrike(size_t firstFrameThrow);
    size_t nextBallForSpare(size_t firstFrameThrow);
    size_t twoBallsInFrame(size_t firstFrameThrow);
};
