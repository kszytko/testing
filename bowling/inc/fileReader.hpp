#pragma once

#include <string>
#include <filesystem>


namespace fs = std::filesystem;

class FileReader{
public:
    FileReader(fs::path file) : file_(file){
        readLines();
    };

    std::vector<std::string> getLines() { return lines_; }
    std::string getFileName() const;

private:
    void readLines();
    bool isLineValid(std::string line);

private:
    fs::path file_;
    std::vector<std::string> lines_;
};

