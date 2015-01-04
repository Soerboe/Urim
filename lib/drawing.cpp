#include "drawing.h"

Drawing::Drawing()
{
}

void Drawing::addLot(const std::shared_ptr<Lot> lot)
{
    _lots.append(lot);
}

bool Drawing::operator==(const Drawing &that)
{
    if (this->_lots.size() != that._lots.size()) {
        return false;
    }

    for(int i = 0; i < this->_lots.size(); ++i) {
        if ((*this->_lots.at(i)) != (*that._lots.at(i))) {
            return false;
        }
    }

    return true;
}
