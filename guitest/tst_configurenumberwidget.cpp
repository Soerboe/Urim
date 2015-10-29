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
#include "configurenumberwidget.h"
#include <QSpinBox>

class ConfigureNumberWidgetTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:

void shouldValidateTrue()
{
    ConfigureNumberWidget widget;
    QSpinBox* min = widget.findChild<QSpinBox*>("minSpin");
    QSpinBox* max = widget.findChild<QSpinBox*>("maxSpin");
    min->setValue(1);
    max->setValue(2);

    QVERIFY(widget.validate());
}

void shouldValidateFalse()
{
    ConfigureNumberWidget widget;
    QSpinBox* min = widget.findChild<QSpinBox*>("minSpin");
    QSpinBox* max = widget.findChild<QSpinBox*>("maxSpin");
    min->setValue(2);
    max->setValue(1);

    QVERIFY(widget.validate() == false);
}

};

REGISTER_TEST(ConfigureNumberWidgetTest)

#include "tst_configurenumberwidget.moc"

