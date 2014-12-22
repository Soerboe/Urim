#ifndef DRAWING_H
#define DRAWING_H

#include <QList>
#include <memory>
#include "lot.h"

class Drawing
{
public:
    Drawing();

    void addLot(std::shared_ptr<Lot> lot);

private:
    QList<std::shared_ptr<Lot> > _lots;
};

#endif // DRAWING_H
