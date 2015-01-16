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

#include "randomnumbergenerator.h"
#include "numberlotelement.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator(int min, int max)
    : _dist(min, max)
{
}

shared_ptr<LotElement> RandomNumberGenerator::generate()
{
    return shared_ptr<LotElement>(new NumberLotElement(doGenerate()));
}

unsigned long RandomNumberGenerator::numberOfUniqueResults() const
{
    return _dist.max() - _dist.min() + 1;
}

int RandomNumberGenerator::doGenerate()
{
    return _dist(_rng);
}
