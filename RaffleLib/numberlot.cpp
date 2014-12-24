#include <typeinfo>
#include "numberlot.h"

NumberLot::NumberLot(const int number)
    : _number(number)
{
}

void NumberLot::view(LotViewer &viewer)
{
    viewer.view(this);
}

bool NumberLot::operator==(const Lot& that)
{
    try {
        const NumberLot& thatNumberLot = dynamic_cast<const NumberLot&>(that);
        return this->_number == thatNumberLot._number;
    } catch(std::bad_cast& e) {
        return false;
    }
}

bool NumberLot::operator!=(const Lot& that)
{
    return !(*this == that);
}
