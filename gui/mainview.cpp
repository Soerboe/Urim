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
#include "randomcolorgenerator.h"
#include "colorlotelementview.h"

using namespace std;

MainView::MainView(DrawingController* controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    _drawingController(controller)
{
    ui->setupUi(this);

    // TODO remove this testing setup code
    shared_ptr<DrawingSession> session(new DrawingSession(true));
    session->addGenerator(shared_ptr<RandomGenerator> (new RandomNumberGenerator(1, 2)));

    vector<Color> colors;
    colors.push_back(Color(255, 0, 0, "Rød"));
    colors.push_back(Color(0, 255, 0, "Grønn"));
    colors.push_back(Color(0, 0, 255, "Blå"));
    shared_ptr<RandomColorGenerator> colorGenerator (new RandomColorGenerator(colors));
    session->addGenerator(colorGenerator);

    _drawingController->setDrawingSession(session);

    shared_ptr<LotViewer> viewer(new LotViewer);
    NumberLotElementView* view = new NumberLotElementView("Tall");
    viewer->addView(0, view);
    ColorLotElementView* colorView = new ColorLotElementView("Farge");
    viewer->addView(1, colorView);
    ui->verticalLayout->addWidget(view);
    ui->verticalLayout->addWidget(colorView);
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
