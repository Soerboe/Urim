#ifndef DRAWINGSESSION_H
#define DRAWINGSESSION_H

#include <qstring.h>
#include "drawing.h"
#include "randomgenerator.h"

/**
 * @brief Trekningsrunde
 */
class DrawingSession
{
public:
    DrawingSession(bool uniqueResults = false);

    Drawing draw();
    void addGenerator(std::shared_ptr<RandomGenerator> generator);
    QList<Drawing> drawings() const {return _drawings;}

private:
    QString _name;
    bool _uniqueResults;
    QList<std::shared_ptr<RandomGenerator> > _generators;
    QList<Drawing> _drawings;

    Drawing drawNonUnique();
    Drawing drawUnique();
    Drawing doDraw();
};

#endif // DRAWINGSESSION_H
