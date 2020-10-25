#pragma once

#include "filesReader.hpp"
#include "frameParser.hpp"
#include "game.hpp"
#include <memory>


class ScoreCounter{
public:
    ScoreCounter(FilesReader & reader) : lanes_(reader.getLanes()){
        calculate();
    }

    void calculate(){
        for (auto & lane : lanes_) {
            calculateLane(lane);
        }
    }

    void calculateLane(Lane & lane){
        bool allSequencesComplete = true;

        for (auto & player : lane.players_) {
            allSequencesComplete &= FrameParser::isSequenceComplete(player.game_);
            auto rolls = FrameParser::parse(player.game_);
            player.score_ = game.calculateScore(rolls);
        }
        
        if (allSequencesComplete) {
            lane.status_ = Status::FINISHED;
        } 
        else if(lane.players_.size() > 0){
            lane.status_ = Status::IN_PROGRESS;
        }
    }


private:
    std::vector<Lane> lanes_;
    Game game;

};
