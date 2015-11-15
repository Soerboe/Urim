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

#ifndef CONFIGUREAMOUNTWIDGET_H
#define CONFIGUREAMOUNTWIDGET_H

#include <QWidget>

class QSpinBox;
class QLineEdit;

namespace Ui {
class ConfigureAmountWidget;
}

class ConfigureAmountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureAmountWidget(QString title, QWidget *parent = 0);
    ~ConfigureAmountWidget();

    void addAmountSelector(QString name, int initialValue, QString label, QString initialLabel);
    void init(int index, int value, QString label);
    int amount(int index) const;
    QString label(int index) const;

private:
    Ui::ConfigureAmountWidget *ui;

    QList<QSpinBox*> _spins;
    QList<QLineEdit*> _edits;
};

#endif // CONFIGUREAMOUNTWIDGET_H
