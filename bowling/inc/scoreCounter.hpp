#pragma once

#include "filesReader.hpp"
#include "game.hpp"
#include "lane.hpp"

class ScoreCounter{
public:
    ScoreCounter(FilesReader & reader);
    std::vector<Lane> getLanes() const { return lanes_; };

private:
    void calculate();
    void calculateLane(Lane & lane);

    std::vector<Lane> lanes_;
    Game game;
};
