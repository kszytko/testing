#include <algorithm>
#include <functional>

#include "frameParser.hpp"
#include "tokenizer.hpp"

const char FrameParser::StrikeSign = 'X';
const char FrameParser::MissSign = '-';
const char FrameParser::SpareSign = '/';

void FrameParser::parseToken(const char token, size_t& lastRollValue) {
    switch (token) {
    case FrameParser::StrikeSign:
        lastRollValue = 10;
        break;
    case FrameParser::SpareSign:
        lastRollValue = 10 - lastRollValue;
        break;
    case FrameParser::MissSign:
        lastRollValue = 0;
        break;
    default:
        lastRollValue = static_cast<size_t>(token - '0');
        break;
    }
}

parsedFrame FrameParser::parse(const std::string& line) {
    std::vector<size_t> parsed{};
    size_t lastRollValue{};

    auto name = Tokenizer::readName(line);
    auto sequence = Tokenizer::readSequence(line);

    std::for_each(sequence.cbegin(), sequence.cend(), [&lastRollValue, &parsed](const auto& el) {
        FrameParser::parseToken(el, lastRollValue);
        parsed.push_back(lastRollValue);
    });

    return std::pair(name, parsed);
}
