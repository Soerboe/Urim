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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include "memory"
#include <QIcon>

class DrawingSession;
class LotView;
class WizardBase;

class Configuration : public QObject, public std::enable_shared_from_this<Configuration>
{
    Q_OBJECT
public:
    Configuration(const QString& name, const QString& description, const QIcon& icon, bool configurable);

    virtual std::shared_ptr<DrawingSession> createDrawingSession() = 0;
    virtual LotView* createView() = 0;
    virtual bool isValid() = 0;
    virtual QString summary() = 0;
    virtual WizardBase* wizard() = 0;

    QString name() {return _name;}
    QString description() {return _description;}
    QIcon icon() {return _icon;}
    bool configurable() {return _configurable;}

private:
    QString _name;
    QString _description;
    QIcon _icon;
    bool _configurable;
};

#endif // CONFIGURATION_H
