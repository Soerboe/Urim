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

#ifndef DRAWINGCONTROLLER_H
#define DRAWINGCONTROLLER_H

#include "drawingsession.h"
#include "lotwindow.h"

class LotView;
class LotLogger;

class DrawingController
{
public:
    DrawingController(LotWindow* lotWindow);

    void draw();
    void showLotWindow(bool visible);
    void showLotWindowFullscreen(bool fullscreen);

    void setDrawingSession(const std::shared_ptr<DrawingSession> drawingSession) {_drawingSession = drawingSession;}
    void setLotLogger(const std::shared_ptr<LotLogger> lotLogger) {_lotLogger = lotLogger;}

    std::shared_ptr<DrawingSession> drawingSession() const {return _drawingSession;}
    void setLotView(LotView* view);

private:
    LotWindow* _lotWindow;
    LotView* _lotView;
    std::shared_ptr<DrawingSession> _drawingSession;
    std::shared_ptr<LotLogger> _lotLogger;
};

#endif // DRAWINGCONTROLLER_H
