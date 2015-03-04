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

#include "configurecolorandnumberdialog.h"
#include "ui_configuredrawingdialog.h"
#include "configurecolorwidget.h"
#include <QGroupBox>

ConfigureColorAndNumberDialog::ConfigureColorAndNumberDialog(const QString name)
    : ConfigureDrawingDialog(name),
      _configureColorWidget(new ConfigureColorWidget),
      _configureNumberWidget(new ConfigureNumberWidget)
{
    QGroupBox* colorGroup = new QGroupBox(tr("Color"));
    QVBoxLayout* colorLayout = new QVBoxLayout();
    colorLayout->addWidget(_configureColorWidget);
    colorGroup->setLayout(colorLayout);
    ui->mainLayout->insertWidget(0, colorGroup);

    QGroupBox* numberGroup = new QGroupBox(tr("Number"));
    QVBoxLayout* numberLayout = new QVBoxLayout();
    numberLayout->addWidget(_configureNumberWidget);
    numberGroup->setLayout(numberLayout);
    ui->mainLayout->insertWidget(1, numberGroup);

    adjustSize();
}

void ConfigureColorAndNumberDialog::init(const std::vector<Color>& colors, QString colorLabel, int min, int max, QString numberLabel, bool uniqueResults)
{
    ConfigureDrawingDialog::init(uniqueResults);
    _configureColorWidget->init(colors, colorLabel);
    _configureNumberWidget->init(min, max, numberLabel);
}

bool ConfigureColorAndNumberDialog::validate()
{
    return _configureColorWidget->validate() && _configureNumberWidget->validate();
}

QString ConfigureColorAndNumberDialog::validationError()
{
    if (!_configureColorWidget->validate()) {
        return _configureColorWidget->validationError();
    } else if (!_configureNumberWidget->validate()) {
        return _configureNumberWidget->validationError();
    } else {
        return QString();
    }
}

std::vector<Color> ConfigureColorAndNumberDialog::colors()
{
    return _configureColorWidget->colors();
}

QString ConfigureColorAndNumberDialog::colorLabel()
{
    return _configureColorWidget->colorLabel();
}

