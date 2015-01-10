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

#ifndef NUMBERLOTELEMENT_H
#define NUMBERLOTELEMENT_H

#include "lotelement.h"

class NumberLotElement : public LotElement
{
public:
    NumberLotElement(const int number);
    virtual void view(LotElementViewer &viewer);
    virtual bool operator==(const LotElement& that);
    virtual bool operator!=(const LotElement& that);

    int number() const {return _number;}
private:
    int _number;
};

#endif // NUMBERLOTELEMENT_H
