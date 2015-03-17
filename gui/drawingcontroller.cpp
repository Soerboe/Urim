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
#include <QTimer>
#include <QScreen>

DrawingController::DrawingController(LotWindow* lotWindow)
    : _lotWindow(lotWindow),
      _lotView(0)
{
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

    _lotView->showLot(true);
    _lotView->showLoading(false);
    _drawingView->enableDrawing(true);
}

void DrawingController::draw()
{
    _lotView->showLoading(true);
    _lotView->showLot(false);

    QTimer::singleShot(1500, this, SLOT(doDraw()));
}

void DrawingController::showLotWindow(bool visible)
{
    if (visible) {
        _lotWindow->showFullScreen();
    } else {
        _lotWindow->setVisible(false);
    }
}

void DrawingController::showLot(bool visible)
{
    _lotView->showLot(visible);
}

void DrawingController::moveLotView(const QScreen* screen)
{
    LotView* view = 0;

    if (_lotWindow->hasView()) {
        view = _lotWindow->takeView();
    } else if (_drawingView->hasLotView()) {
        view = _drawingView->takeLotView();
    }

    if (screen) {
        _lotWindow->move(screen->geometry().x(), screen->geometry().y());
    }

    setLotView(view, screen);
}

void DrawingController::setLotView(LotView* view, const QScreen* screen)
{
    if (!view) {
        return;
    }

    _lotView = view;

    if (screen) {
        _lotWindow->setView(view);
    } else {
        _drawingView->setLotView(view);
    }
}

