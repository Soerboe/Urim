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

#ifndef LOTELEMENTVIEW_H
#define LOTELEMENTVIEW_H

#include <QFrame>
#include <QHBoxLayout>
#include "numberlotelement.h"
#include "colorlotelement.h"
#include "utils.h"

class QLabel;

class LotElementView : public QFrame
{
    Q_OBJECT
public:
    explicit LotElementView(QWidget *parent = 0);
    virtual ~LotElementView();

    virtual void update(const NumberLotElement& numberLotElement) {
        ignore_unused(numberLotElement);
        // this method is supposed to be overridden in subclass views wanting NumberLotElements
    }

    virtual void update(const ColorLotElement& colorLotElement) {
        ignore_unused(colorLotElement);
        // this method is supposed to be overridden in subclass views wanting ColorLotElements
    }

protected:
    QHBoxLayout* _layout;
    QLabel* _label;

    void setLabelText(const LotElement& lotElement);

};

#endif // LOTELEMENTVIEW_H
