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
#include "lotview.h"
#include "lotlogger.h"

DrawingController::DrawingController(LotWindow* lotWindow)
    : _lotWindow(lotWindow),
      _lotView(0)
{
}

void DrawingController::draw()
{
    Lot lot = _drawingSession->draw();
    if (_lotView) {
        lot.view(*_lotView);
    }

    if (_lotLogger) {
        _lotLogger->log(lot, _drawingSession);
    }
}

void DrawingController::showLotWindow(bool visible)
{
    _lotWindow->setVisible(visible);
}

void DrawingController::showLotWindowFullscreen(bool fullscreen)
{
    if (fullscreen) {
        _lotWindow->showFullScreen();
    } else {
        _lotWindow->showNormal();
    }
}

void DrawingController::setLotView(LotView* view)
{
    _lotView = view;
    _lotWindow->setView(view);
}

