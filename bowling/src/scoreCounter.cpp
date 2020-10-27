#include "scoreCounter.hpp"
#include "frameParser.hpp"

ScoreCounter::ScoreCounter(const ILane& reader) : lanes_(reader.getLanes()) {
    for (auto& lane : lanes_) {
        calculateLane(lane);
    }
}

void ScoreCounter::calculateLane(Lane& lane) const {
    bool allSequencesComplete = true;

    for (auto& player : lane.players_) {
        allSequencesComplete &= FrameParser::isSequenceComplete(player.game_);
        auto rolls = FrameParser::parse(player.game_);
        player.score_ = Game(rolls).getScore();
    }

    if (lane.players_.size() > 0) {
        if (allSequencesComplete) {
            lane.status_ = Status::FINISHED;
        } else {
            lane.status_ = Status::IN_PROGRESS;
        }
    }
}
