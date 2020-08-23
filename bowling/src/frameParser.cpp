#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <algorithm>

<<<<<<< HEAD
#include "frameParser.hpp"
#include "tokenizer.hpp"

const char FrameParser::StrikeSign = 'X';
const char FrameParser::MissSign = '-';
const char FrameParser::SpareSign = '/';

size_t FrameParser::parseToken(const char token, size_t& lastParsedToken) {
    if (token == FrameParser::StrikeSign) {
        lastParsedToken = 10;
        return lastParsedToken;
    } else if (token == FrameParser::SpareSign) {
        lastParsedToken = 10 - lastParsedToken;
        return lastParsedToken;
    } else if (token == FrameParser::MissSign) {
        lastParsedToken = 0;
        return lastParsedToken;
    } else {
        lastParsedToken = token - '0';
        return lastParsedToken;
=======
parsedFrame FrameParser::parse(const std::string& gamePoints) {
  std::vector<size_t> parsed {};
  size_t last_parsed_char{};
  auto tokenized = Tokenizer::splitToFramesAlt(gamePoints);
  std::transform(tokenized.second.cbegin(),
		 tokenized.second.cend(),
		 back_inserter(parsed),
		 [&last_parsed_char] (char el) {
		   if (el == 'X') {
		     last_parsed_char = 10;
		     return last_parsed_char;
		   } else if (el == '/') {
		     last_parsed_char = 10 - last_parsed_char;
		     return last_parsed_char;
		   } else if (el == '-') {
		     last_parsed_char = 0;
		     return last_parsed_char;
		   } else {
		     last_parsed_char = el - '0';
		     return last_parsed_char;
		   }
		 });
  
  return std::pair(tokenized.first, parsed);
}

tokenizedFrame Tokenizer::splitToFramesAlt(const std::string& gamePoints) {
    size_t prev = 0;
    size_t next = 0;
    std::string name = "";
    
    next = gamePoints.find(":", prev);
    
    if (next != std::string::npos) {
      name = gamePoints.substr(prev, next - prev);
      prev = next + 1;
>>>>>>> algo + rename
    }
}

parsedFrame FrameParser::parse(const std::string& line) {
    std::vector<size_t> parsed{};
    size_t currentLinePosition{};
    size_t lastParsedToken{};

    auto name = Tokenizer::readName(line, currentLinePosition);
    auto sequence = Tokenizer::readSequence(line, currentLinePosition);

    std::transform(sequence.cbegin(), sequence.cend(), back_inserter(parsed),
                   std::bind(FrameParser::parseToken, std::placeholders::_1, lastParsedToken));

    return std::pair(name, parsed);
}
