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

#ifndef CONFIGURECOLORWIDGET_H
#define CONFIGURECOLORWIDGET_H

#include <QWidget>
#include "color.h"
#include <vector>
#include <QLabel>
#include <QModelIndex>
#include <QList>

class QTreeWidgetItem;

namespace Ui {
class ConfigureColorWidget;
}

class ConfigureColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureColorWidget(bool enableLabel = true, QWidget *parent = 0);
    ~ConfigureColorWidget();

    void init(const std::vector<Color>& colors, QString& label);
    bool validate();
    QString validationError();

    QString colorLabel();
    std::vector<Color> selectedColors();

    void saveColorsToSettings();

private slots:
    void addColorClicked();
    void editColorClicked();
    void removeColorClicked();
    void resetColorsClicked();

    void selectColor(QModelIndex index);

private:
    Ui::ConfigureColorWidget *ui;

    QList<QVariant> defaultColors();
    void initColorsView();
    void updateSelectedColorsView();

    void addColorToList(QList<QVariant>& list, Color c);
};

#endif // CONFIGURECOLORWIDGET_H
