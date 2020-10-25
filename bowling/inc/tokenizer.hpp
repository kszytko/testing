#pragma once
#include <string>

class Tokenizer {
public:
    static std::string readSequence(const std::string& line);

private:
    static const char FrameDelimiterSign;
};
