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

#ifndef WIZARDPAGE
#define WIZARDPAGE

#include <QWidget>

class WizardPage : public QWidget
{
    Q_OBJECT

signals:
    void changed(bool valid);

public:
    virtual QString validationError() = 0;
    virtual bool isValid() = 0;
};

#endif // WIZARDPAGE

