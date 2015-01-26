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

#ifndef CONFIGURESINGLENUMBERDIALOG_H
#define CONFIGURESINGLENUMBERDIALOG_H

#include <QObject>
#include "configuredrawingdialog.h"

class QSpinBox;

class ConfigureSingleNumberDialog : public ConfigureDrawingDialog
{
    Q_OBJECT

public:
    ConfigureSingleNumberDialog(const QString name);
    ~ConfigureSingleNumberDialog();

    void init(int min, int max, bool uniqueResults);
    virtual bool validate();
    virtual void prepareResults();

    int min() {return _min;}
    int max() {return _max;}

private:
    int _min, _max;
    QSpinBox* _minSpin;
    QSpinBox* _maxSpin;
};

#endif // CONFIGURESINGLENUMBERDIALOG_H
