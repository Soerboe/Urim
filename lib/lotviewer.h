#ifndef LOTVIEWER_H
#define LOTVIEWER_H

class NumberLot;
class ColorLot;

class LotViewer
{
public:
    virtual void view(const NumberLot* numberLot) = 0;
    virtual void view(const ColorLot* colorLot) = 0;
};

#endif // LOTVIEWER_H
