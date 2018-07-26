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
#include <QL/Definitions/libs.hpp>

#if defined(__QL_LIBRARY_LINK)
    #define P_LIB_LOAD "t. Linking modules"
#elif defined(__QL_LIBRARY_LOAD)
    #define P_LIB_LOAD "t. Loading modules"
#endif

#define P_VERSION "v.1.0"

#define P_HELP \
"\n\
X11 graphics tablet configuration program\n\
\n\
Usage: 'tablet x0-x1 y0-y1 monitor_index'\n\
Where you can also use '%' after x/y value to get percent from the whole width.\n\
\n\
Example: 'tablet 25%-75% 25%-75% 0' will set your tablet area to the middle of screen mapped to monitor 0.\n\n"

int main(int argc, char** argv) {

    if(argc > 1) {
        if(!strcmp(argv[1],"--version") || !strcmp(argv[1],"-v")) {
            std::cout << P_VERSION << ' ' << __DATE__ << ' ' << __TIME__ << '\n' << P_LIB_LOAD << '\n';
            return 0;
        } else if(!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h")) {
            std::cout << P_HELP;
            return 0;
        } else if(argc > 3) {

            if(ql::Display::init()) {
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
                        std::cerr << "Bad symbols at coordinate: " << i << '\n';
                        return 1;
                    }
                }

                for(uint32_t i = 0; i < 2; i++) {
                    if(n_area[2+i] < n_area[i]) {
                        std::cerr << "Bad sizes: overflow..\n";
                        return 1;
                    }
                }

                t_device.setArea(n_area);
                return 0;   
            }
            else {
                std::cerr << "Cannot load graphic modules..\n";
                return 1;
            }

        }
    }
    
    std::cerr << "There is nothing to do..\n";
    return 1;
}

    