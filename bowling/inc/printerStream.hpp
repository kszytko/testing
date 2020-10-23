#pragma once

#include <string>

class PrinterStream {
public:
    virtual ~PrinterStream() {}
    virtual void print(const std::string& stringToPrint) = 0;
    virtual void print(size_t valueToPrint) = 0;
};
