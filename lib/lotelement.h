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

#ifndef LOTELEMENT_H
#define LOTELEMENT_H

class LotElementViewer;

class LotElement
{
public:
    LotElement();
    virtual void view(LotElementViewer& viewer) = 0;
    virtual bool operator==(const LotElement& that) = 0;
    virtual bool operator!=(const LotElement& that) = 0;
};

#endif // LOTELEMENT_H