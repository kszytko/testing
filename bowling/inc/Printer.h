#pragma once

#include <ostream>
#include <fstream>
#include <string>
#include <vector>

struct LaneStruct {
    enum class Status { NO_GAME, IN_PROGRESS, FINISHED };

    struct Player {
        std::string name;
        size_t score;
        Player(std::string name_, size_t score_) : name(name_), score(score_){};
    };

    std::string name;
    Status status;
    std::vector<Player> players;

    LaneStruct(std::string name_, Status status_) : name(name_), status(status_) {};
    LaneStruct(){};
};

class Printer{
public:
    Printer(std::ostream & stream_){
        stream = &stream_;
    };

    Printer(std::string filePath){
        if(filePath.empty())
            stream = new std::ostringstream;
        else {
            file = new std::ofstream;
            file->open(filePath);
            stream = file;
        }
    };

    ~Printer(){
        file->close();
        delete stream;
        delete file;
    }

    void print(std::vector<LaneStruct> lanes) {
        for(auto & lane : lanes){
            printHeader(lane);
            printPlayers(lane);
        }
    }

private:
    void printHeader(LaneStruct & lane){
        insertText("###");
        insertSpace();
        insertText(lane.name);
        insertText(":");
        insertSpace();
        insertStatus(lane.status);
        insertSpace();
        insertText("###");
        insertNewLine();
    }

    void insertText(const std::string& text) {
        *stream << text;
    }

    void insertSpace() {
        *stream << " ";
    }


    void insertStatus(const LaneStruct::Status status) {
        switch(status){
        case LaneStruct::Status::NO_GAME:
            insertText("no game");
            break;
        case LaneStruct::Status::IN_PROGRESS:
            insertText("game in progress");
            break;
        case LaneStruct::Status::FINISHED:
            insertText("game finished");
            break;
        }
    }

    void printPlayers(LaneStruct & lane){
        for(auto & player : lane.players){
            printPlayer(player);
            insertNewLine();
        }
    }

    void printPlayer(LaneStruct::Player & player){
        if(!player.name.empty()) {
            insertText(player.name);
            insertSpace();
        }
        insertValue(player.score);
    }

    void insertValue(size_t value){
        *stream << value;
    }

    void insertNewLine() {
        *stream << "\n";
    }

private:
    std::ostream * stream;
    std::ofstream * file;

};