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

#include "colorlotelementview.h"
#include "colorlotelement.h"
#include <QPalette>
#include "color.h"

ColorLotElementView::ColorLotElementView(const QString name)
    : LotElementView(name)
{
    _colorView = new QFrame;
    _colorView->setAutoFillBackground(true);
    _textView = new QLabel;
    _layout->addWidget(_colorView);
    _layout->addWidget(_textView);
}

ColorLotElementView::~ColorLotElementView()
{
    delete _colorView;
    delete _textView;
}

void ColorLotElementView::update(const ColorLotElement& colorLotElement)
{
    Color color = colorLotElement.color();
    QPalette palette = _colorView->palette();
    palette.setColor(backgroundRole(), QColor(color.red, color.green, color.blue));
    _colorView->setPalette(palette);

    _textView->setText(color.name);
}
