#pragma once

#include "game.hpp"
#include "lane.hpp"

class ScoreCounter : public ILane {
public:
    ScoreCounter(const ILane& reader);
    std::vector<Lane> getLanes() const override { return lanes_; };

private:
    void calculateLane(Lane& lane) const;

    std::vector<Lane> lanes_;
};
