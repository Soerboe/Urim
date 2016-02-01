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

#ifndef DRAWINGCONFIGURATION_H
#define DRAWINGCONFIGURATION_H

#include <QObject>
#include <QString>
#include <memory>
#include "configuration.h"

class DrawingConfiguration : public Configuration
{
    Q_OBJECT

public:
    DrawingConfiguration(const QString& name, const QString& description, const QIcon &icon, bool configurable);
    virtual ~DrawingConfiguration();

    virtual QString summary() = 0;
    bool uniqueResults() {return _uniqueResults;}
    void setUniqueResults(bool uniqueResults) {_uniqueResults = uniqueResults;}

protected:
    bool _uniqueResults;
    QString uniqueResultsSummary();
};

#endif // DRAWINGCONFIGURATION_H
