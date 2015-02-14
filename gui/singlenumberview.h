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

#ifndef SINGLENUMBERVIEW_H
#define SINGLENUMBERVIEW_H

#include "lotviewtextasmain.h"

namespace Ui {
class SingleNumberView;
}

class SingleNumberView : public LotViewTextAsMain
{
    Q_OBJECT

public:
    explicit SingleNumberView(const QString& longestText, QWidget *parent = 0);
    ~SingleNumberView();

    void view(const NumberLotElement& numberLotElement, const int& id);

protected:
    virtual void calcViewSize();

private:
    Ui::SingleNumberView *ui;

    void calcLocalFontSize(const QFont& font);
};

#endif // SINGLENUMBERVIEW_H
