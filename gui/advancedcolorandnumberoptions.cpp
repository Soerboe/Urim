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

#include "advancedcolorandnumberoptions.h"
#include "ui_advancedconfigurationoptions.h"
#include <QGroupBox>
#include <QRadioButton>
#include "colorandnumberview_pog.h"
#include "colorandnumberview_border.h"
#include "lotviewselector.h"
#include "numberlotelement.h"
#include "colorlotelement.h"

AdvancedColorAndNumberOptions::AdvancedColorAndNumberOptions(const QString& title)
    : AdvancedConfigurationOptions(title),
      _lotViewSelector(new LotViewSelector())
{
    hideSetupTab();
    setupViewsTab();
    adjustSize();
}

void AdvancedColorAndNumberOptions::setupViewsTab()
{
    ColorAndNumberView_POG* pogView = new ColorAndNumberView_POG("1000");
    Color red = Color(Color::RED);
    pogView->view(ColorLotElement(red), 0);
    pogView->view(NumberLotElement(712), 0);
    _lotViewSelector->addView(pogView);

    ColorAndNumberView_Border* borderView = new ColorAndNumberView_Border(red.name().length() > 3 ? red.name() : "712");
    borderView->view(ColorLotElement(red), 0);
    borderView->view(NumberLotElement(712), 0);
    _lotViewSelector->addView(borderView);

    ui->viewsLayout->insertWidget(0, _lotViewSelector);
}

void AdvancedColorAndNumberOptions::init(int viewIndex)
{
    _lotViewSelector->init(viewIndex);
}

bool AdvancedColorAndNumberOptions::validate()
{
    return true;
}

QString AdvancedColorAndNumberOptions::validationError()
{
    return QString();
}
