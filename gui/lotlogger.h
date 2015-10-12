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

class Lot;
class QTreeWidget;
class DrawingSession;
class QString;

class LotLogger
{
public:
    LotLogger(QTreeWidget* view);

    void log(const Lot& lot, const std::shared_ptr<DrawingSession> session);
    void logMessage(const QString message);

private:
    // The view is managed by Qt
    QTreeWidget* _view;
};

#endif // LOTLOGGER_H
