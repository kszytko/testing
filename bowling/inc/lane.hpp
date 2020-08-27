#pragma once

#include <string>
#include <vector>
#include <exception>

struct Lane{
    Lane(std::string name_) : name_(name_){};

    struct Player{
        std::string name;
        std::string game;

        Player(std::string name_, std::string game_) : name(name_), game(game_){};
    };

    std::string getName() const {return name_;};
    std::vector<Player> getPlayers()  {return players_;};

    void addPlayer(std::string & line);
    void addPlayers(std::vector<std::string> lines);

private:
    std::string readPlayerName(std::string & line);
    std::string readPlayerGame(std::string & line);
    unsigned int getSeparatorPos(std::string & line);

private:
    std::string name_;
    std::vector<Player> players_;

};


