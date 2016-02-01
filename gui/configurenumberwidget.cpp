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


#include "configurenumberwidget.h"
#include "ui_configurenumberwidget.h"
#include <limits>

ConfigureNumberWidget::ConfigureNumberWidget(bool enableLabel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureNumberWidget)
{
    ui->setupUi(this);

    ui->minSpin->setMinimum(INT_MIN);
    ui->minSpin->setMaximum(INT_MAX);
    ui->minSpin->setValue(1);

    ui->maxSpin->setMinimum(INT_MIN);
    ui->maxSpin->setMaximum(INT_MAX);
    ui->maxSpin->setValue(10);

    if (!enableLabel) {
        ui->useLabel->hide();
        ui->labelEdit->hide();
    }

    connect(ui->minSpin, SIGNAL(valueChanged(int)), SLOT(handleFieldChanged()));
    connect(ui->maxSpin, SIGNAL(valueChanged(int)), SLOT(handleFieldChanged()));
    connect(ui->useLabel, SIGNAL(toggled(bool)), SLOT(handleFieldChanged()));
    connect(ui->labelEdit, SIGNAL(textChanged(QString)), SLOT(handleFieldChanged()));
}

ConfigureNumberWidget::~ConfigureNumberWidget()
{
    delete ui;
}

void ConfigureNumberWidget::init(int min, int max, QString label)
{
    ui->minSpin->setValue(min);
    ui->maxSpin->setValue(max);
    ui->labelEdit->setText(label);
}

bool ConfigureNumberWidget::validate() const
{
    return min() <= max();
}

QString ConfigureNumberWidget::validationError() const
{
    if (!validate()) {
        return tr("Minimum value is larger than maximum value.");
    } else {
        return QString();
    }
}

int ConfigureNumberWidget::min() const
{
    return ui->minSpin->value();
}

int ConfigureNumberWidget::max() const
{
    return ui->maxSpin->value();
}

QString ConfigureNumberWidget::label() const
{
    return ui->labelEdit->text();
}

void ConfigureNumberWidget::handleFieldChanged()
{
    emit changed(validate());
}
