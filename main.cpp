#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "tablet.hpp"
#include "array.hpp"

#include <QL/Graphics/Display/display.hpp>

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

    ql::Display dis;

    ql::Monitor mon;
    dis.getMonitor(0,mon);

    std::cout << '\n' << mon.name;
}