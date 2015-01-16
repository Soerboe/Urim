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
#include <QDateTime>
#include "numberlotelement.h"
#include "colorlotelement.h"
#include "utils.h"
#include "drawingsession.h"

using namespace std;

class LogItem : public QTreeWidgetItem
{
public:
    LogItem(QTreeWidget* parent = 0)
        : QTreeWidgetItem(parent)
    {
    }

private:
    bool operator< (const QTreeWidgetItem &other) const
    {
        int column = treeWidget()->sortColumn();
        if (column == 0) {
            bool okX, okY;
            int x = QString(text(column)).toInt(&okX);
            int y = QString(other.text(column)).toInt(&okY);
            if (okX && okY) {
                return x < y;
            }
        }

        // fallback to string compare
        return text(column).toLower() < other.text(column).toLower();
    }
};

class LogItemBuilder : public LotElementViewer
{
public:
    LogItem* create()
    {
        QDateTime time = QDateTime::currentDateTime();
        _item.setText(1, time.toString("hh:mm:ss"));
        return new LogItem(_item);
    }

    void setIndex(int index)
    {
        _item.setText(0, QString::number(index));
    }

    void addLotElement(QString s) {
        QString text = _item.text(2);
        if (!text.isEmpty()) {
            text.append(", ");
        }

        text.append(s);
        _item.setText(2, text);
    }

    void view(const NumberLotElement& numberLotElement, const int& id)
    {
        ignore_unused(id);
        addLotElement(QString(numberLotElement.name().c_str()) + ": " + QString::number(numberLotElement.number()));
    }

    void view(const ColorLotElement& colorLotElement, const int& id)
    {
        ignore_unused(id);
        addLotElement(QString(colorLotElement.name().c_str()) + ": " + QString(colorLotElement.color().name));
    }

private:
    LogItem _item;
};


LotLogger::LotLogger(QTreeWidget* view)
    : _view(view)
{
}

void LotLogger::log(const Lot& lot, const shared_ptr<DrawingSession> drawingsession)
{
    LogItemBuilder builder;
    builder.setIndex(drawingsession->lotsCount());
    for (unsigned int i = 0; i < lot.count(); ++i) {
        lot.at(i)->view(builder, i);
    }

    _view->addTopLevelItem(builder.create());
}
