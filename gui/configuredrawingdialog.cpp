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

#include "configuredrawingdialog.h"
#include "ui_configuredrawingdialog.h"
#include <QMessageBox>

ConfigureDrawingDialog::ConfigureDrawingDialog(const QString name, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ConfigureDrawingDialog),
    _uniqueResults(false)
{
    ui->setupUi(this);
    setWindowTitle(tr("Configure drawing: ") + name);
    connect(ui->okButton, SIGNAL(clicked()), SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

ConfigureDrawingDialog::~ConfigureDrawingDialog()
{
    delete ui;
}

void ConfigureDrawingDialog::init(bool uniqueResults)
{
    ui->uniqueResults->setChecked(uniqueResults);
}

void ConfigureDrawingDialog::prepareResults()
{
    _uniqueResults = ui->uniqueResults->isChecked();
}

void ConfigureDrawingDialog::okClicked()
{
    if (validate()) {
        prepareResults();
        accept();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("All fields must be filled out correctly"));
    }
}
