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

#include "configuredrawingdialog.h"
#include "configurenumberwidget.h"

class LotViewSelector;

class ConfigureSingleNumberDialog : public ConfigureDrawingDialog
{
    Q_OBJECT

public:
    ConfigureSingleNumberDialog(const QString name);

    void init(int min, int max, QString label, bool uniqueResults);
    virtual bool validate();
    virtual QString validationError();

    int min() {return _configureNumberWidget->min();}
    int max() {return _configureNumberWidget->max();}
    QString label() {return _configureNumberWidget->label();}

private:
    ConfigureNumberWidget* _configureNumberWidget;
    LotViewSelector* _lotViewSelector;

};

#endif // CONFIGURESINGLENUMBERDIALOG_H
