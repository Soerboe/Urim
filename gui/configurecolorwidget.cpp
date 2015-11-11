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
#include "colors.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <settingshandler.h>

using namespace std;

class ColorItem : public QTreeWidgetItem
{
public:
    ColorItem(const Color& color)
        : _color(color),
          _selected(false)
    {
        update();
    }

    Color color() {
        return _color;
    }

    void setColor(Color c) {
        _color = c;
        update();
    }

    void toggleSelection() {
        _selected = !_selected;

        setText(0, (_selected) ? "✔" : "");
    }

    bool selected() {
        return _selected;
    }

private:
    Color _color;
    bool _selected;

    void update() {
        setBackgroundColor(1, QColor(_color.red, _color.green, _color.blue));
        setText(2, _color.name);
    }
};

ConfigureColorWidget::ConfigureColorWidget(bool enableLabel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureColorWidget)
{
    ui->setupUi(this);
    ui->colorsWidget->setColumnCount(3);
    ui->colorsWidget->setColumnWidth(0, 20);
    ui->colorsWidget->setColumnWidth(1, 50);
    ui->colorsWidget->sortByColumn(2, Qt::AscendingOrder);

    defaultColors();
    initColorsView();

    if (!enableLabel) {
        ui->useLabel->hide();
        ui->colorLabel->hide();
    }

    connect(ui->addColorButton, SIGNAL(clicked()), SLOT(addColorClicked()));
    connect(ui->colorsWidget, SIGNAL(clicked(QModelIndex)), SLOT(selectColor(QModelIndex)));
    connect(ui->editColorButton, SIGNAL(clicked()), SLOT(editColorClicked()));
    connect(ui->removeColorButton, SIGNAL(clicked()), SLOT(removeColorClicked()));
    connect(ui->resetColorsButton, SIGNAL(clicked()), SLOT(resetColorsClicked()));
}

ConfigureColorWidget::~ConfigureColorWidget()
{
    delete ui;
}

void ConfigureColorWidget::init(const vector<Color>& colors, QString& label)
{
    ui->colorLabel->setText(label);

    for (size_t i = 0 ; i < colors.size(); ++i) {
        for (int j = 0; j < ui->colorsWidget->topLevelItemCount(); ++j) {
            ColorItem* item = dynamic_cast<ColorItem*> (ui->colorsWidget->topLevelItem(j));
            if (item && item->color() == colors[i]) {
                item->toggleSelection();
            }
        }
    }

    updateSelectedColorsView();
}

bool ConfigureColorWidget::validate()
{
    return !selectedColors().empty();
}

QString ConfigureColorWidget::validationError()
{
    if (selectedColors().empty()) {
        return tr("No colors selected.");
    } else {
        return QString();
    }
}

QString ConfigureColorWidget::colorLabel()
{
    return ui->colorLabel->text();
}

vector<Color> ConfigureColorWidget::selectedColors()
{
    vector<Color> c;
    for(int i = 0; i < ui->colorsWidget->topLevelItemCount(); ++i) {
        ColorItem* item = dynamic_cast<ColorItem*> (ui->colorsWidget->topLevelItem(i));
        if (item->selected()) {
            c.push_back(item->color());
        }
    }

    return c;
}

void ConfigureColorWidget::addColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::white, 0, tr("Choose color"));
    if (!color.isValid()) {
        return;
    }

    bool okClicked;
    QString colorName;
    while (true) {
        colorName = QInputDialog::getText(this, tr("Choose color name"), tr("Color name:"), QLineEdit::Normal, QString(), &okClicked);
        if (!okClicked) {
            return;
        } else if (colorName.isEmpty()) {
            QMessageBox::information(this, tr("No color name"), tr("No color name given"));
        } else {
            break;
        }
    }

    Color newColor(color.red(), color.green(), color.blue(), colorName);
    ui->colorsWidget->addTopLevelItem(new ColorItem(newColor));
}

void ConfigureColorWidget::editColorClicked()
{
    for (QTreeWidgetItem* item : ui->colorsWidget->selectedItems()) {
        ColorItem* colorItem = dynamic_cast<ColorItem*> (item);
        Color color = colorItem->color();

        QColor newColor = QColorDialog::getColor(QColor(color.red, color.green, color.blue), 0, tr("Choose new color"));
        if (!newColor.isValid()) {
            continue;
        }

        bool okClicked;
        QString colorName = color.name;
        while (true) {
            colorName = QInputDialog::getText(this, tr("Choose new color name"), tr("New color name:"), QLineEdit::Normal, colorName, &okClicked);
            if (!okClicked) {
                return;
            } else if (colorName.isEmpty()) {
                QMessageBox::information(this, tr("No color name"), tr("No color name given"));
            } else {
                break;
            }
        }

        colorItem->setColor(Color(newColor.red(), newColor.green(), newColor.blue(), colorName));
    }

    updateSelectedColorsView();
}

void ConfigureColorWidget::removeColorClicked()
{
    for (QTreeWidgetItem* item : ui->colorsWidget->selectedItems()) {
        ui->colorsWidget->takeTopLevelItem(ui->colorsWidget->indexOfTopLevelItem(item));
        delete item;
    }

    updateSelectedColorsView();
}

void ConfigureColorWidget::resetColorsClicked()
{
    QMessageBox box(QMessageBox::Question,
                    tr("Reset colors to default"),
                    tr("Are you sure you would like to reset colors to default?<br>This will remove all custom changes."),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
    box.setButtonText(QMessageBox::Yes, tr("Yes"));
    box.setButtonText(QMessageBox::No, tr("No"));
    if (box.exec() == QMessageBox::No) {
        return;
    }

    SettingsHandler::removeValue(SETTING_COLORS);
    initColorsView();

    updateSelectedColorsView();
    saveColorsToSettings();
}

void ConfigureColorWidget::saveColorsToSettings()
{
    QList<QVariant> colors;

    for (int i = 0; i < ui->colorsWidget->topLevelItemCount(); ++i) {
        ColorItem* item = dynamic_cast<ColorItem*> (ui->colorsWidget->topLevelItem(i));
        addColorToList(colors, item->color());
    }

    SettingsHandler::setValue(SETTING_COLORS, colors);
}

void ConfigureColorWidget::selectColor(QModelIndex index)
{
    ColorItem* item = dynamic_cast<ColorItem*> (ui->colorsWidget->topLevelItem(index.row()));

    if (!item || index.column() > 0) {
        return;
    }

    item->toggleSelection();
    updateSelectedColorsView();
}

QList<QVariant> ConfigureColorWidget::defaultColors()
{
    Colors colors;

    QList<QVariant> defaultColors;
    addColorToList(defaultColors, colors.red());
    addColorToList(defaultColors, colors.green());
    addColorToList(defaultColors, colors.blue());
    addColorToList(defaultColors, colors.yellow());
    addColorToList(defaultColors, colors.white());
    addColorToList(defaultColors, colors.black());
    addColorToList(defaultColors, colors.grey());
    addColorToList(defaultColors, colors.darkRed());
    addColorToList(defaultColors, colors.darkBlue());
    addColorToList(defaultColors, colors.darkGreen());
    addColorToList(defaultColors, colors.pink());
    addColorToList(defaultColors, colors.purple());
    addColorToList(defaultColors, colors.orange());
    addColorToList(defaultColors, colors.brown());
    addColorToList(defaultColors, colors.violet());
    addColorToList(defaultColors, colors.turquoise());
    addColorToList(defaultColors, colors.olive());
    addColorToList(defaultColors, colors.lightBrown());
    return defaultColors;
}

void ConfigureColorWidget::initColorsView()
{
    QList<QVariant> colors;

    if (SettingsHandler::has(SETTING_COLORS)) {
        colors = SettingsHandler::value(SETTING_COLORS).toList();
    } else {
        colors = defaultColors();
    }

    ui->colorsWidget->clear();

    for (QVariant color : colors) {
        ui->colorsWidget->addTopLevelItem(new ColorItem(color.value<Color>()));
    }
}

void ConfigureColorWidget::updateSelectedColorsView()
{
    ui->selectedColorsLabel->clear();
    QString text(tr("<strong>Selected colors:</strong> "));
    int i = 0;

    for(Color color : selectedColors()) {
        if (i++ != 0) {
            text.append(", ");
        }

        text.append(color.name);
    }

    ui->selectedColorsLabel->setText(text);
}

void ConfigureColorWidget::addColorToList(QList<QVariant> &list, Color c)
{
    QVariant v;
    v.setValue(c);
    list.append(v);
}
