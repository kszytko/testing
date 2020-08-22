#pragma once
#include <string>
#include <vector>

class FrameParser {
public:
    FrameParser(const std::string& gameString);  // thinking about explicit...

    std::string getGameString() const { return gameString_; }
    std::vector<size_t> getFrames() const { return frames_; }

    void parse();

private:
    std::string gameString_;
    std::vector<size_t> frames_;
};
