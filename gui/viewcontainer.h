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

#ifndef VIEWCONTAINER_H
#define VIEWCONTAINER_H

#include <QWidget>

class QSplitter;
class LotView;
class LotViewContainer;

namespace Ui {
class ViewContainer;
}

class ViewContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ViewContainer(QWidget *parent = 0);
    ~ViewContainer();

    void setLotView(LotView* view);
    void zoomLotView(int percent);
    void addHistoryWidget(QWidget* widget);

private:
    Ui::ViewContainer *ui;
    LotView* _lotView;
    LotViewContainer* _lotViewContainer;
    QSplitter* _splitter;
    int _lotViewZoom;

    void resizeEvent(QResizeEvent *);
    void updateLotViewSize();
};

#endif // VIEWCONTAINER_H
