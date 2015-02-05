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

#include "numberlotelementview.h"
#include "numberlotelement.h"

NumberLotElementView::NumberLotElementView()
{
    _view = new QLabel();
    _view->setAlignment(Qt::AlignBaseline | Qt::AlignHCenter);
    _view->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _layout->addWidget(_view);
}

NumberLotElementView::~NumberLotElementView()
{
    delete _view;
}

void NumberLotElementView::update(const NumberLotElement& numberLotElement)
{
    setLabelText(numberLotElement);
    _view->setText(QString::number(numberLotElement.number()));
}
