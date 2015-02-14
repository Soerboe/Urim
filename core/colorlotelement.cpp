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

#include "colorlotelement.h"
#include "lotelementviewer.h"
#include <typeinfo>

using namespace std;

ColorLotElement::ColorLotElement(const Color &color)
    : _color(color)
{
}

void ColorLotElement::view(LotElementViewer &viewer, int id)
{
    viewer.view(*this, id);
}

bool ColorLotElement::operator==(const LotElement& that)
{
    try {
        const ColorLotElement& thatColorLotElement = dynamic_cast<const ColorLotElement&>(that);
        return this->_color == thatColorLotElement._color;
    } catch(bad_cast& e) {
        return false;
    }
}

bool ColorLotElement::operator!=(const LotElement& that)
{
    return !(*this == that);
}

void ColorLotElement::print(ostream& output) const
{
    output << "Color: " << _color.name.toStdString() << "(" <<
              _color.red << ", " << _color.green << ", " << _color.blue << ")";
}
