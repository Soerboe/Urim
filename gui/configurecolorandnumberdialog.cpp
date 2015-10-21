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
#include <QRadioButton>
#include "colorandnumberview_pog.h"
#include "colorandnumberview_border.h"
#include "colors.h"
#include "colorlotelement.h"
#include "numberlotelement.h"
#include "lotviewselector.h"

ConfigureColorAndNumberDialog::ConfigureColorAndNumberDialog(const QString name)
    : ConfigureDrawingDialog(name),
      _configureColorWidget(new ConfigureColorWidget(false)),
      _configureNumberWidget(new ConfigureNumberWidget(false))
{
    ui->setupLayout->insertWidget(0, _configureColorWidget);
    ui->setupLayout->insertWidget(1, _configureNumberWidget);

    setupViewsTab();
    adjustSize();
}

void ConfigureColorAndNumberDialog::setupViewsTab()
{
    _lotViewSelector = new LotViewSelector();
    ColorAndNumberView_POG* pogView = new ColorAndNumberView_POG("1000");
    Colors colors;
    pogView->view(ColorLotElement(colors.red()), 0);
    pogView->view(NumberLotElement(712), 0);
    _lotViewSelector->addView(pogView);

    ColorAndNumberView_Border* borderView = new ColorAndNumberView_Border();
    borderView->view(ColorLotElement(colors.red()), 0);
    borderView->view(NumberLotElement(712), 0);
    _lotViewSelector->addView(borderView);

    ui->viewsLayout->insertWidget(0, _lotViewSelector);
}

void ConfigureColorAndNumberDialog::init(
        const std::vector<Color>& colors,
        QString colorLabel,
        int min,
        int max,
        QString numberLabel,
        bool uniqueResults,
        int viewIndex)
{
    ConfigureDrawingDialog::init(uniqueResults);
    _configureColorWidget->init(colors, colorLabel);
    _configureNumberWidget->init(min, max, numberLabel);
    _lotViewSelector->init(viewIndex);
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

