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

#include "lotview.h"
#include "color.h"

namespace Ui {
class ColorAndNumberView_Border;
}

class ColorAndNumberView_Border : public LotView
{
    Q_OBJECT

public:
    explicit ColorAndNumberView_Border(QWidget *parent = 0);
    ~ColorAndNumberView_Border();

    virtual void view(const NumberLotElement& numberLotElement, const int& id);
    virtual void view(const ColorLotElement& colorLotElement, const int& id);

protected:
    virtual void calcViewSize();

private:
    Ui::ColorAndNumberView_Border *ui;

    bool _drawn;
    Color _borderColor;
    int _borderThickness;

    QString buildStyleSheet();
};

#endif // COLORANDNUMBERVIEW_BORDER_H
