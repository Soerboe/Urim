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
#include "lotview.h"
#include "nomoreuniqueresultsexception.h"
#include <QMessageBox>

using namespace std;

DrawingView::DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingView),
    _drawingController(controller),
    _setupDialog(setupDialog)
{
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName());
    setupLogger();

    ui->drawingNameView->hide();

    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    connect(ui->showFullscreenAction, SIGNAL(toggled(bool)), SLOT(showFullscreenClicked(bool)));
    connect(ui->createNewDrawingAction, SIGNAL(triggered()), SLOT(createNewDrawingClicked()));
    connect(ui->quitAction, SIGNAL(triggered()), SLOT(close()));

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

void DrawingView::setupLogger()
{
    ui->logWidget->setVisible(false);
    QStringList headerLabels;
    headerLabels << tr("No.") << tr("Time") << tr("Lot");
    ui->logWidget->setColumnCount(headerLabels.size());
    ui->logWidget->setHeaderLabels(headerLabels);
    ui->logWidget->resizeColumnToContents(0);

    shared_ptr<LotLogger> logger(new LotLogger(ui->logWidget));
    _drawingController->setLotLogger(logger);

    connect(ui->showLogCheckBox, SIGNAL(toggled(bool)), SLOT(showLogChecked(bool)));
}

void DrawingView::clear()
{
    ui->logWidget->clear();
}

void DrawingView::showDrawingSetup()
{
    int status = _setupDialog->exec();

    if (status == QDialog::Accepted) {
        _drawingController->setDrawingSession(_setupDialog->getDrawingSession());
        LotView* lotView = _setupDialog->getView();
        _drawingController->setLotView(lotView);
        _drawingController->showLotWindow(true);

        QString drawingName = _setupDialog->getDrawingName();
        ui->drawingNameView->setText(drawingName);
        ui->drawingNameView->setVisible(!drawingName.isEmpty());

        this->show();
    } else {
        qApp->exit(0);
    }

}

void DrawingView::drawClicked()
{
    try {
        _drawingController->draw();
    } catch (NoMoreUniqueResultsException& e) {
        QMessageBox::warning(this, tr("No more unique results"), tr("All unique lots have been drawn."));
        ui->drawButton->setEnabled(false);
    }
}

void DrawingView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}

void DrawingView::showFullscreenClicked(bool checked)
{
    _drawingController->showLotWindowFullscreen(checked);
    this->show();
}

void DrawingView::createNewDrawingClicked()
{
    // ask for confirmation
    clear();
    // clear state of view
    this->hide();
    _drawingController->showLotWindow(false);
    showDrawingSetup();
}
