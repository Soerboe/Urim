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

#include "singlenumberwizard.h"
#include "wizardpage.h"
#include <QVBoxLayout>
#include "configurenumberwidget.h"
#include "singlenumberconfiguration.h"

class NumberConfigPage : public WizardPage
{
public:
    NumberConfigPage(std::shared_ptr<SingleNumberConfiguration> config)
        : _numberWidget(new ConfigureNumberWidget(false)),
          _config(config)
    {
        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin(0);
        l->addWidget(_numberWidget);
        l->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        setLayout(l);
        setFieldsFromConfig();
        connect(_numberWidget, &ConfigureNumberWidget::changed, this, updateFields);
    }

    void setFieldsFromConfig() {
        _numberWidget->init(_config->min(), _config->max(), _config->label());
    }

    void updateFields() {
        _config->setMin(_numberWidget->min());
        _config->setMax(_numberWidget->max());
        _config->setLabel(_numberWidget->label());
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
    std::shared_ptr<SingleNumberConfiguration> _config;
};

SingleNumberWizard::SingleNumberWizard(std::shared_ptr<SingleNumberConfiguration> config)
    : WizardBase(config, false),
      _config(config)
{
    _numberConfigPage = new NumberConfigPage(_config);
    _uniqueResultsConfigPage = new UniqueResultsConfigPage(_config);
    addPage(_numberConfigPage);
    addPage(_uniqueResultsConfigPage);
}
