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

#ifndef DRAWING_H
#define DRAWING_H

#include <QList>
#include <memory>

class Lot;

class Drawing
{
public:
    Drawing();

    void addLot(const std::shared_ptr<Lot> lot);
    bool operator==(const Drawing& that);

private:
    QList<std::shared_ptr<Lot> > _lots;
};

#endif // DRAWING_H
