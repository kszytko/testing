#include "LaneReader.hpp"

LaneReader::LaneReader(FolderReader * folderReader) {
      for(auto & file : *folderReader->getFileReaders()){
//        FileReader fileReader(file);
        readLane(file);
    }
};

void LaneReader::readLane(FileReader & fr){
    Lane* lane = new Lane(fr.getFileName());
    lane->addPlayers(fr.getLines());
    lanes_.push_back(lane);
}

