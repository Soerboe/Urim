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

#include "lot.h"
#include "lotelement.h"
#include "utils.h"

using namespace std;

Lot::Lot()
{
}

void Lot::addLotElement(const shared_ptr<LotElement> lotElement)
{
    _lotElements.append(lotElement);
}

void Lot::view(LotElementViewer& viewer)
{
    for (int i = 0; i < _lotElements.size(); ++i) {
        _lotElements.at(i)->view(viewer, i);
    }
}

shared_ptr<LotElement> Lot::at(int index) const
{
    return _lotElements.at(index);
}

size_t Lot::count() const
{
    return _lotElements.count();
}

size_t Lot::hash() const
{
    size_t seed = 0x1f73a8ce;
    for (int i = 0; i < _lotElements.size(); ++i) {
        hash_combine_custom(seed, *_lotElements.at(i));
    }

    return seed;
}

bool operator==(const Lot& a, const Lot& b)
{
    if (a._lotElements.size() != b._lotElements.size()) {
        return false;
    }

    for(int i = 0; i < a._lotElements.size(); ++i) {
        if ((*a._lotElements.at(i)) != (*b._lotElements.at(i))) {
            return false;
        }
    }

    return true;
}

bool operator!=(const Lot& a, const Lot& b)
{
    return !(a == b);
}

ostream& operator<<(ostream& output, const Lot& lot)
{
    output << "Lot[";
    for(int i = 0; i < lot._lotElements.size(); ++i) {
        if (i > 0) {
            output << ", ";
        }
        output << *(lot._lotElements.at(i));
    }

    output << "]";
    return output;
}
