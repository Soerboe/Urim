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

ConfigureSingleNumberDialog::ConfigureSingleNumberDialog(const QString name)
    : ConfigureDrawingDialog(name),
      _configureNumberWidget(new ConfigureNumberWidget)
{
    ui->mainLayout->insertWidget(0, _configureNumberWidget);
    adjustSize();
}

void ConfigureSingleNumberDialog::init(int min, int max, QString label, bool uniqueResults)
{
    ConfigureDrawingDialog::init(uniqueResults);
    _configureNumberWidget->init(min, max, label);
}

bool ConfigureSingleNumberDialog::validate()
{
    return _configureNumberWidget->validate();
}

