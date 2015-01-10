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

#ifndef COLORLOTELEMENT_H
#define COLORLOTELEMENT_H

#include "lotelement.h"
#include "color.h"

class ColorLotElement : public LotElement
{
public:
    ColorLotElement(const Color& color);
    virtual void view(LotElementViewer &viewer);
    virtual bool operator==(const LotElement& that);
    virtual bool operator!=(const LotElement& that);

    Color color() const {return _color;}
private:
    Color _color;
};

#endif // COLORLOTELEMENT_H
