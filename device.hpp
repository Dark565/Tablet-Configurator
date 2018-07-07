#include <string>
#include "array.hpp"


struct Device {
    protected:
    
    int ID;
    uint32_t type;

    public:

    Array<int, 4> getArea();
    void setArea(const Array<int, 4>& area);

    friend class Tablet;
};