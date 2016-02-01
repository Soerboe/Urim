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

#ifndef ADVANCEDCOLORANDNUMBEROPTIONS_H
#define ADVANCEDCOLORANDNUMBEROPTIONS_H

#include "advancedconfigurationoptions.h"
#include "lotviewselector.h"

class AdvancedColorAndNumberOptions : public AdvancedConfigurationOptions
{
    Q_OBJECT

public:
    AdvancedColorAndNumberOptions(const QString &title);

    void init(int viewIndex);
    int viewIndex() {return _lotViewSelector->selectedViewIndex();}

protected:
    virtual bool validate();
    virtual QString validationError();

private:
    LotViewSelector* _lotViewSelector;

    void setupViewsTab();
};

#endif // ADVANCEDCOLORANDNUMBEROPTIONS_H
