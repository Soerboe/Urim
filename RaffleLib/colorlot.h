#ifndef COLORLOT_H
#define COLORLOT_H

#include "lot.h"

class ColorLot : public Lot
{
public:
    ColorLot();

    virtual void view(LotViewer &viewer);
};

#endif // COLORLOT_H
