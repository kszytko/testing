#include "frameParser.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>

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
    }
    
    std::vector<char> result = {
        std::next(gamePoints.begin(), prev),
        gamePoints.end()};
    
    result.erase(std::remove_if(result.begin(), result.end(),
				[] (char el) {return el == '|'; }),
		 result.end());
    
    return std::pair(name, result);
}
