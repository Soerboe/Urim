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

#ifndef NUMBERLOTELEMENTVIEW_H
#define NUMBERLOTELEMENTVIEW_H

#include "lotelementview.h"
#include <QLabel>

class NumberLotElement;

class NumberLotElementView : public LotElementView
{
public:
    NumberLotElementView(const QString &name);
    ~NumberLotElementView();

    void update(const NumberLotElement& numberLotElement);

private:
    QLabel* _elementView;
};

#endif // NUMBERLOTELEMENTVIEW_H
