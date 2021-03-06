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

#include "lotwindow.h"
#include "ui_lotwindow.h"
#include "viewcontainer.h"

LotWindow::LotWindow(QWidget *drawingView) :
    QWidget(0),
    ui(new Ui::LotWindow),
    _viewContainer(0),
    _drawingView(drawingView)
{
    ui->setupUi(this);
    QString style("#LotWindow {background-color: #ffffff;}");
    setStyleSheet(style);
    setAttribute(Qt::WA_ShowWithoutActivating);

    setFocusPolicy(Qt::StrongFocus);
}

LotWindow::~LotWindow()
{
    delete ui;
}

void LotWindow::setViewContainer(ViewContainer *viewContainer)
{
    QLayoutItem* oldView = ui->layout->takeAt(0);
    if (oldView) {
        delete oldView;
    }

    ui->layout->addWidget(viewContainer);
    _viewContainer = viewContainer;
}

ViewContainer *LotWindow::takeViewContainer()
{
    QLayoutItem* oldView = ui->layout->takeAt(0);
    if (oldView) {
        delete oldView;
    }

    ViewContainer* viewContainer = _viewContainer;
    _viewContainer = 0;
    return viewContainer;
}

bool LotWindow::hasViewContainer()
{
    return _viewContainer != 0;
}

void LotWindow::focusInEvent(QFocusEvent *)
{
    _drawingView->activateWindow();
}
