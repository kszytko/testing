#include "game.hpp"

void Game::roll(int pins) {
    rolls[currentRoll++] = pins;
}

int Game::score() {
    int score_{};
    int firstFrameThrow{};
    for (int frame = 0; frame < MAX_FRAMES; ++frame) {
        if (isStrike(firstFrameThrow)) {
            score_ += MAX_FRAME_SCORE + nextTwoBallsForStrike(firstFrameThrow);
            firstFrameThrow++;
        } else if (isSpare(firstFrameThrow)) {
            score_ += MAX_FRAME_SCORE + nextBallForSpare(firstFrameThrow);
            firstFrameThrow += 2;
        } else {
            score_ += twoBallsInFrame(firstFrameThrow);
            firstFrameThrow += 2;
        }
    }
    return score_;
}

void Game::reset() {
    currentRoll = 0;
}

bool Game::isSpare(int firstFrameThrow) {
<<<<<<< HEAD
    return rolls[firstFrameThrow] + rolls[++firstFrameThrow] == MAX_PINS;
}

bool Game::isStrike(int firstFrameThrow) {
    return rolls[firstFrameThrow] == MAX_PINS;
=======
    return (rolls[firstFrameThrow] + rolls[++firstFrameThrow] == MAX_PINS);
}

bool Game::isStrike(int firstFrameThrow) {
    return (rolls[firstFrameThrow] == MAX_PINS);
>>>>>>> Formatted
}

int Game::nextTwoBallsForStrike(int firstFrameThrow) {
    return rolls[++firstFrameThrow] + rolls[++firstFrameThrow];
}

int Game::nextBallForSpare(int firstFrameThrow) {
    return rolls[firstFrameThrow + 2];
}

int Game::twoBallsInFrame(int firstFrameThrow) {
    return rolls[firstFrameThrow] + rolls[++firstFrameThrow];
}
