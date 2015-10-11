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
#include <QObject>
#include <vector>

class LotView;
class LotLogger;
class DrawingView;

class DrawingController : public QObject
{
    Q_OBJECT

public:
    DrawingController();
    ~DrawingController();

    void draw();
    void showLotWindow(bool visible);
    void showLot(bool visible);
    void setLotView(LotView* view, const QScreen* screen = 0);
    void moveLotView(int screenIndex, const QScreen* screen = 0);
    void setDrawingName(QString drawingName);

    std::shared_ptr<DrawingSession> drawingSession() const {return _drawingSession;}

    void setDrawingView(DrawingView* view) {_drawingView = view;}
    void setDrawingSession(const std::shared_ptr<DrawingSession> drawingSession) {_drawingSession = drawingSession;}
    void setLotLogger(const std::shared_ptr<LotLogger> lotLogger) {_lotLogger = lotLogger;}

private slots:
    void doDraw();

private:
    DrawingView* _drawingView;
    std::vector<LotWindow*> _lotWindows;
    int _currLotWindowIndex;
    LotView* _lotView;
    std::shared_ptr<DrawingSession> _drawingSession;
    std::shared_ptr<LotLogger> _lotLogger;
    void delay(int n);
    LotWindow* currLotWindow();
};

#endif // DRAWINGCONTROLLER_H
