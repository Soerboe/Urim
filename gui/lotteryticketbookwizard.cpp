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

#include "lotteryticketbookwizard.h"
#include "configureamountwidget.h"
#include "QVBoxLayout"
#include "lotteryticketbookconfiguration.h"
#include "advancedlotteryticketbookoptions.h"

#define NUM_BOOKS_INDEX 0
#define NUM_LOTS_INDEX 1

class BookConfigPage : public WizardPage
{
    Q_OBJECT
public:
    BookConfigPage(std::shared_ptr<LotteryTicketBookConfiguration> config)
        : _config(config),
          _configureWidget(new ConfigureAmountWidget)
    {
        _configureWidget->addAmountSelector(tr("Number of books"), tr("Choose the total number of lottery ticket books"), _config->numBooks());
        _configureWidget->addAmountSelector(tr("Number of lots per book"), tr("Choose the number of lots per lottery ticket book"), _config->numLotsPerBook());

        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin(0);
        l->addWidget(_configureWidget);
        l->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        setLayout(l);
        connect(_configureWidget, &ConfigureAmountWidget::changed, this, updateFields);
    }

    void updateFields() {
        _config->setNumBooks(_configureWidget->amount(NUM_BOOKS_INDEX));
        _config->setNumLotsPerBook(_configureWidget->amount(NUM_LOTS_INDEX));
        emit changed(isValid());
    }

    bool isValid() {
        return true;
    }

    QString validationError() {
        return QString();
    }

private:
    std::shared_ptr<LotteryTicketBookConfiguration> _config;
    ConfigureAmountWidget* _configureWidget;
};

#include "lotteryticketbookwizard.moc"

LotteryTicketBookWizard::LotteryTicketBookWizard(std::shared_ptr<LotteryTicketBookConfiguration> config)
    : WizardBase(config, true),
      _config(config)
{
    _bookConfigPage = new BookConfigPage(_config);
    _uniqueResultsConfigPage = new UniqueResultsConfigPage(_config);
    addPage(_bookConfigPage);
    addPage(_uniqueResultsConfigPage);
}

void LotteryTicketBookWizard::advancedSetup()
{
    AdvancedLotteryTicketBookOptions dialog(_config->name());
    dialog.init(_config->booksLabel(), _config->lotsLabel());

    if (dialog.exec() == QDialog::Accepted) {
        _config->setBooksLabel(dialog.booksLabel());
        _config->setLotsLabel(dialog.lotsLabel());
    }
}

