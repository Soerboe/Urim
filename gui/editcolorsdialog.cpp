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

#include "editcolorsdialog.h"
#include "ui_editcolorsdialog.h"
#include "editcolorswidget.h"

EditColorsDialog::EditColorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditColorsDialog),
    _editWidget(new EditColorsWidget)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, _editWidget);

    connect(ui->cancelButton, &QPushButton::clicked, this, &EditColorsDialog::reject);
    connect(ui->saveButton, &QPushButton::clicked, this, &EditColorsDialog::saveClicked);
}

EditColorsDialog::~EditColorsDialog()
{
    delete ui;
}

void EditColorsDialog::saveClicked()
{
    _editWidget->saveColorsToSettings();
    accept();
}
