#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "tablet.hpp"
#include "array.hpp"
#include "memory.hpp"

#include <QL/Graphics/Display/display.hpp>

int main(int argc, char** argv) {

    if(argc > 3) {
        ql::Display display; ql::Monitor monitor;

        int n = atoi(argv[3]);

        display.getMonitor(n,monitor);


        Tablet tablet;
        Device t_device = tablet.getFirst(STYLUS);

        Array<int, 4> area;

        t_device.resetDefault();
        t_device.mapToOutput(monitor);
        area = t_device.getArea();

        Array<int, 4> n_area(0);

        for(uint32_t i = 0; i < 2; i++) {
            const char* txt = argv[i+1];
            int pos = 0;

            const char* m_pos = strchr(txt,'-');
            if(!m_pos) pos = 1;

            va_getting:

            int t_l = strlen(txt);

            uint32_t sub_size;

            if(m_pos) sub_size = m_pos - txt;
            else sub_size = t_l;

            const char* pnt_pos = (const char*)memchr(txt,'%',sub_size);

            if(pnt_pos)     sub_size = pnt_pos - txt;
            else if(m_pos)  sub_size = m_pos - txt;
            else            sub_size = t_l;

            int ar_p;

            if(memory::check_interval(txt,sub_size,'0','9')) {
                ar_p = atoi(txt);
                if(pnt_pos) {
                    if(ar_p > 100) {
                        n_area[pos*2+i] = area[2+i];
                    } else  {
                        n_area[pos*2+i] = ar_p * area[2+i] / 100;
                    }
                } else {
                    n_area[pos*2+i] = ar_p;
                }

                if(!pos) {

                    txt = m_pos+1;
                    pos = 1;
                    m_pos = NULL;

                    if(*txt != '\0') goto va_getting;

                }


            }
            else {
                std::cerr << "Bad symbols.." << pos << '\n';
                return 1;
            }
        }

        bool eq = 1;

        for(uint32_t i = 0; i < 2; i++) {
            if(n_area[2+i] < n_area[i]) {
                break; 
                eq = 0; 
            }
        }

        if(eq) {
            t_device.setArea(n_area);
        } else {
            std::cerr << "Bad sizes: overflow..\n";
            return 1;
        }

    }
    else {
        std::cerr << "There is nothing to do..\n";
        return 1;
    }

    return 0;
}

    