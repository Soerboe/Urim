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

#include "editcolorswidget.h"
#include "ui_editcolorswidget.h"
#include <QTreeWidgetItem>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <settingshandler.h>

using namespace std;

class ColorItem : public QTreeWidgetItem
{
public:
    ColorItem(const Color& color)
        : _color(color)
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

private:
    Color _color;

    void update() {
        setBackgroundColor(0, QColor(_color.red(), _color.green(), _color.blue()));
        setText(1, _color.name());
    }
};

EditColorsWidget::EditColorsWidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::EditColorsWidget)
{
    ui->setupUi(this);
    ui->colorsWidget->setColumnCount(2);
    ui->colorsWidget->setColumnWidth(0, 50);

    initColorsView();

    connect(ui->addColorButton, SIGNAL(clicked()), SLOT(addColorClicked()));
    connect(ui->editColorButton, SIGNAL(clicked()), SLOT(editColorClicked()));
    connect(ui->removeColorButton, SIGNAL(clicked()), SLOT(removeColorClicked()));
    connect(ui->resetColorsButton, SIGNAL(clicked()), SLOT(resetColorsClicked()));
    connect(ui->colorsWidget, SIGNAL(itemSelectionChanged()), SLOT(selectionChanged()));
}

EditColorsWidget::~EditColorsWidget()
{
    delete ui;
}

void EditColorsWidget::addColorClicked()
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

void EditColorsWidget::editColorClicked()
{
    for (QTreeWidgetItem* item : ui->colorsWidget->selectedItems()) {
        ColorItem* colorItem = dynamic_cast<ColorItem*> (item);
        Color color = colorItem->color();

        QColor newColor = QColorDialog::getColor(QColor(color.red(), color.green(), color.blue()), 0, tr("Choose new color"));
        if (!newColor.isValid()) {
            continue;
        }

        bool okClicked;
        QString colorName = color.name();
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
}

void EditColorsWidget::removeColorClicked()
{
    for (QTreeWidgetItem* item : ui->colorsWidget->selectedItems()) {
        ui->colorsWidget->takeTopLevelItem(ui->colorsWidget->indexOfTopLevelItem(item));
        delete item;
    }
}

void EditColorsWidget::resetColorsClicked()
{
    QMessageBox box(QMessageBox::Question,
                    tr("Reset colors to default"),
                    tr("Are you sure you would like to reset colors to default?<br>This will remove all custom changes to the colors."),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
    box.setButtonText(QMessageBox::Yes, tr("Yes"));
    box.setButtonText(QMessageBox::No, tr("No"));
    if (box.exec() == QMessageBox::No) {
        return;
    }

    SettingsHandler::resetToDefaultColors();
    initColorsView();
}

void EditColorsWidget::selectionChanged()
{
    bool itemSelected = ui->colorsWidget->selectedItems().size() > 0;
    ui->editColorButton->setEnabled(itemSelected);
    ui->removeColorButton->setEnabled(itemSelected);
}

void EditColorsWidget::saveColorsToSettings()
{
    QList<Color> colors;

    for (int i = 0; i < ui->colorsWidget->topLevelItemCount(); ++i) {
        ColorItem* item = dynamic_cast<ColorItem*> (ui->colorsWidget->topLevelItem(i));
        colors.append(item->color());
    }

    SettingsHandler::setColors(colors);
}

void EditColorsWidget::initColorsView()
{
    QList<Color> colors = SettingsHandler::colors();
    ui->colorsWidget->clear();

    for (Color color : colors) {
        ui->colorsWidget->addTopLevelItem(new ColorItem(color));
    }
}
