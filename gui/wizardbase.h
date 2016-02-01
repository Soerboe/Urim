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

#ifndef WIZARDBASE_H
#define WIZARDBASE_H

#include <QWidget>
#include <memory>
#include "configuration.h"
#include "wizardpage.h"

class DrawingConfiguration;
class ConfigureUniqueResultsWidget;

namespace Ui {
class WizardBase;
}

class WizardBase : public QWidget
{
    Q_OBJECT

public:
    explicit WizardBase(std::shared_ptr<Configuration> config, bool hasAdvancedSetup, QWidget *parent = 0);
    ~WizardBase();

signals:
    void done(std::shared_ptr<Configuration> config);
    void canceled();

protected:
    // override in subclasses with advanced setup
    virtual void advancedSetup() {}
    int addPage(WizardPage* page);
    void showEvent(QShowEvent*);

private:
    Ui::WizardBase *ui;
    std::shared_ptr<Configuration> _config;
    bool _hasAdvancedSetup;
    void handleValidity(bool valid, const QString& error);

    void backButtonClicked();
    void createButtonClicked();
    void currentPageChanged();
};

class UniqueResultsConfigPage : public WizardPage
{
public:
    UniqueResultsConfigPage(std::shared_ptr<DrawingConfiguration> config);


    void setFieldsFromConfig();

    void updateFields();

    bool isValid() {return true;}

    QString validationError() {return "";}

private:
    ConfigureUniqueResultsWidget* _uniqueWidget;
    std::shared_ptr<DrawingConfiguration> _config;
};

#endif // WIZARDBASE_H
