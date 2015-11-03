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
#include "lotview.h"

LotWindow::LotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LotWindow),
    _lotView(0)
{
    ui->setupUi(this);
    QString style("#LotWindow {background-color: #ffffff;}");
    setStyleSheet(style);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFocusPolicy(Qt::NoFocus);

    ui->drawingNameView->hide();
}

LotWindow::~LotWindow()
{
    delete ui;
}

void LotWindow::setView(LotView* view)
{
    QLayoutItem* oldView = ui->layout->takeAt(0);
    if (oldView) {
        delete oldView->widget();
        delete oldView;
    }

    view->setMinimumSize(200, 100);
    ui->layout->addWidget(view);
    _lotView = view;

    ui->drawingNameView->setText(_drawingName);
    ui->drawingNameView->setVisible(!_drawingName.isEmpty());
}

LotView* LotWindow::takeView()
{
    QLayoutItem* oldView = ui->layout->takeAt(0);
    if (oldView) {
        delete oldView;
    }

    LotView* view = _lotView;
    _lotView = 0;
    return view;
}

bool LotWindow::hasView()
{
    return _lotView != 0;
}

