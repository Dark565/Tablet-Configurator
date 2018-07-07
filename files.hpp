#pragma once

#include <stdio.h>
#include <stdint.h>

namespace file {
    int scroll(const char** txt, uint32_t size, FILE* f, char break_char = '\0');
    inline int scroll(const char* txt, FILE* f, char break_char = '\0') {
        return (scroll(&txt, 1, f, break_char) >= 0);  
    }
    int txt_to_number(FILE* f);
}