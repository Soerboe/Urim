#ifndef COLORLOT_H
#define COLORLOT_H

#include "lot.h"
#include "color.h"

class ColorLot : public Lot
{
public:
    ColorLot(const Color& color);
    virtual void view(LotViewer &viewer);
    virtual bool operator==(const Lot& that);
    virtual bool operator!=(const Lot& that);

    Color color() const {return _color;}
private:
    Color _color;
};

#endif // COLORLOT_H
