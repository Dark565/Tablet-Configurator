#pragma once

#include <string>
#include <set>
#include <vector>
#include "device.hpp"

enum devs {
    STYLUS,
    PAD
};

class Tablet {
    
    std::set<int> devs[2];

public:

    bool loadDevices();

    Device getFirst(uint32_t i);

    Tablet(bool l = true);

protected:

    static int getIdFromFile(FILE* f);
    static int getTypeFromFile(FILE* f);

};