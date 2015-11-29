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
#include <QSvgWidget>

using namespace std;

DrawingSetupDialog::DrawingSetupDialog(DrawingSetupController* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawingSetupDialog),
    _controller(controller)
{
    ui->setupUi(this);
    setWindowTitle(tr("Setup drawing"));

    QSvgWidget* svg = new QSvgWidget(":/gui/icons/lots.svg");
    svg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    svg->setFixedSize(64, 64);
    ui->headerLayout->insertWidget(0, svg);

    setupConfigurations();

    connect(ui->createButton, SIGNAL(clicked()), SLOT(createClicked()));
    connect(ui->quitButton, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->drawingTypeSelector, SIGNAL(currentIndexChanged(int)), SLOT(configurationChanged(int)));
    connect(ui->configureButton, SIGNAL(clicked()), SLOT(configureClicked()));
}

DrawingSetupDialog::~DrawingSetupDialog()
{
    delete ui;
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

QString DrawingSetupDialog::getDrawingName()
{
    return ui->nameEdit->text();
}

void DrawingSetupDialog::createClicked()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;

    if (selectedConfiguration == -1) {
        QMessageBox::warning(this, tr("No type of drawing chosen"), tr("Please choose a type of drawing."));
    } else {
        shared_ptr<Configuration> configuration = _controller->at(selectedConfiguration);
        if (configuration->isValid()) {
            accept();
        }
    }
}

void DrawingSetupDialog::configurationChanged(int index)
{
    bool configurationChoosen = index > 0;
    bool configurable = false;
    ui->createButton->setEnabled(configurationChoosen);
    if (configurationChoosen) {
        shared_ptr<Configuration> configuration = _controller->at(index - 1);
        configurable = configuration->configurable();
        ui->summary->setHtml(configuration->summary());
    } else {
        ui->summary->clear();
    }

    ui->configureButton->setEnabled(configurable);
}

void DrawingSetupDialog::configureClicked()
{
    int selectedConfiguration = ui->drawingTypeSelector->currentIndex() - 1;
    if (selectedConfiguration >= 0) {
        shared_ptr<Configuration> configuration = _controller->at(selectedConfiguration);
        configuration->configure();
        ui->summary->setHtml(configuration->summary());
    }
}

void DrawingSetupDialog::setupConfigurations()
{
    ui->drawingTypeSelector->addItem(tr("Choose a type of drawing:"));

    for(int i = 0; i < _controller->configurationsCount(); ++i) {
        ui->drawingTypeSelector->addItem(_controller->at(i)->name());
    }
}
