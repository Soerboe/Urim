#ifndef NUMBERLOT_H
#define NUMBERLOT_H

#include "lot.h"

class NumberLot : public Lot
{
public:
    NumberLot(int number);
    virtual void view(LotViewer &viewer);

    int number() {return _number;}
private:
    int _number;
};

#endif // NUMBERLOT_H
