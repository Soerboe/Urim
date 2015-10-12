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

#ifndef LOTLOGGER_H
#define LOTLOGGER_H

#include <memory>
#include <vector>
#include <QString>
#include <QDateTime>

class Lot;
class QTreeWidget;
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

class LotLogger
{
public:
    LotLogger(QTreeWidget* view);

    void log(const Lot& lot, const std::shared_ptr<DrawingSession> session);
    void logMessage(const QString message);
    void clear();

private:
    // The view is managed by Qt
    QTreeWidget* _view;
    std::vector<LogItem> _log;

    void updateView();
};

#endif // LOTLOGGER_H
