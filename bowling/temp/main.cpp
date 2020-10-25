#include <string>
#include <iostream>
#include <vector>
#include <memory>

struct Player{
    std::string name;
    std::string game;
    size_t score;
};

enum class Status { NO_GAME, IN_PROGRESS, FINISHED };


struct Lane{
    void addPlayer(std::string & line);
    void addPlayers(std::vector<std::string> lines);

    std::string name_;
    Status status_;
    std::vector<Player> players_;
};


int main(){
    Lane a{"asd"};
    auto d = std::shared_ptr<Lane>{"asd"};


    std::cout << a.name_;    
    return 0;
}