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
#include "lotlogger.h"

using namespace std;

MainView::MainView(DrawingController* controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    _drawingController(controller)
{
    ui->setupUi(this);
    ui->logWidget->setVisible(false);
    QStringList headerLabels;
    headerLabels << tr("No.") << tr("Time") << tr("Lot");
    ui->logWidget->setColumnCount(headerLabels.size());
    ui->logWidget->setHeaderLabels(headerLabels);
    ui->logWidget->resizeColumnToContents(0);

    // TODO remove this testing setup code
    shared_ptr<DrawingSession> session(new DrawingSession(true));
    shared_ptr<RandomGenerator> g1(new RandomNumberGenerator(1, 1000));
    g1->setName("Nummer");
    session->addGenerator(g1);

    vector<Color> colors;
    colors.push_back(Color(255, 0, 0, "Rød"));
    colors.push_back(Color(0, 255, 0, "Grønn"));
    colors.push_back(Color(0, 0, 255, "Blå"));
    shared_ptr<RandomColorGenerator> colorGenerator (new RandomColorGenerator(colors));
    colorGenerator->setName("Farge");
    session->addGenerator(colorGenerator);

    _drawingController->setDrawingSession(session);

    shared_ptr<LotViewer> viewer(new LotViewer);
    NumberLotElementView* view = new NumberLotElementView();
    viewer->addView(0, view);
    ColorLotElementView* colorView = new ColorLotElementView();
    viewer->addView(1, colorView);
    ui->verticalLayout->addWidget(view);
    ui->verticalLayout->addWidget(colorView);
    _drawingController->setLotViewer(viewer);

    shared_ptr<LotLogger> logger(new LotLogger(ui->logWidget));
    _drawingController->setLotLogger(logger);


    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    connect(ui->showLogCheckBox, SIGNAL(toggled(bool)), SLOT(showLogChecked(bool)));
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

void MainView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}
