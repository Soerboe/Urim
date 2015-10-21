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
    std::vector<Color> colors();

private slots:
    void selectClicked();
    void deselectClicked();

private:
    std::vector<Color> _availableColors;

    Ui::ConfigureColorWidget *ui;

    void initAvailableColors();
};

#endif // CONFIGURECOLORWIDGET_H
