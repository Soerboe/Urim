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

#include "drawingview.h"
#include "ui_drawingview.h"
#include <QTimer>
#include "drawingsetupdialog.h"
#include "lotlogger.h"
#include "lotviewer.h"
#include "lotelementview.h"

using namespace std;

DrawingView::DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingView),
    _drawingController(controller),
    _setupDialog(setupDialog)
{
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName());
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
    connect(ui->showFullscreenAction, SIGNAL(toggled(bool)), SLOT(showFullscreenClicked(bool)));

    QTimer::singleShot(0, this, SLOT(showDrawingSetup()));
}

DrawingView::~DrawingView()
{
    delete ui;
}

void DrawingView::closeEvent(QCloseEvent* event)
{
    event->accept();
    if (event->isAccepted()) {
        qApp->quit();
    }
}

void DrawingView::showDrawingSetup()
{
    int status = _setupDialog->exec(true);

    if (status == QDialog::Accepted) {
        _drawingController->setDrawingSession(_setupDialog->getDrawingSession());
        shared_ptr<LotViewer> viewer = _setupDialog->getViewer();
        _drawingController->setLotViewer(viewer);
        _drawingController->updateLotView();

        _drawingController->showLotView(true);
        this->show();
    } else {
        qApp->exit(0);
    }

}

void DrawingView::drawClicked()
{
    _drawingController->draw();
}

void DrawingView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}

void DrawingView::showFullscreenClicked(bool checked)
{
    _drawingController->showLotViewFullscreen(checked);
    this->show();
}
