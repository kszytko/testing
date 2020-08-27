#include "fileReader.hpp"
#include <fstream>

std::string FileReader::getFileName() const {
    return file_.stem().string();
}

void FileReader::readLines() {
    std::ifstream infile(file_);
    std::string line;

    while (std::getline(infile, line)) {
        if(isLineValid(line)) {
            lines_.push_back(line);
        }
    }
}
bool FileReader::isLineValid(std::string line) {
    return line.find(':') != std::string::npos;
}