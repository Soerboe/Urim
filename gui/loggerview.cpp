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

#include "loggerview.h"
#include "logger.h"
#include <QTreeWidgetItem>

LoggerView::LoggerView(QTreeWidget *view, std::shared_ptr<Logger> logger)
    : _view(view),
      _logger(logger)
{
    _headerLabels << tr("No.") << tr("Time") << tr("Event");

    _view->setColumnCount(_headerLabels.size());
    _view->setHeaderLabels(_headerLabels);
    _view->resizeColumnToContents(0);
    _view->sortByColumn(1, Qt::DescendingOrder);

    _logger->setHeaderLabels(_headerLabels);

    connect(_logger.get(), SIGNAL(logUpdated()), SLOT(updateView()));
}

void LoggerView::updateView()
{
    _view->clear();

    for(auto rit = _logger->rbegin();
        rit != _logger->rend();
        ++rit) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, (*rit).index());
        item->setText(1, (*rit).time());
        item->setText(2, (*rit).text());
        _view->addTopLevelItem(item);
    }
}
