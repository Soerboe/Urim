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
#include "logger.h"
#include "loggerview.h"
#include "nomoreuniqueresultsexception.h"
#include <QMessageBox>
#include <QScreen>
#include "aboutbox.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include "viewcontainer.h"
#include "settingsdialog.h"
#include <QDesktopServices>
#include "settingshandler.h"
#include <QCheckBox>
#include <QLabel>

using namespace std;

DrawingView::DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawingView),
    _drawingController(controller),
    _setupDialog(setupDialog),
    _viewContainer(0),
    _presentationViewActions(0),
    _updateView(this)
{
    ui->setupUi(this);

    setupLogger();
    setupPresentationViewMenu();
    setupStatusbar();

    QString style("#container {background-color: #ffffff;}");
    ui->container->setStyleSheet(style);

    ui->drawButton->hide();

    QWidget* toolbarSpacer = new QWidget(this);
    toolbarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbarSpacer->setVisible(true);
    ui->mainToolBar->insertWidget(ui->finishDrawingAction, toolbarSpacer);

    connect(ui->drawButton, SIGNAL(clicked()), SLOT(drawClicked()));
    connect(ui->drawAction, SIGNAL(triggered()), SLOT(drawClicked()));
    connect(ui->startNewSessionAction, SIGNAL(triggered()), SLOT(startNewDrawingSession()));
    connect(ui->createNewDrawingAction, SIGNAL(triggered()), SLOT(createNewDrawingClicked()));
    connect(ui->saveLogAction, SIGNAL(triggered()), SLOT(saveLogToFile()));
    connect(ui->tooglePresentationViewAction, SIGNAL(triggered(bool)), SLOT(tooglePresentationView(bool)));
    connect(ui->quitAction, SIGNAL(triggered()), SLOT(close()));
    connect(ui->aboutAction, SIGNAL(triggered()), SLOT(showAbout()));
    connect(ui->aboutQtAction, SIGNAL(triggered()), SLOT(showAboutQt()));
    connect(ui->presentationViewMenu, SIGNAL(aboutToShow()), SLOT(setupPresentationViewMenu()));
    connect(qApp, SIGNAL(screenAdded(QScreen*)), SLOT(screensChanged()));
    connect(qApp, SIGNAL(screenRemoved(QScreen*)), SLOT(screensChanged()));
    connect(ui->showLotsDrawnAction, SIGNAL(toggled(bool)), SLOT(showLotsDrawnClicked(bool)));
    connect(ui->settingsAction, SIGNAL(triggered()), SLOT(showSettingsDialog()));
    connect(ui->checkForUpdateAction, SIGNAL(triggered()), SLOT(checkForUpdate()));
    connect(ui->goToWebsiteAction, SIGNAL(triggered()), SLOT(goToWebsite()));
    connect(ui->finishDrawingAction, SIGNAL(triggered()), SLOT(finishDrawingClicked()));

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    QTimer::singleShot(0, this, SLOT(showDrawingSetup()));
}

DrawingView::~DrawingView()
{
    delete ui;
}

void DrawingView::setupStatusbar()
{
    _zoomSlider = new QSlider(Qt::Horizontal);
    _zoomSlider->setRange(10, 100);
    _zoomSlider->setFixedWidth(100);
    _zoomSlider->setValue(90);

    auto setZoomText = [&](int percent) -> QString {
        return tr("Zoom").append(QString::number(percent).rightJustified(4, ' ')).append("% ");
    };

    _zoomView = new QLabel();
    _zoomView->setText(setZoomText(_zoomSlider->value()));

    auto zoom = [&](int position) {
        _drawingController->viewContainer()->zoomLotView(position);
        _zoomView->setText(setZoomText(position));
    };

    connect(_zoomSlider, &QSlider::sliderMoved, zoom);
    connect(_zoomSlider, &QSlider::valueChanged, zoom);

    _sessionIdView = new QLabel;

    statusBar()->addPermanentWidget(_zoomView);
    statusBar()->addPermanentWidget(_zoomSlider);
    statusBar()->addPermanentWidget(_sessionIdView);
}

void DrawingView::setViewContainer(ViewContainer *viewContainer)
{
    QLayoutItem* oldView = ui->container->layout()->takeAt(0);
    if (oldView) {
        delete oldView;
    }

    ui->container->layout()->addWidget(viewContainer);
    _viewContainer = viewContainer;
}

ViewContainer *DrawingView::takeViewContainer()
{
    QLayoutItem* oldView = ui->container->layout()->takeAt(0);
    if (oldView) {
        delete oldView;
    }

    ViewContainer* viewContainer = _viewContainer;
    _viewContainer = 0;
    return viewContainer;
}

bool DrawingView::hasViewContainer()
{
    return _viewContainer != 0;
}

void DrawingView::enableDrawing(bool enabled)
{
    ui->drawAction->setEnabled(enabled);
    ui->drawButton->setEnabled(enabled);
}

void DrawingView::closeEvent(QCloseEvent* event)
{
    event->accept();
    if (event->isAccepted()) {
        qApp->quit();
    }
}

void DrawingView::updateSessionIdView(const std::shared_ptr<DrawingSession> session)
{
    _sessionIdView->setText(tr("Session %1").arg(session->id()));
}

void DrawingView::setupLogger()
{
    ui->logWidget->setVisible(false);

    shared_ptr<Logger> logger(new Logger());
    _drawingController->setLogger(logger);
    _loggerView = shared_ptr<LoggerView>(new LoggerView(ui->logWidget, logger));

    connect(ui->showLogAction, SIGNAL(triggered(bool)), SLOT(showLogChecked(bool)));
}

void DrawingView::setupPresentationViewMenu()
{
    if (_presentationViewActions) {
        delete _presentationViewActions;
        ui->presentationViewMenu->clear();
    }

    _presentationViewActions = new QActionGroup(this);

    QAction* thisWindowAction = new QAction(tr("In this window"), ui->presentationViewMenu);
    thisWindowAction->setCheckable(true);
    thisWindowAction->setData(-1);
    _presentationViewActions->addAction(thisWindowAction);
    ui->presentationViewMenu->addAction(thisWindowAction);

    QList<QScreen*> screens = qApp->screens();
    if (screens.size() > 1) {
        for (int screenIndex = 0; screenIndex < screens.size(); ++screenIndex) {
            QAction* monitorAction = new QAction(tr("Fullscreen on screen %1").arg(screenIndex + 1), ui->presentationViewMenu);
            monitorAction->setCheckable(true);
            monitorAction->setData(screenIndex);
            _presentationViewActions->addAction(monitorAction);
            ui->presentationViewMenu->addAction(monitorAction);
        }
    }

    connect(_presentationViewActions, SIGNAL(triggered(QAction*)), SLOT(moveViewContainer(QAction*)));

    _presentationViewActions->actions().at(_drawingController->currentLotWindowIndex() + 1)->setChecked(true);
}

void DrawingView::clear()
{
    ui->logWidget->clear();
    _drawingController->clearHistory();
    enableDrawing(true);
    ui->presentationViewMenu->actions()[0]->setChecked(true);

    setupComponentVisibility(false);
}

void DrawingView::setupComponentVisibility(bool showViewContainerInWindow)
{
    ui->container->setVisible(!showViewContainerInWindow);
    ui->showLogAction->setChecked(showViewContainerInWindow);
    ui->logWidget->setVisible(showViewContainerInWindow);
    ui->drawButton->setVisible(showViewContainerInWindow);
    ui->tooglePresentationViewAction->setChecked(showViewContainerInWindow);
}

/*
 * A screenIndex of -1 refers to the drawing window
 * A screenIndex > 0 refers to screen index in qApp->screens()
 */
void DrawingView::moveViewContainer(int screenIndex)
{
    if (screenIndex < -1) {
        return;
    }

    QScreen* screen = 0;
    if (screenIndex >= 0) {
        screen = qApp->screens().at(screenIndex);
    }

    _drawingController->moveViewContainer(screenIndex, screen);
    _drawingController->showLotWindow(screen != 0);
    setupComponentVisibility(screen != 0);
    bool lotsDrawn = _drawingController->drawingSession()->lotsCount() > 0;
    _drawingController->showLot(lotsDrawn);
    _presentationViewActions->actions().at(screenIndex + 1)->setChecked(true);
}

void DrawingView::moveViewContainer(QAction* action)
{
    int screenIndex = action->data().toInt();
    moveViewContainer(screenIndex);
}

void DrawingView::showDrawingSetup()
{
    _setupDialog->show();

    connect(_setupDialog, &DrawingSetupDialog::finished, [&](int result) {
        if (result == QDialog::Accepted) {
            _drawingController->initViewContainer(_setupDialog->getView());
            _drawingController->logger()->clear();
            startNewDrawingSession(true);
            this->show();
        } else {
            qApp->exit(0);
        }
    });
}

void DrawingView::saveLogToFile()
{
    QString suffices;
    QString selectedSuffix;
    suffices.append(tr("Excel file (*.xlsx)")).append(";;");
    suffices.append(tr("Log files (*.log)"));
    QString filename = QFileDialog::getSaveFileName(this, tr("Save log to file"), QDir::homePath(), suffices, &selectedSuffix);

    if (filename.isNull()) {
        return;
    }

    QFileInfo fileInfo(filename);
    QString suffix;
    if (selectedSuffix.contains(LOG_SUFFIX)) {
        suffix = LOG_SUFFIX;
    } else {
        suffix = EXCEL_SUFFIX; // default suffix
    }

    if (fileInfo.suffix().isEmpty() ||
            (fileInfo.suffix() != LOG_SUFFIX && fileInfo.suffix() != EXCEL_SUFFIX)) {
        fileInfo.setFile(filename.append(suffix));
    }

    bool saved = _drawingController->logger()->saveToFile(fileInfo);

    if (!saved) {
        QMessageBox::warning(this, tr("Error"), tr("Could not save log to file"));
    }
}

void DrawingView::drawClicked()
{
    try {
        enableDrawing(false);
        statusBar()->showMessage(tr("Drawing a lot..."));
        _drawingController->draw();
        statusBar()->clearMessage();
        enableDrawing(true);
    } catch (NoMoreUniqueResultsException&) {
        QString s = tr("No more unique results");
        QMessageBox::warning(this, s, tr("All unique lots have been drawn."));
        statusBar()->showMessage(s);
    }
}

void DrawingView::startNewDrawingSession(bool newDrawing)
{
    shared_ptr<DrawingSession> session = _setupDialog->getDrawingSession();
    if (!newDrawing && _drawingController->drawingSession()) {
        session->setId(_drawingController->drawingSession()->id() + 1);
    }
    _drawingController->setDrawingSession(session);
    updateSessionIdView(session);
    _drawingController->logger()->logMessage(tr("Session %1 started").arg(session->id()));
    _drawingController->showLot(false);
    _drawingController->clearHistory();
    enableDrawing(true);
}

void DrawingView::showLogChecked(bool checked)
{
    ui->logWidget->setVisible(checked);
}

void DrawingView::tooglePresentationView(bool checked)
{
    int numScreens = qApp->screens().size();
    int screenIndex = checked ? 1 : -1;

    if (numScreens == 1) {
        QMessageBox box(QMessageBox::Information,
                    tr("Setup presentation view"),
                    tr("To enable presentiation view you need to connect to an external display or projector.<br><br> \
                       <h3>Windows</h3>Display settings must be set to <strong>Extended</strong>. Use shortcut <strong>Windows Key + P</strong>.<br><br> \
                       <h3>macOS / OS X</h3>Mirror displays must be turned off. Go to System Preferences > Displays > Arrangement. Deselect Mirror Displays checkbox."),
                    QMessageBox::Ok,
                    this);
        box.exec();
        ui->tooglePresentationViewAction->setChecked(false);
    } else {
        moveViewContainer(screenIndex);
    }

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

void DrawingView::screensChanged()
{
    moveViewContainer(-1);
}

void DrawingView::showLotsDrawnClicked(bool checked)
{
    _drawingController->showHistoryWidget(checked);
}

void DrawingView::showSettingsDialog()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

void DrawingView::checkForUpdate()
{
    _updateView.checkForUpdate();
}

void DrawingView::goToWebsite()
{
    QDesktopServices::openUrl(QUrl(QString("https://lioddensorbo.com/urim/").append(SettingsHandler::language())));
}

void DrawingView::finishDrawingClicked()
{
    QMessageBox finishBox(
                QMessageBox::Question,
                tr("Finish lottery drawing"),
                tr("Are you sure you want to finish current lottery drawing?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
    QCheckBox* saveLogBox = new QCheckBox(tr("Save log"));
    saveLogBox->setChecked(true);
    finishBox.setCheckBox(saveLogBox);

    finishBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    finishBox.setButtonText(QMessageBox::No, tr("No"));
    if (finishBox.exec() == QMessageBox::No) {
        return;
    }

    if (saveLogBox->isChecked()) {
        saveLogToFile();
    }

    QMessageBox exitBox(
                QMessageBox::Question,
                tr("Create new lottery drawing"),
                tr("Would you like to create a new lottery drawing?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
    exitBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    exitBox.setButtonText(QMessageBox::No, tr("No, exit application"));

    if (exitBox.exec() == QMessageBox::Yes) {
        this->hide();
        showDrawingSetup();
    } else {
        qApp->exit(0);
    }
}
