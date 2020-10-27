#include "filesReader.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>

FilesReader::FilesReader(const std::string& directory) : directoryPath_(fs::path(directory)) {
    checkDirectory();
    makeFileList();
    populateLanesFromFiles();
};

void FilesReader::checkDirectory() const {
    if (!fs::exists(directoryPath_)) {
        throw std::invalid_argument("Directory does not exist");
    }
    if (!fs::is_directory(directoryPath_)) {
        throw std::invalid_argument("Not a directory");
    }
}

void FilesReader::makeFileList() {
    for (const auto& entry : fs::directory_iterator(directoryPath_)) {
        auto filename = entry.path().filename();
        if (fs::is_regular_file(entry.status())) {
            files_.push_back(entry.path());
        }
    }
    files_.shrink_to_fit();
    std::sort(files_.begin(), files_.end());
}

void FilesReader::populateLanesFromFiles() {
    for (const auto& file : files_) {
        auto fileName = file.stem().string();
        Lane lane{fileName};
    
        for(auto & line : readFile(file))  {
            if (isValidPlayer(line)) {
                lane.addPlayer(line);        
            }
        } 
        
        lanes_.push_back(lane);
    }
}

std::vector<std::string> FilesReader::readFile(const fs::path& file) {
    std::ifstream infile(file);
    std::string line;
    std::vector<std::string> lanes;

    while (std::getline(infile, line)) {
        lanes.push_back(line);
    }

    return lanes;
}

bool FilesReader::isValidPlayer(const std::string& line) {
    return line.find(NAME_DELIMITER_SIGN) != std::string::npos;
}
