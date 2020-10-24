#pragma once

#include "filesReader.hpp"
#include "frameParser.hpp"
#include "game.hpp"
#include <memory>

#include "printableData.hpp"

class ScoreCounter{
public:
    ScoreCounter(FilesReader & reader) : reader_(std::make_shared<FilesReader>(reader)){
        calculate(reader);
    }

    void calculate(FilesReader & reader){
        Game game;
        for (size_t i = 0; i < reader.getLanesNum(); i++) {
            auto lane = reader.getLane(i);
            LaneStruct printableLane(lane->getName(), Status::NO_GAME);
            bool allSequencesComplete = true;
            for (size_t j = 0; j < lane->getPlayersNum(); j++) {
                allSequencesComplete &= FrameParser::isSequenceComplete(lane->getPlayer(j));
                auto parsed = FrameParser::parse(lane->getPlayer(j));
                for (const auto& el : parsed.second) {
                    game.roll(el);
                }
                printableLane.players_.emplace_back(parsed.first, game.score());
                game.reset();
            }
            if (lane->getPlayersNum() == 0) {
                printableLane.status_ = Status::NO_GAME;
            } else if (allSequencesComplete) {
                printableLane.status_ = Status::FINISHED;
            } else {
                printableLane.status_ = Status::IN_PROGRESS;
            }
            lanes.push_back(printableLane);
        }
    }

private:
    std::shared_ptr<FilesReader> reader_;
public:
    std::vector<LaneStruct> lanes;
};
