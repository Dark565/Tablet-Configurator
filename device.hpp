#include <string>
#include "EWL/Definitions/Objects/array.hpp"

#include <EWL/Graphics/Display/display.hpp>

struct Device {
    protected:
    
    int ID;
    uint32_t type;

    public:

    ewl::Array<int, 4> getArea();
    void setArea(const ewl::Array<int, 4>&);
    void resetDefault();
    void mapToOutput(const ewl::Monitor&);

    friend class Tablet;
};