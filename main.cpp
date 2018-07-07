#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "tablet.hpp"
#include "array.hpp"

int main(int argc, char** argv) {
    Tablet t;

    Device d = t.getFirst(STYLUS);

    Array<int,4> area;
    try {
        area = d.getArea();
    }
    catch(std::string& s) {
        std::cout << '\n' << s << '\n';
    }

    for(uint32_t i = 0; i < 4; i++) {
        std::cout << area[i] << '\n';
    }
}