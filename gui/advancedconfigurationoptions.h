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

#ifndef ADVANCEDCONFIGURATIONOPTIONS_H
#define ADVANCEDCONFIGURATIONOPTIONS_H

#include <QDialog>

namespace Ui {
class AdvancedConfigurationOptions;
}

class AdvancedConfigurationOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedConfigurationOptions(const QString& title, QWidget* parent = 0);
    ~AdvancedConfigurationOptions();

protected:
    virtual bool validate() = 0;
    virtual QString validationError() = 0;
    Ui::AdvancedConfigurationOptions* ui;

    void hideSetupTab();
    void hideViewsTab();

private slots:
    void okClicked();
};

#endif // ADVANCEDCONFIGURATIONOPTIONS_H
