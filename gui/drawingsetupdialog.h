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

#ifndef DRAWINGSETUPDIALOG_H
#define DRAWINGSETUPDIALOG_H

#include <QDialog>
#include "drawingsetupcontroller.h"

class LotViewer;

namespace Ui {
class DrawingSetupDialog;
}

class DrawingSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawingSetupDialog(DrawingSetupController* controller, QWidget *parent = 0);
    ~DrawingSetupDialog();
    int exec(bool canTerminateApp);

    std::shared_ptr<DrawingSession> getDrawingSession();
    LotView* getView();

private slots:
    void createClicked();
    void configurationChanged(int index);
    void configureClicked();

private:
    Ui::DrawingSetupDialog* ui;
    DrawingSetupController* _controller;

    void setupConfigurations();
};

#endif // DRAWINGSETUPDIALOG_H
