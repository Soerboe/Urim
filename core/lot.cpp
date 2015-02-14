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

using namespace std;

Lot::Lot()
{
}

void Lot::addLotElement(const shared_ptr<LotElement> lotElement)
{
    _lotElements.append(lotElement);
}

bool Lot::operator==(const Lot &that)
{
    if (this->_lotElements.size() != that._lotElements.size()) {
        return false;
    }

    for(int i = 0; i < this->_lotElements.size(); ++i) {
        if ((*this->_lotElements.at(i)) != (*that._lotElements.at(i))) {
            return false;
        }
    }

    return true;
}

void Lot::view(LotElementViewer& viewer)
{
    for (int i = 0; i < _lotElements.size(); ++i) {
        _lotElements.at(i)->view(viewer, i);
    }
}

shared_ptr<LotElement> Lot::at(const int& index) const
{
    return _lotElements.at(index);
}

size_t Lot::count() const
{
    return _lotElements.count();
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
