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

#ifndef LOTWINDOW_H
#define LOTWINDOW_H

#include <QWidget>

class ViewContainer;

namespace Ui {
class LotWindow;
}

class LotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LotWindow(QWidget *parent = 0);
    ~LotWindow();

    void setViewContainer(ViewContainer* viewContainer);
    ViewContainer* takeViewContainer();
    bool hasViewContainer();

    void setDrawingName(QString name) {_drawingName = name;}

private:
    Ui::LotWindow *ui;

    ViewContainer* _viewContainer;
    QString _drawingName;
};

#endif // LOTWINDOW_H
