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
#include <QFile>
#include <QTextStream>

using namespace std;

class LogItemBuilder : public LotElementViewer
{
public:
    LogItemBuilder(QString eventPrefix = 0) :
        _eventPrefix(eventPrefix)
    {}

    LogItem create()
    {
        QDateTime time = QDateTime::currentDateTime();
        _item.setTime(time);
        if (!_eventPrefix.isEmpty()) {
            _item.setText(_eventPrefix + _item.text());
        }
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
    QString _eventPrefix;
};


LotLogger::LotLogger(QTreeWidget* view)
    : _view(view)
{
}

void LotLogger::log(const Lot& lot, const shared_ptr<DrawingSession> session)
{
    LogItemBuilder builder(tr("Lot drawn: "));
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

bool LotLogger::saveToFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    if (_headerLabels.size() > 0) {
        for (QString s : _headerLabels) {
            out << s << "\t";
        }
        out << "\n";
    }

    for(vector<LogItem>::reverse_iterator rit = _log.rbegin();
        rit != _log.rend();
        ++rit) {
        out << (*rit).index() << "\t"
            << (*rit).time() << "\t"
            << (*rit).text() << "\n";
    }

    return true;
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
