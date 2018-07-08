#include <string>
#include "array.hpp"

#include <QL/Graphics/Display/display.hpp>

struct Device {
    protected:
    
    int ID;
    uint32_t type;

    public:

    Array<int, 4> getArea();
    void setArea(const Array<int, 4>& area);
    void setDefafaultArea();
    void mapToOutput();

    friend class Tablet;
};