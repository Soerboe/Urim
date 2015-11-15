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

#ifndef LOTTERYTICKETBOOKVIEW_H
#define LOTTERYTICKETBOOKVIEW_H

#include "twotextsview.h"

#define BOOKS_INDEX 0
#define LOTS_INDEX 1

class LotteryTicketBookView : public TwoTextsView
{
public:
    LotteryTicketBookView();

    virtual void view(const NumberLotElement& numberLotElement, int id);

private:
    QString createText(int number);
};

#endif // LOTTERYTICKETBOOKVIEW_H
