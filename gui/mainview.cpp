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

#include "mainview.h"
#include "ui_mainview.h"
#include <QTimer>
#include "drawingsetupdialog.h"
#include "lotlogger.h"
#include "lotviewer.h"
#include "lotelementview.h"

using namespace std;

MainView::MainView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    _drawingController(controller),
    _setupDialog(setupDialog)
{
    ui->setupUi(this);
    ui->logWidget->setVisible(false);
    QStringList headerLabels;
    headerLabels << tr("No.") << tr("Time") << tr("Lot");
    ui->logWidget->setColumnCount(headerLabels.size());
    ui->logWidget->setHeaderLabels(headerLabels);
    ui->logWidget->resizeColumnToContents(0);

    shared_ptr<LotLogger> logger(new LotLogger(ui->logWidget));
    _drawingController->setLotLogger(logger);

    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    connect(ui->showLogCheckBox, SIGNAL(toggled(bool)), SLOT(showLogChecked(bool)));

    QTimer::singleShot(0, this, SLOT(showDrawingSetup()));
}

MainView::~MainView()
{
    delete ui;
}

void MainView::showDrawingSetup()
{
    int status = _setupDialog->exec(true);

    if (status == QDialog::Accepted) {
        _drawingController->setDrawingSession(_setupDialog->getDrawingSession());
        shared_ptr<LotViewer> viewer = _setupDialog->getViewer();
        for (int i = 0; i < viewer->countViews(); ++i) {
            ui->verticalLayout->addWidget(viewer->at(i));
        }
        _drawingController->setLotViewer(viewer);

        this->show();
    } else {
        qApp->exit(0);
    }

}

void MainView::drawClicked()
{
    _drawingController->draw();
}

void MainView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}
