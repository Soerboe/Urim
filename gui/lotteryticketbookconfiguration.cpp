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

#include "lotteryticketbookconfiguration.h"
#include <memory>
#include "randomnumbergenerator.h"
#include "lotteryticketbookview.h"
#include "drawingsession.h"
#include "lotteryticketbookwizard.h"

using namespace std;

LotteryTicketBookConfiguration::LotteryTicketBookConfiguration()
    : DrawingConfiguration(tr("Lottery ticket book"), tr("Draw lots from lottery ticket books"), QIcon(":/gui/icons/lotterybookdrawing.svg"), true),
      _numBooks(1),
      _numLotsPerBook(1000),
      _booksLabel(tr("Book")),
      _lotsLabel(tr("Lot"))
{
}

std::shared_ptr<DrawingSession> LotteryTicketBookConfiguration::createDrawingSession()
{
    shared_ptr<DrawingSession> session(new DrawingSession(_uniqueResults));
    shared_ptr<RandomNumberGenerator> booksGenerator(new RandomNumberGenerator(1, _numBooks));
    booksGenerator->setName(_booksLabel.toStdString());
    session->addGenerator(booksGenerator);

    shared_ptr<RandomNumberGenerator> lotsGenerator(new RandomNumberGenerator(1, _numLotsPerBook));
    lotsGenerator->setName(_lotsLabel.toStdString());
    session->addGenerator(lotsGenerator);

    return session;
}

LotView *LotteryTicketBookConfiguration::createView()
{
    QString bookView = QString(_booksLabel).append(": ").append(QString::number(_numBooks));
    QString lotView = QString(_lotsLabel).append(": ").append(QString::number(_numLotsPerBook));
    return new LotteryTicketBookView(bookView.size() > lotView.size() ? bookView : lotView);
}


WizardBase *LotteryTicketBookConfiguration::wizard()
{
    return new LotteryTicketBookWizard(dynamic_pointer_cast<LotteryTicketBookConfiguration> (shared_from_this()));
}

QString LotteryTicketBookConfiguration::summary()
{
    QString s;
    s.append("<div>");
    s.append(tr("Number of books") + ": " + QString::number(_numBooks));
    s.append("</div><div>");
    s.append(tr("Number of lots per book") + ": " + QString::number(_numLotsPerBook));
    s.append("</div>");
    if (!_booksLabel.isEmpty()) {
        s.append("<div>");
        s.append(tr("Book label") + ": " + _booksLabel);
        s.append("</div>");
    }
    if (!_lotsLabel.isEmpty()) {
        s.append("<div>");
        s.append(tr("Lots label") + ": " + _lotsLabel);
        s.append("</div>");
    }
    s.append(uniqueResultsSummary());
    return s;
}

