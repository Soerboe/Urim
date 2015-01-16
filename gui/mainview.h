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

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "drawingcontroller.h"

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(DrawingController* controller, QWidget *parent = 0);
    ~MainView();

private:
    Ui::MainView *ui;

    DrawingController* _drawingController;

private slots:
    void showDrawingSetup();
    void drawClicked();
    void showLogChecked(bool checked);
};

#endif // MAINVIEW_H
