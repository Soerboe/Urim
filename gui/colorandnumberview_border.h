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

#ifndef COLORANDNUMBERVIEW_BORDER_H
#define COLORANDNUMBERVIEW_BORDER_H

#include "verticaltextsview.h"

class ColorAndNumberView_Border : public VerticalTextsView
{
    Q_OBJECT

public:
    explicit ColorAndNumberView_Border(const QString& longestText, QWidget *parent = 0);

    virtual void view(const NumberLotElement& numberLotElement, int id);
    virtual void view(const ColorLotElement& colorLotElement, int id);

};

#endif // COLORANDNUMBERVIEW_BORDER_H
