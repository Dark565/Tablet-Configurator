#include "memory.hpp"

#include <stdlib.h>
#include <iostream>

bool memory::check_interval(const void* mem, uint32_t size, uint8_t st, uint8_t en) {
    if(mem != NULL && st < en) {
        uint8_t* b_ptr = (uint8_t*)mem;
        for(uint32_t i = 0; i < size; i++) {
            if(!(b_ptr[i] >= st && b_ptr[i] <= en)) return false;
        }
        return true;
    }
    return false;
}