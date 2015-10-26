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

#ifndef LOGGERVIEW_H
#define LOGGERVIEW_H

#include <QObject>
#include <QStringList>
#include <memory>

class QTreeWidget;
class Logger;

class LoggerView : public QObject
{
    Q_OBJECT

public:
    LoggerView(QTreeWidget* view, std::shared_ptr<Logger> logger);

private:
    // The view is managed by Qt
    QTreeWidget* _view;
    QStringList _headerLabels;
    std::shared_ptr<Logger> _logger;

private slots:
    void updateView();
};

#endif // LOGGERVIEW_H
