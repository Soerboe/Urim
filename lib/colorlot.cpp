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

#include "colorlot.h"
#include "lotviewer.h"

ColorLot::ColorLot(const Color &color)
    : _color(color)
{
}

void ColorLot::view(LotViewer &viewer)
{
    viewer.view(this);
}

bool ColorLot::operator==(const Lot& that)
{
    try {
        const ColorLot& thatColorLot = dynamic_cast<const ColorLot&>(that);
        return this->_color == thatColorLot._color;
    } catch(std::bad_cast& e) {
        return false;
    }
}

bool ColorLot::operator!=(const Lot& that)
{
    return !(*this == that);
}
