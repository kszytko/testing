#pragma once
#include <vector>
#include <string>

#include "fileReader.hpp"
#include "folderReader.hpp"
#include "lane.hpp"

class LaneReader {
public:
    LaneReader(FolderReader * folderReader);

    std::vector<Lane*> getLanes() { return lanes_; };

private:
    void readLane(FileReader & fr);

private:
    std::vector<Lane*> lanes_;
};
