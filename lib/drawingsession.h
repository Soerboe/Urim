/*
 * Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DRAWINGSESSION_H
#define DRAWINGSESSION_H

#include <QString>
#include "drawing.h"

class RandomGenerator;

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

    unsigned long numberOfUniqueResults();

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
