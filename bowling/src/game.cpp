#include "game.hpp"

Game::Game(const std::vector<size_t>& rolls) {
    std::copy(rolls.begin(), rolls.end(), rolls_.begin());
    calculateScore();
}

void Game::calculateScore() {
    size_t firstFrameThrow{};

    for (size_t frame = 0; frame < MAX_FRAMES; ++frame) {
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
}

bool Game::isSpare(size_t firstFrameThrow) {
    return rolls_[firstFrameThrow] + rolls_[++firstFrameThrow] == MAX_PINS;
}

bool Game::isStrike(size_t firstFrameThrow) {
    return rolls_[firstFrameThrow] == MAX_PINS;
}

size_t Game::nextTwoBallsForStrike(size_t firstFrameThrow) {
    return rolls_[++firstFrameThrow] + rolls_[++firstFrameThrow];
}

size_t Game::nextBallForSpare(size_t firstFrameThrow) {
    return rolls_[firstFrameThrow + 2];
}

size_t Game::twoBallsInFrame(size_t firstFrameThrow) {
    return rolls_[firstFrameThrow] + rolls_[++firstFrameThrow];
}
