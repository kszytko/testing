#pragma once

#include <array>
#include <iostream>

constexpr size_t MAX_PINS{10};
constexpr size_t MAX_FRAMES{10};
constexpr size_t MAX_ROLLS{21};
constexpr size_t MAX_FRAME_SCORE{MAX_PINS};

class Game {
public:
    void roll(size_t pins);
    size_t score();
    void reset();

private:
    std::array<size_t, MAX_ROLLS> rolls;
    size_t currentRoll{};

    bool isSpare(size_t firstFrameThrow);
    bool isStrike(size_t firstFrameThrow);
    size_t nextTwoBallsForStrike(size_t firstFrameThrow);
    size_t nextBallForSpare(size_t firstFrameThrow);
    size_t twoBallsInFrame(size_t firstFrameThrow);
};
