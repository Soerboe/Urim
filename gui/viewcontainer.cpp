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

#include "viewcontainer.h"
#include "ui_viewcontainer.h"
#include <QLayoutItem>
#include "lotview.h"

ViewContainer::ViewContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewContainer)
{
    ui->setupUi(this);
}

ViewContainer::~ViewContainer()
{
    delete ui;
}

void ViewContainer::setLotView(LotView *view)
{
    clear();
    ui->lotViewLayout->insertWidget(1,view);
    _lotView = view;
}

void ViewContainer::addHistoryWidget(QWidget *widget)
{
    ui->horizontalLayout->insertWidget(1, widget, 25);
    ui->horizontalLayout->setStretch(0, 75);
}

void ViewContainer::clear()
{
    QLayoutItem* oldView = ui->lotViewLayout->takeAt(0);
    if (oldView) {
        delete oldView->widget();
        delete oldView;
    }
}
