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

#ifndef LOTTERYTICKETBOOKCONFIGURATION_H
#define LOTTERYTICKETBOOKCONFIGURATION_H

#include <QObject>
#include "drawingconfiguration.h"

class LotteryTicketBookConfiguration : public DrawingConfiguration
{
    Q_OBJECT
public:
    explicit LotteryTicketBookConfiguration();

    std::shared_ptr<DrawingSession> createDrawingSession();
    LotView* createView();
    bool isValid() {return true;}
    WizardBase* wizard();
    virtual QString summary();

    int numBooks() {return _numBooks;}
    QString booksLabel() {return _booksLabel;}
    int numLotsPerBook() {return _numLotsPerBook;}
    QString lotsLabel() {return _lotsLabel;}

    void setNumBooks(int n) {_numBooks = n;}
    void setBooksLabel(const QString& s) {_booksLabel = s;}
    void setNumLotsPerBook(int n) {_numLotsPerBook = n;}
    void setLotsLabel(const QString& s) {_lotsLabel = s;}

private:
    int _numBooks, _numLotsPerBook;
    QString _booksLabel;
    QString _lotsLabel;
};

#endif // LOTTERYTICKETBOOKCONFIGURATION_H
