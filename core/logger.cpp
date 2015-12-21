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

#include "logger.h"
#include "utils.h"
#include "lot.h"
#include "lotelement.h"
#include "lotelementviewer.h"
#include "numberlotelement.h"
#include "colorlotelement.h"
#include "drawingsession.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include "xlsxdocument.h"

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
        addText(label + QString(colorLotElement.color().name()));
    }

private:
    LogItem _item;
    QString _eventPrefix;
};

Logger::Logger()
    : QObject(0)
{
}

void Logger::log(const Lot& lot, const shared_ptr<DrawingSession> session)
{
    LogItemBuilder builder(tr("Lot drawn: "));
    builder.setIndex(session->lotsCount());
    for (unsigned int i = 0; i < lot.count(); ++i) {
        lot.at(i)->view(builder, i);
    }

    _log.push_back(builder.create());
    emit logUpdated();
}

void Logger::logMessage(const QString message)
{
    LogItemBuilder builder;
    builder.addText(message);
    _log.push_back(builder.create());
    emit logUpdated();
}

void Logger::clear()
{
    _log.clear();
    emit logUpdated();
}

bool Logger::saveToFile(QFileInfo fileInfo)
{
    QFile file(fileInfo.absoluteFilePath());
    if (fileInfo.suffix() == LOG_SUFFIX) {
        return saveToLogFile(file);
    } else if (fileInfo.suffix() == EXCEL_SUFFIX) {
        return saveToExcelFile(file);
    } else {
        qDebug() << "Unknown file suffix: " << fileInfo.suffix();
        return false;
    }
}

bool Logger::saveToLogFile(QFile &file)
{
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

bool Logger::saveToExcelFile(QFile &file)
{
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QXlsx::Document doc;

    if (_headerLabels.size() > 0) {
        int col = 1;
        for (QString s : _headerLabels) {
            doc.write(1, col++, s);
        }
    }

    int row = 2;
    for(vector<LogItem>::reverse_iterator rit = _log.rbegin();
        rit != _log.rend();
        ++rit) {
        doc.write(row, 1, (*rit).index());
        doc.write(row, 2, (*rit).time());
        doc.write(row, 3, (*rit).text());
        ++row;
    }

    return doc.saveAs(&file);
}
