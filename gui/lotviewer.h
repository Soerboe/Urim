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

#ifndef LOTVIEWER_H
#define LOTVIEWER_H

#include "lotelementviewer.h"
#include <QMap>
#include <memory>
#include "lot.h"

class LotElementView;

class LotViewer : public LotElementViewer
{
public:
    LotViewer();

    void view(const Lot& lot);
    void view(const NumberLotElement& numberLotElement, const int& id);
    void view(const ColorLotElement& colorLotElement, const int& id);

    void addView(const int& id, LotElementView* view);
private:
    // Save as raw pointers here. Since the views are added
    // to a Qt widget, Qt will handle the memory management.
    QMap<int, LotElementView*> _views;
};

#endif // LOTVIEWER_H
