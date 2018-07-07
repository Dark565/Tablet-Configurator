#include "files.hpp"

#include <stdlib.h>
#include <string.h>
#include <string>

#include <iostream>

int file::scroll(const char** txt, uint32_t size, FILE* f, char break_char) {
    int pos = ftell(f);

    int max_l;

    int* sizes = (int*)calloc(size,sizeof(int));

    for(uint32_t i = 0; i < size; i++) {
        int o_l = strlen(txt[i]);

        sizes[i] = o_l;

        if(!i || o_l > max_l) max_l = o_l;
    }

    if(max_l <= 0) return -1;

    int r = -1;

    char* buffer = (char*)calloc(max_l,1);

    fread(buffer,1,max_l,f);

    while(!feof(f)) {
        for(uint32_t i = 0; i < size; i++) {
            if(!memcmp(buffer, txt[i], sizes[i])) {
                r = i;
                goto end_while;
            }
        }

        if(buffer[max_l-1] == break_char) break;

        if(max_l > 1) memmove(buffer,buffer+1,max_l-1);
        buffer[max_l-1] = fgetc(f);
    }

    end_while:

    free(sizes);
    free(buffer);

    return r;
}

int file::txt_to_number(FILE* f) {
    int num = 0;
    char m = 0;

    while(!feof(f)) {
        char c = fgetc(f);
        
        if(c >= '0' && c <= '9') {
            m |= 2;

            num *= 10;
            num += (c - '0');
        }
        else if(c == '-') {
            m |= 1;
        }
        else if(m & 2) {
            if(m & 1) {
                num = -num;
            }
            return num;
        }
    }
    
    throw std::string("Cannot find number in the file"); 
}