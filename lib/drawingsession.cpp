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

#include "drawingsession.h"
#include "nomoreuniqueresultsexception.h"
#include "randomgenerator.h"

using namespace std;

DrawingSession::DrawingSession(bool uniqueResults)
    : _uniqueResults(uniqueResults)
{
}

Drawing DrawingSession::draw()
{
    return _uniqueResults ? drawUnique() : drawNonUnique();
}

void DrawingSession::addGenerator(shared_ptr<RandomGenerator> generator)
{
    _generators.append(generator);
}

Drawing DrawingSession::drawNonUnique()
{
    Drawing drawing = doDraw();
    _drawings.append(drawing);
    return drawing;
}

Drawing DrawingSession::drawUnique()
{
    Drawing drawing;

    if ((unsigned long) _drawings.size() >= numberOfUniqueResults()) {
        throw NoMoreUniqueResultsException();
    }

    do {
        drawing = doDraw();
    } while (_drawings.contains(drawing));

    _drawings.append(drawing);
    return drawing;
}

Drawing DrawingSession::doDraw()
{
    Drawing drawing;

    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        shared_ptr<LotElement> lotElement = (*generator)();
        drawing.addLotElement(lotElement);
    }

    return drawing;
}

unsigned long DrawingSession::numberOfUniqueResults()
{
    unsigned long count = 1;
    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        count *= generator->numberOfUniqueResults();
    }

    return count;
}
