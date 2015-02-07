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

#include "configuresinglenumberdialog.h"
#include "ui_configuredrawingdialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <limits>
#include <QLineEdit>

ConfigureSingleNumberDialog::ConfigureSingleNumberDialog(const QString name)
    : ConfigureDrawingDialog(name)
{
    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->addWidget(new QLabel(tr("Label:")));
    _labelLabel = new QLineEdit();
    labelLayout->addWidget(_labelLabel);
    QHBoxLayout* minMaxLayout = new QHBoxLayout();
    QLabel* minLabel = new QLabel(tr("Minimum number:"));
    QLabel* maxLabel = new QLabel(tr("Maximum number:"));
    _minSpin = new QSpinBox();
    _minSpin->setMinimum(INT_MIN);
    _minSpin->setMaximum(INT_MAX);
    _minSpin->setValue(1);
    _maxSpin = new QSpinBox();
    _maxSpin->setMinimum(INT_MIN);
    _maxSpin->setMaximum(INT_MAX);
    _maxSpin->setValue(10);
    minMaxLayout->addWidget(minLabel);
    minMaxLayout->addWidget(_minSpin);
    minMaxLayout->addWidget(maxLabel);
    minMaxLayout->addWidget(_maxSpin);
    ui->mainLayout->insertLayout(0, minMaxLayout);
    ui->mainLayout->insertLayout(1, labelLayout);
    adjustSize();
}

ConfigureSingleNumberDialog::~ConfigureSingleNumberDialog()
{
}

void ConfigureSingleNumberDialog::init(int min, int max, QString label, bool uniqueResults)
{
    ConfigureDrawingDialog::init(uniqueResults);
    _minSpin->setValue(min);
    _maxSpin->setValue(max);
    _labelLabel->setText(label);
}

bool ConfigureSingleNumberDialog::validate()
{
    return _minSpin->value() <= _maxSpin->value();
}

void ConfigureSingleNumberDialog::prepareResults()
{
    ConfigureDrawingDialog::prepareResults();
    _min = _minSpin->value();
    _max = _maxSpin->value();
    _label = _labelLabel->text();
}

