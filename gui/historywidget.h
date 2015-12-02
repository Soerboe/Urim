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

#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

class LotView;

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget *parent = 0);
    ~HistoryWidget();

    void addItem(LotView* lotView);
    void clear();

private:
    Ui::HistoryWidget* ui;

    void updateLotViews();
    void updateHeaderFont();
    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*event);

    int lotViewHeight();
    QWidget *createSeparator();
};

#endif // HISTORYWIDGET_H
