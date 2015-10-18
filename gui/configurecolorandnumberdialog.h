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

#ifndef CONFIGURECOLORANDNUMBERDIALOG_H
#define CONFIGURECOLORANDNUMBERDIALOG_H

#include "configuredrawingdialog.h"
#include "color.h"
#include "lotviewselector.h"

class ConfigureColorWidget;

class ConfigureColorAndNumberDialog : public ConfigureDrawingDialog
{
    Q_OBJECT

public:
    ConfigureColorAndNumberDialog(const QString name);

    void init(const std::vector<Color>& colors, QString colorLabel, int min, int max, QString numberLabel, bool uniqueResults, int viewIndex);
    virtual bool validate();
    virtual QString validationError();

    int min() {return _configureNumberWidget->min();}
    int max() {return _configureNumberWidget->max();}
    QString numberLabel() {return _configureNumberWidget->label();}

    std::vector<Color> colors();
    QString colorLabel();
    int viewIndex() {return _lotViewSelector->selectedViewIndex();}

private:
    ConfigureColorWidget* _configureColorWidget;
    ConfigureNumberWidget* _configureNumberWidget;
    LotViewSelector* _lotViewSelector;

    void setupViewsTab();
};

#endif // CONFIGURECOLORANDNUMBERDIALOG_H
