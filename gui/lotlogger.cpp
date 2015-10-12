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

#include "lotlogger.h"
#include "lot.h"
#include "lotelement.h"
#include "lotelementviewer.h"
#include <QTreeWidgetItem>
#include "numberlotelement.h"
#include "colorlotelement.h"
#include "utils.h"
#include "drawingsession.h"

using namespace std;

class LogItemBuilder : public LotElementViewer
{
public:
    LogItem create()
    {
        QDateTime time = QDateTime::currentDateTime();
        _item.setTime(time);
        return LogItem(_item);
    }

    void setIndex(int index)
    {
        _item.setIndex(index);
    }

    void addText(QString s) {
        QString text = _item.text();
        if (!text.isEmpty()) {
            text.append(", ");
        }

        text.append(s);
        _item.setText(text);
    }

    void view(const NumberLotElement& numberLotElement, int id)
    {
        ignore_unused(id);
        QString label(numberLotElement.name().c_str());
        if (!label.isEmpty()) {
            label.append(": ");
        }
        addText(label + QString::number(numberLotElement.number()));
    }

    void view(const ColorLotElement& colorLotElement, int id)
    {
        ignore_unused(id);
        QString label(colorLotElement.name().c_str());
        if (!label.isEmpty()) {
            label.append(": ");
        }
        addText(label + QString(colorLotElement.color().name));
    }

private:
    LogItem _item;
};


LotLogger::LotLogger(QTreeWidget* view)
    : _view(view)
{
}

void LotLogger::log(const Lot& lot, const shared_ptr<DrawingSession> session)
{
    LogItemBuilder builder;
    builder.setIndex(session->lotsCount());
    for (unsigned int i = 0; i < lot.count(); ++i) {
        lot.at(i)->view(builder, i);
    }

    _log.push_back(builder.create());
    updateView();
}

void LotLogger::logMessage(const QString message)
{
    LogItemBuilder builder;
    builder.addText(message);
    _log.push_back(builder.create());
    updateView();
}

void LotLogger::clear()
{
    _log.clear();
}

void LotLogger::updateView()
{
    _view->clear();

    for(vector<LogItem>::reverse_iterator rit = _log.rbegin();
        rit != _log.rend();
        ++rit) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, (*rit).index());
        item->setText(1, (*rit).time());
        item->setText(2, (*rit).text());
        _view->addTopLevelItem(item);
    }
}
