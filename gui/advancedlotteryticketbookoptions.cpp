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

#include "advancedlotteryticketbookoptions.h"
#include "ui_advancedconfigurationoptions.h"
#include <QLineEdit>
#include <QLabel>

AdvancedLotteryTicketBookOptions::AdvancedLotteryTicketBookOptions(const QString name)
    : AdvancedConfigurationOptions(name)
{
    hideViewsTab();

    QString placeholder(tr("Label"));

    _booksLabelEdit = new QLineEdit;
    _booksLabelEdit->setPlaceholderText(placeholder);
    _booksLabelEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _booksLabelEdit->setMinimumWidth(100);
    ui->setupLayout->addWidget(new QLabel(tr("Book label:")));
    ui->setupLayout->addWidget(_booksLabelEdit);

    _lotsLabelEdit = new QLineEdit;
    _lotsLabelEdit->setPlaceholderText(placeholder);
    _lotsLabelEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _lotsLabelEdit->setMinimumWidth(100);
    ui->setupLayout->addWidget(new QLabel(tr("Lot label:")));
    ui->setupLayout->addWidget(_lotsLabelEdit);

    ui->setupLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    adjustSize();
}

void AdvancedLotteryTicketBookOptions::init(const QString& booksLabel, const QString& lotsLabel)
{
    _booksLabelEdit->setText(booksLabel);
    _lotsLabelEdit->setText(lotsLabel);
}

QString AdvancedLotteryTicketBookOptions::booksLabel()
{
    return _booksLabelEdit->text();
}

QString AdvancedLotteryTicketBookOptions::lotsLabel()
{
    return _lotsLabelEdit->text();
}
