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
#include <QSplitter>

ViewContainer::ViewContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewContainer),
    _lotView(0)
{
    ui->setupUi(this);
    _splitter = new QSplitter();
    ui->horizontalLayout->addWidget(_splitter);

    QString splitterStyle("QSplitter::handle { border-left: 2px dotted #C0C0C0; background-color: #F0F0F0;}");
    _splitter->setStyleSheet(splitterStyle);
}

ViewContainer::~ViewContainer()
{
    delete ui;
}

void ViewContainer::setLotView(LotView *view)
{
    if (_lotView) {
        delete _lotView;
    }

    _splitter->insertWidget(0, view);
    _splitter->setStretchFactor(0, 75);
    _lotView = view;
}

void ViewContainer::addHistoryWidget(QWidget *widget)
{
    _splitter->insertWidget(1, widget);
    _splitter->setStretchFactor(1, 25);
}

