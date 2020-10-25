#pragma once

#include "filesReader.hpp"
#include "frameParser.hpp"
#include "game.hpp"
#include <memory>

enum class Status { NO_GAME, IN_PROGRESS, FINISHED };

struct Player {
    std::string name_;
    size_t score_;
};

struct LaneStruct {
    std::string name_;
    Status status_;
    std::vector<Player> players_;
};

class ScoreCounter{
public:
    ScoreCounter(FilesReader & reader) : reader_(std::make_shared<FilesReader>(reader)){
        calculate(reader);
    }

    void calculate(FilesReader & reader){
        for (auto & lane : reader.getLanes()) {
            calculateLane(lane);
        }
    }

    void calculateLane(std::shared_ptr<Lane> & lane){
        LaneStruct printableLane;
        bool allSequencesComplete = true;

        for (auto & player : lane->players_) {
            allSequencesComplete &= FrameParser::isSequenceComplete(player);
            auto [playerName, rolls] = FrameParser::parse(player);


            printableLane.players_.push_back({playerName, game.calculateScore(rolls)});
        }
        
        if (allSequencesComplete) {
            printableLane.status_ = Status::FINISHED;
        } 
        else if(lane->getPlayersNum() > 0){
            printableLane.status_ = Status::IN_PROGRESS;
        }

        lanes_.push_back(printableLane);
    }

    

private:
    std::shared_ptr<FilesReader> reader_;
    Game game;

public:
    std::vector<LaneStruct> lanes_;
};
