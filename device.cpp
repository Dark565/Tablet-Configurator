#include "device.hpp"

#include "files.hpp"
#include "configuration.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>


Array<int, 4> Device::getArea() {
    char id[4];
    snprintf(id,4,"%i",ID);

    std::string entry = std::string(T_CONF_FILE) + ' ' + T_GET_FLAG + ' ' + id + ' ' + T_AREA_FLAG;

    FILE* p = popen(entry.c_str(), "r");
    if(p) {

        Array<int, 4> ar;
        for(uint32_t i = 0; i < 4; i++) {
            ar[i] = file::txt_to_number(p);
        }

        pclose(p);
        return ar;

    }

    throw std::string("Cannot run: ") + T_CONF_FILE;

}

void Device::setArea(const Array<int, 4>& ar) {
    char id[4];
    snprintf(id,4,"%i",ID);

    std::string entry = std::string(T_CONF_FILE) + ' ' + T_SET_FLAG + ' ' + id + ' ' + T_AREA_FLAG + ' ';

    for(uint32_t i = 0; i < 4; i++) {
        char s[6];

        snprintf(s,6,"%i",ar.x[i]);

        entry += s; entry += ' ';
    }

    FILE* p = popen(entry.c_str(), "r");

    if(p) {
        pclose(p);
    } else {
        throw std::string("Cannot run: ") + T_CONF_FILE;
    }
}

void Device::mapToOutput(const ql::Monitor& m) {
    char id[4];
    snprintf(id,4,"%i",ID);

    std::string entry = std::string(T_CONF_FILE) + ' ' + T_SET_FLAG + ' ' + id + ' ' + T_MAPTOOUTPUT + ' ' + m.name;

    FILE* p = popen(entry.c_str(), "r");
    if(p) {
        pclose(p);
    } else {
        throw std::string("Cannot run: ") + T_CONF_FILE;
    }
}

void Device::resetDefault() {
    char id[4];
    snprintf(id,4,"%i",ID);

    std::string entry = std::string(T_CONF_FILE) + ' ' + T_SET_FLAG + ' ' + id + ' ' + T_RESET_AREA_FLAG;

    FILE* p = popen(entry.c_str(), "r");
    if(p) {
        pclose(p);
    } else {
        throw std::string("Cannot run: ") + T_CONF_FILE;
    }
}