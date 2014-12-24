#ifndef NUMBERLOT_H
#define NUMBERLOT_H

#include "lot.h"

class NumberLot : public Lot
{
public:
    NumberLot(const int number);
    virtual void view(LotViewer &viewer);
    virtual bool operator==(const Lot& that);
    virtual bool operator!=(const Lot& that);

    int number() const {return _number;}
private:
    int _number;
};

#endif // NUMBERLOT_H
