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
#include "lot.h"

class RandomGenerator;

class DrawingSession
{
public:
    DrawingSession(bool uniqueResults = false);

    Lot draw();
    unsigned long numberOfUniqueResults();
    int lotsCount() {return _lots.size();}

    void addGenerator(std::shared_ptr<RandomGenerator> generator);
    int generatorsCount() const {return _generators.size();}
    std::shared_ptr<RandomGenerator> generatorsAt(int i) {return _generators.at(i);}

private:
    QString _name;
    bool _uniqueResults;
    QList<std::shared_ptr<RandomGenerator> > _generators;
    QList<Lot> _lots;

    Lot drawNonUnique();
    Lot drawUnique();
    Lot doDraw();
};

#endif // DRAWINGSESSION_H
