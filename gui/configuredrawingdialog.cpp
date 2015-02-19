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
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <limits>

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

bool ConfigureDrawingDialog::uniqueResults()
{
    return ui->uniqueResults->isChecked();
}

void ConfigureDrawingDialog::okClicked()
{
    if (validate()) {
        accept();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("All fields must be filled out correctly"));
    }
}


ConfigureNumberWidget::ConfigureNumberWidget(QWidget* parent)
    :QWidget(parent)
{
    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->addWidget(new QLabel(tr("Label:")));
    _label = new QLineEdit();
    labelLayout->addWidget(_label);
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

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->insertLayout(0, minMaxLayout);
    mainLayout->insertLayout(1, labelLayout);
    setLayout(mainLayout);
}

void ConfigureNumberWidget::init(int min, int max, QString label)
{
    _minSpin->setValue(min);
    _maxSpin->setValue(max);
    _label->setText(label);
}

bool ConfigureNumberWidget::validate()
{
    return _minSpin->value() <= _maxSpin->value();
}

int ConfigureNumberWidget::min()
{
    return _minSpin->value();
}

int ConfigureNumberWidget::max()
{
    return _maxSpin->value();
}

QString ConfigureNumberWidget::label()
{
    return _label->text();
}
