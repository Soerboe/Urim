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

#ifndef DRAWINGVIEW_H
#define DRAWINGVIEW_H

#include <QMainWindow>
#include "drawingcontroller.h"
#include "drawingsetupdialog.h"
#include <QCloseEvent>

namespace Ui {
class DrawingView;
}

class DrawingView : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget* parent = 0);
    ~DrawingView();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::DrawingView *ui;
    DrawingController* _drawingController;
    DrawingSetupDialog* _setupDialog;

    void setupLogger();
    void clear();

private slots:
    void showDrawingSetup();
    void drawClicked();
    void showLogChecked(bool checked);
    void showFullscreenClicked(bool checked);
    void createNewDrawingClicked();
};

#endif // DRAWINGVIEW_H
