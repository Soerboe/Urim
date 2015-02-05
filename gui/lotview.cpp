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

#include "lotview.h"
#include "ui_lotview.h"
#include "lotelementview.h"
#include "lotviewer.h"
#include <memory>
#include "drawingcontroller.h"
#include <QResizeEvent>
#include <QTimer>
#include "randomgenerator.h"

using namespace std;

LotView::LotView(DrawingController* controller, QWidget *parent) :
    QWidget(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::LotView),
    _controller(controller)
{
    ui->setupUi(this);
}

LotView::~LotView()
{
    delete ui;
}

void LotView::initializeViews()
{
    shared_ptr<LotViewer> viewer = _controller->lotViewer();
    int count = viewer->countViews();

    if (count == 1) {
        LotElementView* view = viewer->at(0);
        ui->gridLayout->addWidget(view, 0, 0);
    } else if (count == 2) {
        ui->gridLayout->addWidget(viewer->at(0), 0, 0);
        ui->gridLayout->addWidget(viewer->at(1), 0, 1);
    }
}

void LotView::showEvent(QShowEvent*)
{
    calcFontSize();
}

void LotView::resizeEvent(QResizeEvent*)
{
    calcFontSize();
}

void LotView::calcFontSize()
{
    int maxFontSize = MAX_FONT_SIZE;

    for (int i = 0; i < _controller->lotViewer()->countViews(); ++i) {
        int localMax = _controller->lotViewer()->at(i)->calcMaxFontSize();
        if (localMax < maxFontSize) {
            maxFontSize = localMax;
        }
    }

    if (maxFontSize <= 0) {
        return;
    }

    QFont f = font();
    f.setPointSize(maxFontSize);
    setFont(f);

    for (int i = 0; i < _controller->lotViewer()->countViews(); ++i) {
        //TODO trenger en test paa at viewers og generators er likt antall
        QString s(_controller->drawingSession()->generatorsAt(i)->name().c_str());
        _controller->lotViewer()->at(i)->calcLocalFontSize(s);
    }
}

void LotView::initFont()
{
    calcFontSize();
}
