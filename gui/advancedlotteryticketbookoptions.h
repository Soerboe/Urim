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

#ifndef ADVANCEDLOTTERYTICKETBOOKOPTIONS_H
#define ADVANCEDLOTTERYTICKETBOOKOPTIONS_H

#include <QObject>
#include "advancedconfigurationoptions.h"
#include "lotviewselector.h"

class QLineEdit;

class AdvancedLotteryTicketBookOptions : public AdvancedConfigurationOptions
{
    Q_OBJECT

public:
    AdvancedLotteryTicketBookOptions(const QString name);

    void init(const QString& booksLabel, const QString& lotsLabel);
    QString booksLabel();
    QString lotsLabel();

protected:
    virtual bool validate() {return true;}
    virtual QString validationError() {return "";}

private:
    QLineEdit* _booksLabelEdit;
    QLineEdit* _lotsLabelEdit;
};

#endif // ADVANCEDLOTTERYTICKETBOOKOPTIONS_H
