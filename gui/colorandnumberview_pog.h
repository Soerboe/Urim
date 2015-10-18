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

#ifndef COLORANDNUMBERVIEW_POG_H
#define COLORANDNUMBERVIEW_POG_H

#include "lotviewtextasmain.h"
#include "color.h"

namespace Ui {
class ColorAndNumberView_POG;
}

class ColorAndNumberView_POG : public LotViewTextAsMain
{
    Q_OBJECT

public:
    explicit ColorAndNumberView_POG(const QString& longestText, QWidget *parent = 0);
    ~ColorAndNumberView_POG();

    virtual void view(const NumberLotElement& numberLotElement, int id);
    virtual void view(const ColorLotElement& colorLotElement, int id);

    void updateView(bool updateColorView = true);
    virtual void showLot(bool visible);
protected:
    virtual void calcViewSize();

private:
    Ui::ColorAndNumberView_POG *ui;

    Color _color;
    int _number;

    void calcLocalFontSize(const QFont& font);

};

#endif // COLORANDNUMBERVIEW_POG_H
