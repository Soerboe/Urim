#ifndef LOT_H
#define LOT_H

#include "lotviewer.h"

class Lot
{
public:
    Lot();
    virtual void view(LotViewer& viewer) = 0;
    virtual bool operator==(const Lot& that) = 0;
    virtual bool operator!=(const Lot& that) = 0;
};

#endif // LOT_H
