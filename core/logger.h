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

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <vector>
#include <memory>
#include <QDateTime>
#include <QFileInfo>

#define LOG_SUFFIX "log"
#define EXCEL_SUFFIX "xlsx"

class Lot;
class DrawingSession;

class LogItem {
public:
    QString index() {return _index;}
    void setIndex(int index) {_index = QString::number(index);}

    QString time() {return _time;}
    void setTime(QDateTime time) {_time = time.toString("hh:mm:ss");}

    QString text() {return _text;}
    void setText(QString text) {_text = text;}
private:
    QString _index;
    QString _time;
    QString _text;
};

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger();

    void log(const Lot& lot, const std::shared_ptr<DrawingSession> session);
    void logMessage(const QString message);
    void clear();
    void setHeaderLabels(QStringList list) {_headerLabels = list;}

    std::vector<LogItem>::iterator begin() {return _log.begin();}
    std::vector<LogItem>::iterator end() {return _log.end();}
    std::vector<LogItem>::reverse_iterator rbegin() {return _log.rbegin();}
    std::vector<LogItem>::reverse_iterator rend() {return _log.rend();}

    bool saveToFile(QFileInfo fileInfo);

signals:
    void logUpdated();

private:
    std::vector<LogItem> _log;
    QStringList _headerLabels;

    bool saveToLogFile(QFile &file);
    bool saveToExcelFile(QFile &file);
};

#endif // LOGGER_H
