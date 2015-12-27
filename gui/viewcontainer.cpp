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

class LotViewContainer : public QFrame
{
    Q_OBJECT

public:
    LotViewContainer()
        : QFrame(0)
    {
        setLayout(new QVBoxLayout);
        setFrameStyle(QFrame::NoFrame);
    }

    void setLotView(LotView* view)
    {
        if (layout()->itemAt(0)) {
            QLayoutItem* item = layout()->takeAt(0);
            delete item->widget();
            delete item;
        }

        layout()->addWidget(view);
    }
};

#include "viewcontainer.moc"

ViewContainer::ViewContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewContainer),
    _lotView(0),
    _lotViewZoom(90)
{
    ui->setupUi(this);
    _splitter = new QSplitter();
    _splitter->setChildrenCollapsible(false);
    ui->horizontalLayout->addWidget(_splitter);

    QString splitterStyle("QSplitter::handle { border-left: 2px dotted #C0C0C0; background-color: #F0F0F0;}");
    _splitter->setStyleSheet(splitterStyle);

    _lotViewContainer = new LotViewContainer();
    _splitter->insertWidget(0, _lotViewContainer);
    _splitter->setStretchFactor(0, 75);

    connect(_splitter, &QSplitter::splitterMoved, [&](int, int) {
        this->updateLotViewSize();
    });
}

ViewContainer::~ViewContainer()
{
    delete ui;
}

void ViewContainer::setLotView(LotView *view)
{
    _lotViewContainer->setLotView(view);
    _lotView = view;
    updateLotViewSize();
}

void ViewContainer::addHistoryWidget(QWidget *widget)
{
    _splitter->insertWidget(1, widget);
    _splitter->setStretchFactor(1, 25);
}

void ViewContainer::zoomLotView(int percent)
{
    if (percent < 10 || percent > 100) {
        return;
    }

    _lotViewZoom = percent;
    updateLotViewSize();
}

void ViewContainer::resizeEvent(QResizeEvent *)
{
    updateLotViewSize();
}

void ViewContainer::updateLotViewSize()
{
    int w = _lotViewContainer->width(), h = _lotViewContainer->height();
    double internalZoomFactor = (20 + _lotViewZoom / 1.25) / 100.0;

    // tries to set height and adjust width
    // else set width and adjust height
    int viewHeight = w / LOTVIEW_ASPECT_RATIO;
    int viewWidth;
    if (viewHeight <= h) {
        viewWidth = viewHeight * LOTVIEW_ASPECT_RATIO;
    } else {
        viewWidth = h * LOTVIEW_ASPECT_RATIO;
        viewHeight = viewWidth / LOTVIEW_ASPECT_RATIO;
    }

    viewHeight *= internalZoomFactor;
    viewWidth *= internalZoomFactor;

    if (_lotView && viewWidth < _lotView->minimumWidth()) {
        viewWidth = _lotView->minimumWidth();
        viewHeight = viewWidth / LOTVIEW_ASPECT_RATIO;
    }

    int mh = (h - viewHeight) / 2;
    int mw = (w - viewWidth) / 2;
    _lotViewContainer->layout()->setContentsMargins(mw, mh, mw, mh);
}
