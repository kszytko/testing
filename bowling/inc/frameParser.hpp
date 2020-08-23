#pragma once
#include <string>
#include <vector>

constexpr char DELIMITER = '|';
constexpr char STRIKE = 'X';  // Maybe map like - strike - 10, spare miss, 0, but additional logic with spare sign...
constexpr char SPARE_SIGN = '/';
constexpr char MISS = '-';

using tokenizedFrame = std::pair<std::string,  std::vector<char>>;
using parsedFrame = std::pair<std::string, std::vector<size_t>>;

class FrameParser {
public:
    static parsedFrame parse(const std::string& gamePoints);
};

class Tokenizer {
public:
  static tokenizedFrame splitToFrames(const std::string& gamePoints);
  static tokenizedFrame splitToFramesAlt(const std::string& gamePoints);
};
