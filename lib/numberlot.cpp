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

#include <typeinfo>
#include "numberlot.h"
#include "lotviewer.h"

NumberLot::NumberLot(const int number)
    : _number(number)
{
}

void NumberLot::view(LotViewer &viewer)
{
    viewer.view(this);
}

bool NumberLot::operator==(const Lot& that)
{
    try {
        const NumberLot& thatNumberLot = dynamic_cast<const NumberLot&>(that);
        return this->_number == thatNumberLot._number;
    } catch(std::bad_cast& e) {
        return false;
    }
}

bool NumberLot::operator!=(const Lot& that)
{
    return !(*this == that);
}
