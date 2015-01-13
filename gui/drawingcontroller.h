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

class LotViewer;

class DrawingController
{
public:
    DrawingController();

    void draw();

    void setDrawingSession(const std::shared_ptr<DrawingSession> drawingSession) {_drawingSession = drawingSession;}
    void setLotViewer(const std::shared_ptr<LotViewer> lotViewer) {_lotViewer = lotViewer;}

private:
    std::shared_ptr<DrawingSession> _drawingSession;
    std::shared_ptr<LotViewer> _lotViewer;
};

#endif // DRAWINGCONTROLLER_H
