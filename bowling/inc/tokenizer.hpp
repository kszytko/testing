#pragma once
#include <string>

class Tokenizer {
public:
    static std::string readSequence(const std::string& line);
    static std::string readName(const std::string& line);

private:
    static const char FrameDelimiterSign;
    static const char NameDelimiterSign;
};
