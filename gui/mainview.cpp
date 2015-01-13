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

// TODO fjern disse
#include "randomnumbergenerator.h"
#include "lotelementview.h"
#include "lotviewer.h"
#include "numberlotelementview.h"

MainView::MainView(DrawingController* controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    _drawingController(controller)
{
    ui->setupUi(this);

    // TODO remove this testing setup code
    std::shared_ptr<DrawingSession> session(new DrawingSession(true));
    session->addGenerator(std::shared_ptr<RandomGenerator> (new RandomNumberGenerator(1, 1000)));
    _drawingController->setDrawingSession(session);

    std::shared_ptr<LotViewer> viewer(new LotViewer);
    std::shared_ptr<NumberLotElementView> view(new NumberLotElementView("test"));
    viewer->addView(0, view);
    ui->verticalLayout->addWidget(view.get());
    _drawingController->setLotViewer(viewer);

    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    //QTimer::singleShot(0, this, SLOT(showDrawingSetup()));
}

MainView::~MainView()
{
    delete ui;
}

void MainView::showDrawingSetup()
{
    DrawingSetupDialog dialog;
    int status = dialog.exec();

    if (status == QDialog::Accepted) {
        //dialog.createDrawing();
    }
    exit(0);
}

void MainView::drawClicked()
{
    _drawingController->draw();
}
