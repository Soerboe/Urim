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

#ifndef LOTVIEW_H
#define LOTVIEW_H

#include <QWidget>

class DrawingController;

namespace Ui {
class LotView;
}

class LotView : public QWidget
{
    Q_OBJECT

public:
    explicit LotView(DrawingController* controller, QWidget* parent = 0);
    ~LotView();

    void initializeViews();

    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent*);
    void calcFontSize();

private:
    Ui::LotView *ui;
    DrawingController* _controller;

    void initFont();
};

#endif // LOTVIEW_H
