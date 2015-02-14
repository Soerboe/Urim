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
#include <QMessageBox>

using namespace std;

DrawingSetupDialog::DrawingSetupDialog(DrawingSetupController* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawingSetupDialog),
    _controller(controller)
{
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName());
    ui->header->setStyleSheet("#header {border: 1px solid #ff8522;}");
    ui->summary->setStyleSheet("#summary {border: 1px solid #ff8522;}");
    ui->createButton->setStyleSheet("#createButton {background-color: #ff8522;}");

    setupConfigurations();

    connect(ui->createButton, SIGNAL(clicked()), SLOT(createClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->drawingTypeSelector, SIGNAL(currentIndexChanged(int)), SLOT(configurationChanged(int)));
    connect(ui->configureButton, SIGNAL(clicked()), SLOT(configureClicked()));
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

shared_ptr<DrawingSession> DrawingSetupDialog::getDrawingSession()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    return _controller->at(selectedConfiguration)->createDrawingSession();
}

LotView* DrawingSetupDialog::getView()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    return _controller->at(selectedConfiguration)->createView();
}

void DrawingSetupDialog::createClicked()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;

    if (selectedConfiguration == -1) {
        QMessageBox::warning(this, tr("No type of drawing chosen"), tr("Please choose a type of drawing."));
    } else {
        shared_ptr<DrawingConfiguration> configuration = _controller->at(selectedConfiguration);
        if (configuration->isValid()) {
            accept();
        }
    }
}

void DrawingSetupDialog::configurationChanged(int index)
{
    bool configurationChoosen = index > 0;
    ui->configureButton->setEnabled(configurationChoosen);
    ui->createButton->setEnabled(configurationChoosen);
    if (index > 0) {
        shared_ptr<DrawingConfiguration> configuration = _controller->at(index - 1);
        ui->summary->setHtml(configuration->summary());
    } else {
        ui->summary->clear();
    }
}

void DrawingSetupDialog::configureClicked()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    if (selectedConfiguration >= 0) {
        shared_ptr<DrawingConfiguration> configuration = _controller->at(selectedConfiguration);
        configuration->configure();
        ui->summary->setHtml(configuration->summary());
    }
}

void DrawingSetupDialog::setupConfigurations()
{
    ui->drawingTypeSelector->addItem(tr("Choose a type of drawing:"));

    for(int i = 0; i < _controller->countConfigurations(); ++i) {
        ui->drawingTypeSelector->addItem(_controller->at(i)->name());
    }
}
