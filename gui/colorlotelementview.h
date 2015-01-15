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

#ifndef COLORLOTELEMENTVIEW_H
#define COLORLOTELEMENTVIEW_H

#include "lotelementview.h"
#include <QFrame>
#include <QLabel>

class ColorLotElement;

class ColorLotElementView : public LotElementView
{
public:
    ColorLotElementView(const QString name = QString());
    ~ColorLotElementView();

    void update(const ColorLotElement& colorLotElement);

private:
    QFrame* _colorView;
    QLabel* _textView;
};

#endif // COLORLOTELEMENTVIEW_H
