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

#include "drawingcontroller.h"
#include "drawingview.h"
#include "lotview.h"
#include "lotlogger.h"
#include "nomoreuniqueresultsexception.h"
#include <QTimer>
#include <QScreen>
#include <QTime>
#include <QCoreApplication>

#define MAX_SCREENS 8

DrawingController::DrawingController()
    : _lotWindows(MAX_SCREENS),
      _currLotWindowIndex(-1),
      _lotView(0)
{
    for (int i = 0; i < MAX_SCREENS; ++i) {
        _lotWindows[i] = 0;
    }
}

DrawingController::~DrawingController()
{
    for (LotWindow* lw : _lotWindows) {
        delete lw;
    }
}

void DrawingController::doDraw()
{
    Lot lot = _drawingSession->draw();

    if (_lotView) {
        lot.view(*_lotView);
    }

    if (_lotLogger) {
        _lotLogger->log(lot, _drawingSession);
    }

}

void DrawingController::delay(int n = 1000)
{
    QTime endTime = QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < endTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

LotWindow *DrawingController::currLotWindow()
{
    return _currLotWindowIndex < 0 || _currLotWindowIndex >= MAX_SCREENS ? 0 : _lotWindows[_currLotWindowIndex];
}

void DrawingController::draw()
{
    _lotView->showLoading(true);
    _lotView->showLot(false);

    delay(1500);
    try {
        doDraw();
    } catch (NoMoreUniqueResultsException& e) {
        _lotView->showLoading(false);
        throw e;
    }

    _lotView->showLot(true);
    _lotView->showLoading(false);
}

void DrawingController::showLotWindow(bool visible)
{
    if (!currLotWindow()) {
        return;
    }

    if (visible) {
        currLotWindow()->showFullScreen();
    } else {
        currLotWindow()->setVisible(false);
    }
}

void DrawingController::showLot(bool visible)
{
    _lotView->showLot(visible);
}

void DrawingController::moveLotView(int screenIndex, const QScreen* screen)
{
    if (screenIndex >= MAX_SCREENS) {
        return;
    }

    LotView* view = 0;
    LotWindow* currentLotWindow = currLotWindow();

    if (currentLotWindow && currentLotWindow->hasView()) {
        view = currentLotWindow->takeView();
        currentLotWindow->setVisible(false);
    } else if (_drawingView->hasLotView()) {
        view = _drawingView->takeLotView();
    }

    if (!view) {
        return;
    }

    if (screenIndex >= 0 && screen) {
        if (!_lotWindows[screenIndex]) {
            _lotWindows[screenIndex] = new LotWindow();
        }

        _currLotWindowIndex = screenIndex;
        _lotWindows[screenIndex]->move(screen->geometry().x(), screen->geometry().y());
    }

    setLotView(view, screen);
}

void DrawingController::setDrawingName(QString drawingName)
{
    if (currLotWindow()) {
        currLotWindow()->setDrawingName(drawingName);
    }
    _drawingView->setDrawingName(drawingName);
}

void DrawingController::setLotView(LotView* view, const QScreen* screen)
{
    if (!view) {
        return;
    }

    _lotView = view;

    if (screen) {
        if (currLotWindow()) {
            currLotWindow()->setView(view);
        }
    } else {
        _drawingView->setLotView(view);
        _currLotWindowIndex = -1;
    }
}

