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

#include "configureamountwidget.h"
#include <limits>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>

ConfigureAmountWidget::ConfigureAmountWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* l = new QVBoxLayout;
    l->setMargin(0);
    setLayout(l);
}

void ConfigureAmountWidget::addAmountSelector(const QString& name, const QString& description, int initialValue)
{
    QSpinBox* spin = new QSpinBox();
    spin->setMinimum(1);
    spin->setMaximum(INT_MAX);
    spin->setValue(initialValue);
    spin->setButtonSymbols(QSpinBox::PlusMinus);
    spin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    spin->setMinimumWidth(100);
    _spins.append(spin);
    QLabel* n = new QLabel(name);
    QFont f = n->font();
    f.setPointSize(12);
    n->setFont(f);
    layout()->addWidget(n);
    QLabel* d = new QLabel(description);
    f.setPointSize(10);
    d->setFont(f);
    layout()->addWidget(d);
    layout()->addWidget(spin);

    connect(spin, SIGNAL(valueChanged(int)), SLOT(handleChanges()));
}

int ConfigureAmountWidget::amount(int index) const
{
    if (index >= 0 && index < _spins.size()) {
        return _spins.at(index)->value();
    } else {
        return -1;
    }
}

void ConfigureAmountWidget::handleChanges()
{
    emit changed();
}
