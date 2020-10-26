#pragma once

#include "game.hpp"
#include "lane.hpp"
#include "reader.hpp"

class ScoreCounter {
public:
    ScoreCounter(Reader& reader);
    std::vector<Lane> getLanes() const { return lanes_; };

private:
    void calculateLane(Lane& lane);

    std::vector<Lane> lanes_;
    Game game;
};
