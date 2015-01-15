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
#include "numberlotelement.h"
#include "lotelementviewer.h"

NumberLotElement::NumberLotElement(const int& number)
    : _number(number)
{
}

void NumberLotElement::view(LotElementViewer &viewer, const int& id)
{
    viewer.view(*this, id);
}

bool NumberLotElement::operator==(const LotElement& that)
{
    try {
        const NumberLotElement& thatNumberLotElement = dynamic_cast<const NumberLotElement&>(that);
        return this->_number == thatNumberLotElement._number;
    } catch(std::bad_cast& e) {
        return false;
    }
}

bool NumberLotElement::operator!=(const LotElement& that)
{
    return !(*this == that);
}

void NumberLotElement::print(std::ostream& output) const
{
    output << "Number: " << _number;
}
