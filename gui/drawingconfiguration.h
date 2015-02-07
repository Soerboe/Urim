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
#include <color.h>

class DrawingSession;
class LotViewer;
class NumberLotElementView;
class ColorLotElementView;

class DrawingConfiguration : public QObject
{
    Q_OBJECT

public:
    DrawingConfiguration(const QString& name, QObject* parent = 0);
    virtual ~DrawingConfiguration();

    virtual std::shared_ptr<DrawingSession> createDrawingSession() = 0;
    virtual std::shared_ptr<LotViewer> createViewer() = 0;
    virtual void configure() = 0;
    virtual bool isValid() = 0;

    QString summary();
    QString name() {return _name;}
    bool uniqueResults() {return _uniqueResults;}

protected:
    bool _uniqueResults;

    NumberLotElementView* buildNumberLotElementView(int min, int max);
    ColorLotElementView* buildColorLotElementView(std::vector<Color>& colors);
    virtual QString detailedSummary() = 0;

private:
    QString _name;
};

#endif // DRAWINGCONFIGURATION_H
