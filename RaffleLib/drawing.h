#ifndef DRAWING_H
#define DRAWING_H

#include <QList>
#include <memory>
#include "lot.h"

class Drawing
{
public:
    Drawing();

    void addLot(const std::shared_ptr<Lot> lot);
    bool operator==(const Drawing& that);

private:
    QList<std::shared_ptr<Lot> > _lots;
};

#endif // DRAWING_H
