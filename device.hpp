#include <string>
#include "array.hpp"

#include <QL/Graphics/Display/display.hpp>

struct Device {
    protected:
    
    int ID;
    uint32_t type;

    public:

    Array<int, 4> getArea();
    void setArea(const Array<int, 4>&);
    void resetDefault();
    void mapToOutput(const ql::Monitor&);

    friend class Tablet;
};