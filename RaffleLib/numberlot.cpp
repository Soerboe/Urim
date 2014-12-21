#include "numberlot.h"

NumberLot::NumberLot(int number)
    : _number(number)
{
}

void NumberLot::view(LotViewer &viewer)
{
    viewer.view(this);
}
