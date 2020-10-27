#pragma once

#include "game.hpp"
#include "lane.hpp"

class ScoreCounter : public ILane{
public:
    ScoreCounter(const ILane& reader);
    std::vector<Lane> getLanes() const { return lanes_; };

private:
    void calculateLane(Lane& lane);

    std::vector<Lane> lanes_;
    Game game;
};
