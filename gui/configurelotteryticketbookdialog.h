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

#ifndef CONFIGURELOTTERYTICKETBOOKDIALOG_H
#define CONFIGURELOTTERYTICKETBOOKDIALOG_H

#include <QObject>
#include "configuredrawingdialog.h"
#include "configureamountwidget.h"
#include "lotviewselector.h"

#define NUM_BOOKS_INDEX 0
#define NUM_LOTS_INDEX 1

class ConfigureLotteryTicketBookDialog : public ConfigureDrawingDialog
{
    Q_OBJECT

public:
    ConfigureLotteryTicketBookDialog(const QString name);

    void init(int numBooks, QString booksLabel, int numLotsPerBook, QString lotsLabel, bool uniqueResults, int viewIndex);
    virtual bool validate() {return true;}
    virtual QString validationError() {return "";}

    int numBooks() {return _configureWidget->amount(NUM_BOOKS_INDEX);}
    QString booksLabel() {return _configureWidget->label(NUM_BOOKS_INDEX);}
    int numLotsPerBook() {return _configureWidget->amount(NUM_LOTS_INDEX);}
    QString lotsLabel() {return _configureWidget->label(NUM_LOTS_INDEX);}
    int viewIndex() {return _lotViewSelector->selectedViewIndex();}

private:
    ConfigureAmountWidget* _configureWidget;
    LotViewSelector* _lotViewSelector;

    void setupViewsTab();
};

#endif // CONFIGURELOTTERYTICKETBOOKDIALOG_H
