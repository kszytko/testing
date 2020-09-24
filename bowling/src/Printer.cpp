#include "Printer.h"



    void ConsoleStream::print(std::string stream){
        stream_ << stream;
    }

    void ConsoleStream::print(size_t value){
        stream_ << value;
    }

    std::string ConsoleStream::str() const {
        return stream_.str();
    }



    FileStream::FileStream(std::string filePath){
        if(filePath.empty())
            throw InvalidFileName();
        
        file_ = new std::ofstream;
        file_->open(filePath);
    }

    void FileStream::print(std::string stream){
        *file_ << stream;
    };

    void FileStream::print(size_t value){
        *file_ << value;
    }



    void Printer::print(std::vector<LaneStruct> lanes) {
        for(auto & lane : lanes){
            printHeader(lane);
            printPlayers(lane);
        }
    }

    void Printer::printHeader(LaneStruct & lane){
        print("### " + lane.name + ": " + parseStatus(lane.status) + " ###\n");
    }

    void Printer::print(std::string text){
        stream_->print(text);
    }

    void Printer::print(size_t value){
        stream_->print(value);
    }

    std::string Printer::parseStatus(const LaneStruct::Status status) {
        switch(status){
        case LaneStruct::Status::NO_GAME:
            return "no game";

        case LaneStruct::Status::IN_PROGRESS:
            return "game in progress";
        
        case LaneStruct::Status::FINISHED:
            return "game finished";

        default:
            return "";
        }
    }

    void Printer::printPlayers(LaneStruct & lane){
        for(auto & player : lane.players){
            printPlayer(player);
            print("\n");
        }
    }

    void Printer::printPlayer(Player & player){
        if(!player.name.empty()) {
            print(player.name + " ");
        }
        print(player.score);
    }

