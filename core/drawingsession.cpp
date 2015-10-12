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
    : _id(1),
      _uniqueResults(uniqueResults)
{
}

Lot DrawingSession::draw()
{
    return _uniqueResults ? drawUnique() : drawNonUnique();
}

void DrawingSession::addGenerator(shared_ptr<RandomGenerator> generator)
{
    _generators.append(generator);
}

Lot DrawingSession::drawNonUnique()
{
    Lot lot = doDraw();
    _lots.append(lot);
    return lot;
}

Lot DrawingSession::drawUnique()
{
    Lot lot;

    if ((unsigned long) _lots.size() >= numberOfUniqueResults()) {
        throw NoMoreUniqueResultsException();
    }

    do {
        lot = doDraw();
    } while (_lotsSet.find(lot) != _lotsSet.end());

    _lotsSet.insert(lot);
    _lots.append(lot);
    return lot;
}

Lot DrawingSession::doDraw()
{
    Lot lot;

    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        shared_ptr<LotElement> lotElement = (*generator)();
        lot.addLotElement(lotElement);
    }

    return lot;
}

unsigned long DrawingSession::numberOfUniqueResults()
{
    if (_generators.isEmpty()) {
        return 0;
    }

    unsigned long count = 1;
    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        count *= generator->numberOfUniqueResults();
    }

    return count;
}
