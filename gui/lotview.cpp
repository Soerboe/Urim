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
#include <memory>
#include <QResizeEvent>
#include "loadingwidget.h"

using namespace std;

LotView::LotView(QWidget* parent) :
    QWidget(parent)
{
    _loadingWidget = new LoadingWidget(this);
    _loadingWidget->setVisible(false);
    setMinimumWidth(150);
}

LotView::~LotView()
{

}

void LotView::showLoading(bool visible)
{
    _loadingWidget->setVisible(visible);
    if (visible) {
        _loadingWidget->raise();
    }
}

void LotView::showEvent(QShowEvent*)
{
    calcViewSize();
}

void LotView::resizeEvent(QResizeEvent* event)
{
    calcViewSize();
    _loadingWidget->resize(event->size());
    event->accept();
}
