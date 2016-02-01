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

#ifndef EDITCOLORSWIDGET_H
#define EDITCOLORSWIDGET_H

#include <QWidget>

class QTreeWidgetItem;

namespace Ui {
class EditColorsWidget;
}

class EditColorsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditColorsWidget(QWidget *parent = 0);
    ~EditColorsWidget();

    void saveColorsToSettings();

private slots:
    void addColorClicked();
    void editColorClicked();
    void removeColorClicked();
    void resetColorsClicked();
    void selectionChanged();

private:
    Ui::EditColorsWidget *ui;

    void initColorsView();
};

#endif // EDITCOLORSWIDGET_H
