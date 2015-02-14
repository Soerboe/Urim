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

#ifndef LOT_H
#define LOT_H

#include <QList>
#include <memory>
#include <ostream>

class LotElement;
class LotElementViewer;

class Lot
{
public:
    Lot();

    void addLotElement(const std::shared_ptr<LotElement> lotElement);
    bool operator==(const Lot& that);
    void view(LotElementViewer& viewer);

    std::shared_ptr<LotElement> at(int index) const;
    size_t count() const;

    friend std::ostream& operator<< (std::ostream& output, const Lot& lot);

private:
    QList<std::shared_ptr<LotElement> > _lotElements;
};

#endif // LOT_H
