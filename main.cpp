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

    d.resetDefault();

    ql::Display display; ql::Monitor monitor;
    display.getMonitor(0,monitor);

    d.mapToOutput(monitor);
}

    