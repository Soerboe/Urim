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

#include "configurelotteryticketbookdialog.h"
#include "ui_configuredrawingdialog.h"
#include "lotteryticketbookview.h"
#include "numberlotelement.h"

ConfigureLotteryTicketBookDialog::ConfigureLotteryTicketBookDialog(const QString name)
    : ConfigureDrawingDialog(name),
      _configureWidget(new ConfigureAmountWidget(tr("Lottery ticket books"))),
      _lotViewSelector(new LotViewSelector())
{
    _configureWidget->addAmountSelector(tr("Number of books:"), 1, tr("Book label:"), tr("Book"));
    _configureWidget->addAmountSelector(tr("Number of lots per book:"), 1000, tr("Lot label:"), tr("Lot"));
    ui->setupLayout->insertWidget(0, _configureWidget);

    setupViewsTab();
    adjustSize();
}

void ConfigureLotteryTicketBookDialog::init(int numBooks, QString booksLabel, int numLotsPerBook, QString lotsLabel, bool uniqueResults, int viewIndex)
{
    ConfigureDrawingDialog::init(uniqueResults);
    _configureWidget->init(NUM_BOOKS_INDEX, numBooks, booksLabel);
    _configureWidget->init(NUM_LOTS_INDEX, numLotsPerBook, lotsLabel);
    _lotViewSelector->init(viewIndex);
}

void ConfigureLotteryTicketBookDialog::setupViewsTab()
{
    QString book(tr("Book"));
    QString lot(tr("Lot"));

    QString bookView = QString(book).append(": ").append(QString::number(3));
    QString lotView = QString(lot).append(": ").append(QString::number(712));
    LotteryTicketBookView* view = new LotteryTicketBookView(bookView.size() > lotView.size() ? bookView : lotView);
    NumberLotElement bookElement(3);
    bookElement.setName(book.toStdString());
    view->view(bookElement, BOOKS_INDEX);

    NumberLotElement lotsElement(712);
    lotsElement.setName(lot.toStdString());
    view->view(lotsElement, LOTS_INDEX);
    _lotViewSelector->addView(view);
    ui->viewsLayout->insertWidget(0, _lotViewSelector);
}

