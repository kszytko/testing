#pragma once
#include <string>
#include <vector>

using parsedFrame = std::pair<std::string, std::vector<size_t>>;

class FrameParser {
public:
    static parsedFrame parse(const std::string& line);
    static bool isSequenceComplete(const std::string& line);

private:
    static const char StrikeSign;
    static const char SpareSign;
    static const char MissSign;
    static void parseToken(const char token, size_t& lastRollValue);
    static bool areProperTokensAtTheEnd(const std::string& line, size_t position, size_t numberOfTokensToLookFor);
};
