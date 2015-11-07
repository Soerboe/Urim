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

#include "colorandnumberview_border.h"
#include "numberlotelement.h"
#include "colorlotelement.h"

ColorAndNumberView_Border::ColorAndNumberView_Border(QWidget *parent) :
    TwoTextsView(parent)
{
    showBorder(true);
}

void ColorAndNumberView_Border::view(const NumberLotElement& numberLotElement, int id)
{
    ignore_unused(id);

    setBottomText(QString::number(numberLotElement.number()));
}

void ColorAndNumberView_Border::view(const ColorLotElement& colorLotElement, int id)
{
    ignore_unused(id);

    setBorderColor(colorLotElement.color());
    setTopText(colorLotElement.color().name);
}
