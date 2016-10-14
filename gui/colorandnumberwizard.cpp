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

#include "colorandnumberwizard.h"
#include "wizardpage.h"
#include <QVBoxLayout>
#include "configurenumberwidget.h"
#include "configureuniqueresultswidget.h"
#include "colorandnumberconfiguration.h"
#include "configurecolorwidget.h"
#include "advancedcolorandnumberoptions.h"

class NumberRangeConfigPage : public WizardPage
{
public:
    NumberRangeConfigPage(std::shared_ptr<ColorAndNumberConfiguration> config)
        : _numberWidget(new ConfigureNumberWidget(false)),
          _config(config)
    {
        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin(0);
        l->addWidget(_numberWidget);
        l->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        setLayout(l);
        setFieldsFromConfig();
        connect(_numberWidget, &ConfigureNumberWidget::changed, this, &NumberRangeConfigPage::updateFields);
    }

    void setFieldsFromConfig() {
        _numberWidget->init(_config->min(), _config->max(), _config->numberLabel());
    }

    void updateFields() {
        _config->setMin(_numberWidget->min());
        _config->setMax(_numberWidget->max());
        _config->setNumberLabel(_numberWidget->label());
        emit changed(isValid());
    }

    bool isValid() {
        return _numberWidget->validate();
    }

    QString validationError() {
        return _numberWidget->validationError();
    }

private:
    ConfigureNumberWidget* _numberWidget;
    std::shared_ptr<ColorAndNumberConfiguration> _config;
};

class ColorsConfigPage : public WizardPage
{
public:
    ColorsConfigPage(std::shared_ptr<ColorAndNumberConfiguration> config)
        : _colorWidget(new ConfigureColorWidget),
          _config(config)
    {
        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin(0);
        l->addWidget(_colorWidget);
        l->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        setLayout(l);
        setFieldsFromConfig();
        connect(_colorWidget, &ConfigureColorWidget::changed, this, &ColorsConfigPage::updateFields);
    }

    void setFieldsFromConfig() {
        _colorWidget->init(_config->colors());
    }

    void updateFields() {
        _config->setColors(_colorWidget->selectedColors());
        emit changed(isValid());
    }

    bool isValid() {
        return _colorWidget->validate();
    }

    QString validationError() {
        return _colorWidget->validationError();
    }

private:
    ConfigureColorWidget* _colorWidget;
    std::shared_ptr<ColorAndNumberConfiguration> _config;
};

ColorAndNumberWizard::ColorAndNumberWizard(std::shared_ptr<ColorAndNumberConfiguration> config)
    : WizardBase(config, true),
      _config(config)
{
    _numberConfigPage = new NumberRangeConfigPage(_config);
    _colorConfigPage = new ColorsConfigPage(_config);
    _uniqueResultsConfigPage = new UniqueResultsConfigPage(_config);
    addPage(_numberConfigPage);
    addPage(_colorConfigPage);
    addPage(_uniqueResultsConfigPage);
}

void ColorAndNumberWizard::advancedSetup()
{
    AdvancedColorAndNumberOptions dialog(_config->name());
    dialog.init(_config->viewIndex());

    if (dialog.exec() == QDialog::Accepted) {
        _config->setViewIndex(dialog.viewIndex());
    }
}

