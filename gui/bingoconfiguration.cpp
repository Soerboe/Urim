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

#include "bingoconfiguration.h"
#include <memory>
#include "randomnumbergenerator.h"
#include "drawingsession.h"
#include "bingoview.h"

using namespace std;

BingoConfiguration::BingoConfiguration()
    : Configuration(tr("Bingo"), tr("Draws standard 5x5 bingo card lots"), QIcon(":/gui/icons/bingodrawing.svg"), false)
{
}

std::shared_ptr<DrawingSession> BingoConfiguration::createDrawingSession()
{
    shared_ptr<RandomNumberGenerator> generator(new RandomNumberGenerator(1, 75));
    shared_ptr<DrawingSession> session(new DrawingSession(true));
    session->addGenerator(generator);
    return session;
}

LotView *BingoConfiguration::createView()
{
    return new BingoView("O 75");
}

bool BingoConfiguration::isValid()
{
    return true;
}

QString BingoConfiguration::summary()
{
    QString s;
    s.append("<h3>");
    s.append(tr("Draw bingo numbers"));
    s.append("</h3>");
    s.append("<div>");
    s.append(tr("Standard 5x5 bingo cards"));
    s.append("</div>");
    return s;
}

WizardBase *BingoConfiguration::wizard()
{
    return 0;
}

