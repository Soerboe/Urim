#ifndef DRAWINGSESSION_H
#define DRAWINGSESSION_H

#include <qstring.h>
#include "drawing.h"

/**
 * @brief Trekningsrunde
 */
class DrawingSession
{
public:
    DrawingSession();

    Drawing draw();

private:
    QString _name;
    QList<Drawing> _drawings;

};

#endif // DRAWINGSESSION_H
