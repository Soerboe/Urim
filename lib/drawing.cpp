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

#include "drawing.h"
#include "lot.h"

Drawing::Drawing()
{
}

void Drawing::addLot(const std::shared_ptr<Lot> lot)
{
    _lots.append(lot);
}

bool Drawing::operator==(const Drawing &that)
{
    if (this->_lots.size() != that._lots.size()) {
        return false;
    }

    for(int i = 0; i < this->_lots.size(); ++i) {
        if ((*this->_lots.at(i)) != (*that._lots.at(i))) {
            return false;
        }
    }

    return true;
}
