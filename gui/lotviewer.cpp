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

#include "lotviewer.h"
#include "numberlotelementview.h"
#include "colorlotelementview.h"

using namespace std;

LotViewer::LotViewer()
{
}

void LotViewer::view(const Lot& lot)
{
    for (unsigned int i = 0; i < lot.count(); ++i) {
        lot.at(i)->view(*this, i);
    }
}

void LotViewer::view(const NumberLotElement& numberLotElement, const int& id)
{
    shared_ptr<LotElementView> view = _views.value(id);
    view->update(numberLotElement);
}

void LotViewer::view(const ColorLotElement& colorLotElement, const int& id)
{
    shared_ptr<LotElementView> view = _views.value(id);
    view->update(colorLotElement);
}

void LotViewer::addView(const int& id, const shared_ptr<LotElementView> view)
{
    _views.insert(id, view);
}
