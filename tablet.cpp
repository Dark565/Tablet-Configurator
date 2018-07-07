#include "tablet.hpp"

#include "configuration.hpp"
#include "files.hpp"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include <string.h>

bool Tablet::loadDevices() {

    std::string entry = std::string(T_CONF_FILE) + ' ' + T_LIST_FLAG;

    FILE* prog_stream = popen(entry.c_str(), "r");

    if(prog_stream) {

        char d = 0;

        while(!feof(prog_stream)) {
            
            int id = Tablet::getIdFromFile(prog_stream);
            int tp = Tablet::getTypeFromFile(prog_stream);

            if(id >= 0 && tp >= 0) {
                devs[tp].insert(id);
                d = 1;                
            }
            else break;

        }

        pclose(prog_stream);

        return (d);
    }

    return false;
}

int Tablet::getIdFromFile(FILE* f) {

    if(file::scroll(T_OUTPUT_IDS,f)) {
        try {
            return file::txt_to_number(f);
        }
        catch(std::string& s) {
            std::cerr << '\n' << s << '\n';
        }
    }

    return -1;
}

int Tablet::getTypeFromFile(FILE* f) {

    if(file::scroll(T_OUTPUT_TPS,f)) {

        const char* t[] = {T_DEVICE_STYLUS, T_DEVICE_PAD};

        return file::scroll(t,2,f);
    }

    return -1;

}

Device Tablet::getFirst(uint32_t i) {
    Device d;

    d.ID = *devs[i].begin();
    d.type = i;

    return d;
}

Tablet::Tablet(bool l) {
    if(l) {
        loadDevices();
    }
}