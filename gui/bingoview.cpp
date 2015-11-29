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

#include "bingoview.h"
#include "utils.h"
#include "numberlotelement.h"

BingoView::BingoView(const QString &longestText)
    : VerticalTextsView(1, longestText)
{
}

void BingoView::view(const NumberLotElement &numberLotElement, int id)
{
    ignore_unused(id);

    QString letter = findLetter(numberLotElement.number());
    setViewText(0, letter.append(" ").append(QString::number(numberLotElement.number())));
}

QString BingoView::findLetter(int n)
{
    if (in(n, 1, 15)) {
        return "B";
    } else if (in(n, 16, 30)) {
        return "I";
    } else if (in(n, 31, 45)) {
        return "N";
    } else if (in(n, 46, 60)) {
        return "G";
    } else if (in(n, 61, 75)) {
        return "O";
    } else {
        return "";
    }
}

bool BingoView::in(int n, int low, int high)
{
    return n >= low && n <= high;
}

