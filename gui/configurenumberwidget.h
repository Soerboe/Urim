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


#ifndef CONFIGURENUMBERWIDGET_H
#define CONFIGURENUMBERWIDGET_H

#include <QWidget>

namespace Ui {
class ConfigureNumberWidget;
}

class ConfigureNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureNumberWidget(bool enableLabel = true, QWidget *parent = 0);
    ~ConfigureNumberWidget();

    void init(int min, int max, QString label);
    bool validate() const;
    QString validationError() const;
    int min() const;
    int max() const;
    QString label() const;

signals:
    void changed(bool valid);

private slots:
    void handleFieldChanged();

private:
    Ui::ConfigureNumberWidget *ui;
};

#endif // CONFIGURENUMBERWIDGET_H
