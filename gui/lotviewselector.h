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

#ifndef LOTVIEWSELECTOR_H
#define LOTVIEWSELECTOR_H

#include <QWidget>

class QButtonGroup;
class LotView;

namespace Ui {
class LotViewSelector;
}

class LotViewSelector : public QWidget
{
    Q_OBJECT

public:
    explicit LotViewSelector(QWidget *parent = 0);
    ~LotViewSelector();

    void init(int viewIndex);
    void addView(LotView* lotView);
    int selectedViewIndex();

private:
    Ui::LotViewSelector *ui;
    QButtonGroup* _radioGroup;
};

#endif // LOTVIEWSELECTOR_H
