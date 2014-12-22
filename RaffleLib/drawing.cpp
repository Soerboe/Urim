#include "drawing.h"

Drawing::Drawing()
{
}

void Drawing::addLot(std::shared_ptr<Lot> lot)
{
    _lots.append(lot);
}
