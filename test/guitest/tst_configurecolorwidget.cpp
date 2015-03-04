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

#include "testrunner.h"
#include <QtTest>
#include "configurecolorwidget.h"
#include <algorithm>
#include "color.h"
#include "QToolButton"
#include "QTreeWidget"

class ConfigureColorWidgetTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:

void shouldInitializeColors()
{
    ConfigureColorWidget widget;
    std::vector<Color> defaultColors;
    defaultColors.push_back(Color(0,0,0, "Red"));
    defaultColors.push_back(Color(0,0,0, "Green"));
    QString label("ColorLabel");
    widget.init(defaultColors, label);
    std::vector<Color> colors = widget.colors();

    QVERIFY(std::any_of(colors.begin(), colors.end(), [](Color c) {return c.name == "Red";}));
    QVERIFY(std::any_of(colors.begin(), colors.end(), [](Color c) {return c.name == "Green";}));
}

void shouldSelectColors() {
    ConfigureColorWidget widget;
    QTreeWidget* availableColors = widget.findChild<QTreeWidget*>("availableColorsWidget");
    availableColors->selectAll();
    QToolButton* select = widget.findChild<QToolButton*>("selectColorButton");
    select->click();
    std::vector<Color> colors = widget.colors();

    QVERIFY(colors.size() > 0);
}

void shouldValidateFalseWhenNoSelectedColors() {
    ConfigureColorWidget widget;
    QTreeWidget* selectedColors = widget.findChild<QTreeWidget*>("selectedColorsWidget");
    selectedColors->selectAll();
    QToolButton* deselect = widget.findChild<QToolButton*>("deselectColorButton");
    deselect->click();
    QVERIFY(widget.validate() == false);
}

void shouldValidateTrueWhenColorSelected() {
    ConfigureColorWidget widget;
    QTreeWidget* availableColors = widget.findChild<QTreeWidget*>("availableColorsWidget");
    availableColors->setCurrentItem(availableColors->topLevelItem(0));
    QToolButton* select = widget.findChild<QToolButton*>("selectColorButton");
    select->click();
    QVERIFY(widget.validate() == true);
}

};

REGISTER_TEST(ConfigureColorWidgetTest)

#include "tst_configurecolorwidget.moc"

