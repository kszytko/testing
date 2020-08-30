#pragma once
#include <string>
#include <vector>

using parsedFrame = std::pair<std::string, std::vector<size_t>>;

class FrameParser {
public:
    static parsedFrame parse(const std::string& line);

private:
    static const char StrikeSign;
    static const char SpareSign;
    static const char MissSign;
    static size_t parseToken(const char token, size_t& lastParsedToken);
};
