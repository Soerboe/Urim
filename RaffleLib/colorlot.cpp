#include "colorlot.h"

ColorLot::ColorLot(const Color &color)
    : _color(color)
{
}

void ColorLot::view(LotViewer &viewer)
{
    viewer.view(this);
}

bool ColorLot::operator==(const Lot& that)
{
    try {
        const ColorLot& thatColorLot = dynamic_cast<const ColorLot&>(that);
        return this->_color == thatColorLot._color;
    } catch(std::bad_cast& e) {
        return false;
    }
}

bool ColorLot::operator!=(const Lot& that)
{
    return !(*this == that);
}
