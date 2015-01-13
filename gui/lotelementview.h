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

class LotElementView : public QFrame
{
    Q_OBJECT
public:
    explicit LotElementView(const QString& name = QString(), QWidget *parent = 0);
    ~LotElementView();

    virtual void update(const NumberLotElement& numberLotElement) {
        // this method is supposed to be overridden in subclass views wanting NumberLotElements
    }

    virtual void update(const ColorLotElement& colorLotElement) {
        // this method is supposed to be overridden in subclass views wanting ColorLotElements
    }

protected:
    QHBoxLayout* _layout;

private:
    QString _name;
};

#endif // LOTELEMENTVIEW_H
