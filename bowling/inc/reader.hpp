#pragma once

#include <vector>
class Lane;

class Reader{
public:
    virtual std::vector<Lane> getLanes() const = 0;
};