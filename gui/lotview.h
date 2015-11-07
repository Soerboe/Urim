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
#include "lotelementviewer.h"
#include "utils.h"

class DrawingController;
class LoadingWidget;

class LotView : public QWidget, public LotElementViewer
{
    Q_OBJECT

public:
    explicit LotView(QWidget* parent = 0);
    ~LotView();

    virtual void view(const NumberLotElement& numberLotElement, int id) {
        ignore_unused(numberLotElement, id);
        // this method is supposed to be overridden in subclass views expecting NumberLotElements
    }

    virtual void view(const ColorLotElement& colorLotElement, int id) {
        ignore_unused(colorLotElement, id);
        // this method is supposed to be overridden in subclass views expecting ColorLotElements
    }

    void showLoading(bool visible);
    virtual void showLot(bool visible) = 0;

protected:
    virtual void calcViewSize() = 0;

private:
    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*event);
    LoadingWidget* _loadingWidget;
};

#endif // LOTVIEW_H
