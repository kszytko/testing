#pragma once

#include "printableData.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>

class Printer{
public:
    explicit Printer(std::ostream & outStream){
        stream_ = std::make_unique<std::ostream>(outStream.rdbuf());
    }

    explicit Printer(std::string filename = ""){
        if(filename.empty()){
            stream_ = std::make_unique<std::ostream>(std::cout.rdbuf());
        }
        else{
            file_ = std::make_unique<std::fstream>(filename, std::fstream::out | std::fstream::app);
            if(!file_->is_open()){
                throw std::runtime_error("Open file not possible."); 
            }      
            stream_ = std::make_unique<std::ostream>(file_->rdbuf());
       }
    }

    ~Printer(){
        if(file_){
            file_->close(); 
        }
    }

    void print(std::vector<LaneStruct> & lanes);

private:
    void printHeader(LaneStruct & lane);
    std::string parseStatus(const Status & status);
    void printPlayers(LaneStruct & lane);
    void printPlayer(Player & player);

private:
    std::unique_ptr<std::ostream> stream_;
    std::unique_ptr<std::fstream> file_;
};
