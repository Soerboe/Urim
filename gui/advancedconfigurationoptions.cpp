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

#include "advancedconfigurationoptions.h"
#include "ui_advancedconfigurationoptions.h"
#include <QMessageBox>

AdvancedConfigurationOptions::AdvancedConfigurationOptions(const QString &title, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::AdvancedConfigurationOptions)
{
    ui->setupUi(this);
    setWindowTitle(QString(title).append(" - ").append(tr("Advanced options")));
    connect(ui->okButton, SIGNAL(clicked()), SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

AdvancedConfigurationOptions::~AdvancedConfigurationOptions()
{
    delete ui;
}

void AdvancedConfigurationOptions::hideSetupTab()
{
    int index = ui->tabWidget->indexOf(ui->setupTab);
    ui->tabWidget->removeTab(index);
}

void AdvancedConfigurationOptions::hideViewsTab()
{
    int index = ui->tabWidget->indexOf(ui->viewsTab);
    ui->tabWidget->removeTab(index);
}

void AdvancedConfigurationOptions::okClicked()
{
    if (validate()) {
        accept();
    } else {
        QString error = validationError();
        if (error.isEmpty()) {
            error = tr("All fields must be filled out correctly");
        }

        QMessageBox::warning(this, tr("Error"), error);
    }
}
