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
#include "ui_configureamountwidget.h"
#include <limits>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>

ConfigureAmountWidget::ConfigureAmountWidget(QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureAmountWidget)
{
    ui->setupUi(this);
    ui->groupBox->setTitle(title);
}

ConfigureAmountWidget::~ConfigureAmountWidget()
{
    delete ui;
}

void ConfigureAmountWidget::addAmountSelector(QString name, int initialValue, QString label, QString initialLabel)
{
    QSpinBox* spin = new QSpinBox();
    spin->setValue(initialValue);
    spin->setMinimum(1);
    spin->setMaximum(INT_MAX);
    spin->setButtonSymbols(QSpinBox::PlusMinus);
    ui->formLayout->addRow(name, spin);
    _spins.append(spin);

    QLineEdit* labelEdit = new QLineEdit(initialLabel);
    labelEdit->setPlaceholderText(tr("Label"));
    ui->formLayout->addRow(label, labelEdit);
    _edits.append(labelEdit);
}

void ConfigureAmountWidget::init(int index, int value, QString label)
{
    if (index < 0) {
        return;
    }

    if (index < _spins.size()) {
        _spins.at(index)->setValue(value);
    }

    if (index < _edits.size()) {
        _edits.at(index)->setText(label);
    }
}

int ConfigureAmountWidget::amount(int index) const
{
    if (index >= 0 && index < _spins.size()) {
        return _spins.at(index)->value();
    } else {
        return -1;
    }
}

QString ConfigureAmountWidget::label(int index) const
{
    if (index >= 0 && index < _edits.size()) {
        return _edits.at(index)->text();
    } else {
        return 0;
    }
}
