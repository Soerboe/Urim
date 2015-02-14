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

#define MAX_FONT_SIZE 500

class DrawingController;

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

protected:
    virtual void calcViewSize() = 0;

    int calcMaxFontSize(const QFont& originalFont, const QString& text, const QRect& boundingBox) const;

private:
    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*);
};

#endif // LOTVIEW_H
