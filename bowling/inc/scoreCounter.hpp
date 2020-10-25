#pragma once

#include "filesReader.hpp"
#include "game.hpp"
#include "lane.hpp"

class ScoreCounter{
public:
    ScoreCounter(FilesReader & reader);

private:
    void calculate();
    void calculateLane(Lane & lane);

    std::vector<Lane> lanes_;
    Game game;
};
