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

#include "configurecolorwidget.h"
#include "ui_configurecolorwidget.h"
#include <QTreeWidgetItem>

using namespace std;

vector<Color> ConfigureColorWidget::_availableColors (
    {
        Color(220, 0, 0,     tr("Red")),
        Color(0, 200, 0,     tr("Green")),
        Color(0, 0, 255,     tr("Blue")),
        Color(255, 255, 0,   tr("Yellow")),
        Color(255, 255, 255, tr("White")),
        Color(0, 0, 0,       tr("Black")),
        Color(128, 128, 128, tr("Grey")),
        Color(110, 0, 0,     tr("Dark red")),
        Color(0, 0, 90,      tr("Dark blue")),
        Color(0, 80, 0,      tr("Dark green")),
        Color(255, 62, 150,  tr("Pink")),
        Color(155, 48, 255,  tr("Purple")),
        Color(255, 97, 3,    tr("Orange")),
        Color(138, 54, 15,   tr("Brown"))
    }
);

class ColorItem : public QTreeWidgetItem
{
public:
    ColorItem(const Color& color)
        : _color(color)
    {
        setBackgroundColor(0, QColor(color.red, color.green, color.blue));
        setText(1, color.name);
    }

    Color color() {return _color;}

private:
    Color _color;
};

ConfigureColorWidget::ConfigureColorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureColorWidget)
{
    ui->setupUi(this);
    ui->availableColorsWidget->setColumnCount(2);
    ui->selectedColorsWidget->setColumnCount(2);
    initAvailableColors();

    ui->availableColorsWidget->setSortingEnabled(true);
    ui->availableColorsWidget->sortByColumn(1, Qt::AscendingOrder);
    ui->selectedColorsWidget->setSortingEnabled(true);
    ui->selectedColorsWidget->sortByColumn(1, Qt::AscendingOrder);

    connect(ui->selectColorButton, SIGNAL(clicked()), SLOT(selectClicked()));
    connect(ui->deselectColorButton, SIGNAL(clicked()), SLOT(deselectClicked()));
}

ConfigureColorWidget::~ConfigureColorWidget()
{
    delete ui;
}

void ConfigureColorWidget::init(const vector<Color>& colors, QString& label)
{
    ui->colorLabel->setText(label);

    for (size_t i = 0 ; i < colors.size(); ++i) {
        for (int j = 0; j < ui->availableColorsWidget->topLevelItemCount(); ++j) {
            ColorItem* item = dynamic_cast<ColorItem*> (ui->availableColorsWidget->topLevelItem(j));
            if (item && item->color().name == colors[i].name) {
                delete item;
            }
        }

        ui->selectedColorsWidget->addTopLevelItem(new ColorItem(colors[i]));
    }
}

bool ConfigureColorWidget::validate()
{
    return ui->selectedColorsWidget->topLevelItemCount() > 0;
}

QString ConfigureColorWidget::colorLabel()
{
    return ui->colorLabel->text();
}

vector<Color> ConfigureColorWidget::colors()
{
    vector<Color> c;
    for(int i = 0; i < ui->selectedColorsWidget->topLevelItemCount(); ++i) {
        ColorItem* item = dynamic_cast<ColorItem*> (ui->selectedColorsWidget->topLevelItem(i));
        c.push_back(item->color());
    }

    return c;
}

Color ConfigureColorWidget::getAvailableColor(QString name)
{
    for (size_t i = 0; i < _availableColors.size(); ++i) {
        if (_availableColors[i].name == name) {
            return _availableColors[i];
        }
    }

    return Color();
}

void ConfigureColorWidget::selectClicked()
{
    foreach(QTreeWidgetItem* item, ui->availableColorsWidget->selectedItems()) {
        ui->availableColorsWidget->takeTopLevelItem(ui->availableColorsWidget->indexOfTopLevelItem(item));
        ui->selectedColorsWidget->addTopLevelItem(item);
    }
}

void ConfigureColorWidget::deselectClicked()
{
    foreach(QTreeWidgetItem* item, ui->selectedColorsWidget->selectedItems()) {
        ui->selectedColorsWidget->takeTopLevelItem(ui->selectedColorsWidget->indexOfTopLevelItem(item));
        ui->availableColorsWidget->addTopLevelItem(item);
    }
}

void ConfigureColorWidget::initAvailableColors()
{
    foreach (Color c, _availableColors) {
        ui->availableColorsWidget->addTopLevelItem(new ColorItem(c));
    }
}
