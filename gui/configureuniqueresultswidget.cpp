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

#include "configureuniqueresultswidget.h"
#include "ui_configureuniqueresultswidget.h"

#define YES 0
#define NO 1

ConfigureUniqueResultsWidget::ConfigureUniqueResultsWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ConfigureUniqueResultsWidget)
{
    ui->setupUi(this);

    ui->verticalLayout->setAlignment(Qt::AlignTop);
    ui->buttonGroup->setId(ui->yesRadio, YES);
    ui->buttonGroup->setId(ui->noRadio, NO);
    setChecked(false);
    auto CHANGED = [&]() {emit changed();};
    connect(ui->yesRadio, &QRadioButton::toggled, CHANGED);
    connect(ui->noRadio, &QRadioButton::toggled, CHANGED);
}

void ConfigureUniqueResultsWidget::init(bool unique)
{
    setChecked(unique);
}

bool ConfigureUniqueResultsWidget::uniqueResults()
{
    return ui->buttonGroup->checkedId() != YES;
}

void ConfigureUniqueResultsWidget::setChecked(bool unique)
{
    ui->buttonGroup->button(YES)->setChecked(!unique);
    ui->buttonGroup->button(NO)->setChecked(unique);
}

