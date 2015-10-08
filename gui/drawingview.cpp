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
#include "urimthummim.h"
#include <QScreen>
#include "aboutbox.h"
#include <QDesktopWidget>

using namespace std;

DrawingView::DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingView),
    _drawingController(controller),
    _setupDialog(setupDialog),
    _lotView(0)
{
    ui->setupUi(this);
    setupLogger();

    QString style("#lotContainer {background-color: #ffffff; border: 1px solid ");
    style.append(IDENTITY_COLOR).append(";}");
    ui->lotContainer->setStyleSheet(style);

    setupShowLotViewMenu();

    ui->drawingNameView->hide();
    ui->drawButton->hide();

    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    connect(ui->drawAction, SIGNAL(triggered()), SLOT(drawClicked()));
    connect(ui->createNewDrawingAction, SIGNAL(triggered()), SLOT(createNewDrawingClicked()));
    connect(ui->quitAction, SIGNAL(triggered()), SLOT(close()));
    connect(ui->aboutAction, SIGNAL(triggered()), SLOT(showAbout()));
    connect(ui->aboutQtAction, SIGNAL(triggered()), SLOT(showAboutQt()));

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    QTimer::singleShot(0, this, SLOT(showDrawingSetup()));
}

DrawingView::~DrawingView()
{
    delete ui;
}

void DrawingView::setLotView(LotView* lotView)
{
    QLayoutItem* oldView = ui->lotContainer->layout()->takeAt(0);
    if (oldView) {
        delete oldView->widget();
        delete oldView;
    }

    ui->lotContainer->layout()->addWidget(lotView);
    _lotView = lotView;
}

LotView* DrawingView::takeLotView()
{
    QLayoutItem* oldView = ui->lotContainer->layout()->takeAt(0);
    LotView* view = _lotView;
    _lotView = 0;
    return view;
}

bool DrawingView::hasLotView()
{
    return _lotView != 0;
}

void DrawingView::enableDrawing(bool enabled)
{
    ui->drawAction->setEnabled(enabled);
    ui->drawButton->setEnabled(enabled);
}

void DrawingView::setDrawingName(QString drawingName)
{
    ui->drawingNameView->setText(drawingName);
    ui->drawingNameView->setVisible(!drawingName.isEmpty());
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

    connect(ui->showLogAction, SIGNAL(triggered(bool)), SLOT(showLogChecked(bool)));
}

void DrawingView::setupShowLotViewMenu()
{
    QActionGroup* showLotViewActions = new QActionGroup(this);
    QAction* thisWindowAction = new QAction(tr("In this window"), this);
    thisWindowAction->setCheckable(true);
    thisWindowAction->setData(-1);
    showLotViewActions->addAction(thisWindowAction);
    ui->showLotViewMenu->addAction(thisWindowAction);

    QList<QScreen*> screens = qApp->screens();
    if (screens.size() > 0) {
        for (int screenIndex = 0; screenIndex < screens.size(); ++screenIndex) {
            QAction* monitorAction = new QAction(tr("Fullscreen on screen %1").arg(screenIndex + 1), this);
            monitorAction->setCheckable(true);
            monitorAction->setData(screenIndex);
            showLotViewActions->addAction(monitorAction);
            ui->showLotViewMenu->addAction(monitorAction);
        }
    }

    connect(showLotViewActions, SIGNAL(triggered(QAction*)), SLOT(moveLotView(QAction*)));

    // TODO get this from QSettings
    thisWindowAction->setChecked(true);
}

void DrawingView::clear()
{
    ui->logWidget->clear();
}

void DrawingView::moveLotView(QAction* action)
{
    QScreen* screen = 0;
    int screenIndex = action->data().toInt();
    if (screenIndex >= 0) {
        screen = qApp->screens().at(screenIndex);
    }

    bool inThisWindow = !screen;

    _drawingController->moveLotView(screen);
    _drawingController->showLotWindow(!inThisWindow);
    ui->lotContainer->setVisible(inThisWindow);
    ui->showLogAction->setChecked(!inThisWindow);
    ui->logWidget->setVisible(!inThisWindow);
    ui->drawButton->setVisible(!inThisWindow);
    if (_drawingController->drawingSession()->lotsCount() > 0) {
        _drawingController->showLot(true);
    }
}

void DrawingView::showDrawingSetup()
{
    int status = _setupDialog->exec();

    if (status == QDialog::Accepted) {
        _drawingController->setDrawingSession(_setupDialog->getDrawingSession());
        LotView* lotView = _setupDialog->getView();
        QString drawingName = _setupDialog->getDrawingName();
        _drawingController->setLotView(lotView);
        _drawingController->setDrawingName(drawingName);
        this->show();
    } else {
        qApp->exit(0);
    }

}

void DrawingView::drawClicked()
{
    try {
        enableDrawing(false);
        _drawingController->draw();
        enableDrawing(true);
    } catch (NoMoreUniqueResultsException& e) {
        QMessageBox::warning(this, tr("No more unique results"), tr("All unique lots have been drawn."));
    }
}

void DrawingView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}

void DrawingView::createNewDrawingClicked()
{
    QMessageBox box(QMessageBox::Question,
                    tr("Quit session"),
                    tr("Quit current drawing session and create a new drawing?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
    box.setButtonText(QMessageBox::Yes, tr("Yes"));
    box.setButtonText(QMessageBox::No, tr("No"));
    if (box.exec() == QMessageBox::No) {
        return;
    }

    clear();
    // TODO clear state of view
    this->hide();
    _drawingController->showLotWindow(false);
    showDrawingSetup();
}

void DrawingView::showAbout()
{
    AboutBox about(this);
    about.exec();
}

void DrawingView::showAboutQt()
{
    QMessageBox::aboutQt(this);
}
