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

Lot::Lot()
{
}

void Lot::addLotElement(const std::shared_ptr<LotElement> lotElement)
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
