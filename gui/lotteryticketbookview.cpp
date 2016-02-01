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

#include "lotteryticketbookview.h"
#include "numberlotelement.h"

LotteryTicketBookView::LotteryTicketBookView(const QString& longestText)
    : VerticalTextsView(2, longestText)
{}

void LotteryTicketBookView::view(const NumberLotElement &numberLotElement, int id)
{
    QString text;
    if (!numberLotElement.name().empty()) {
        text.append(numberLotElement.name().c_str()).append(": ");
    }
    text.append(createText(numberLotElement.number()));
    setViewText(id, text);
}

QString LotteryTicketBookView::createText(int number)
{
    QString text;
//    return text.append("<strong>").append(QString::number(number)).append("</strong>");
    return text.append(QString::number(number));
}

