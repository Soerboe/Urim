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

#include "drawingsetupdialog.h"
#include "ui_drawingsetupdialog.h"

DrawingSetupDialog::DrawingSetupDialog(DrawingSetupController* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawingSetupDialog),
    _controller(controller)
{
    ui->setupUi(this);

    setupConfigurations();

    connect(ui->createButton, SIGNAL(clicked()), SLOT(createClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

DrawingSetupDialog::~DrawingSetupDialog()
{
    delete ui;
}

int DrawingSetupDialog::exec(bool quitInsteadOfCancel)
{
    ui->cancelButton->setText(quitInsteadOfCancel ? tr("Quit") : tr("Cancel"));
    return QDialog::exec();
}

std::shared_ptr<DrawingSession> DrawingSetupDialog::getDrawingSession()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    return _controller->at(selectedConfiguration)->createDrawingSession();
}

std::shared_ptr<LotViewer> DrawingSetupDialog::getViewer()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    return _controller->at(selectedConfiguration)->createViewer();
}

void DrawingSetupDialog::createClicked()
{
    accept();
}

void DrawingSetupDialog::setupConfigurations()
{
    ui->drawingTypeSelector->addItem(tr("Choose a type of drawing:"));

    for(int i = 0; i < _controller->countConfigurations(); ++i) {
        ui->drawingTypeSelector->addItem(_controller->at(i)->name());
    }
}
