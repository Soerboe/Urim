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

#ifndef SINGLENUMBERCONFIGURATION_H
#define SINGLENUMBERCONFIGURATION_H

#include "drawingconfiguration.h"

#define DEFAULT_MIN 1
#define DEFAULT_MAX 1000

class SingleNumberConfiguration : public DrawingConfiguration
{
    Q_OBJECT

public:
    SingleNumberConfiguration();

    std::shared_ptr<DrawingSession> createDrawingSession();
    LotView* createView();
    bool isValid();
    WizardBase* wizard();
    virtual QString summary();

    int min() {return _min;}
    int max() {return _max;}
    QString label() {return _label;}
    void setMin(int min) {_min = min;}
    void setMax(int max) {_max = max;}
    void setLabel(const QString& label) {_label = label;}

private:
    int _min, _max;
    QString _label;
};

#endif // SINGLENUMBERCONFIGURATION_H
