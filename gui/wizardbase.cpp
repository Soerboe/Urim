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

#include "wizardbase.h"
#include "ui_wizardbase.h"
#include "wizardpage.h"
#include <QMessageBox>
#include "configureuniqueresultswidget.h"
#include "drawingconfiguration.h"

class SummaryPage : public WizardPage
{
    Q_OBJECT
public:
    SummaryPage(std::shared_ptr<Configuration> config)
        : _config(config)
    {
        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin(0);
        l->setAlignment(Qt::AlignTop);

        QLabel* heading = new QLabel(tr("Summary of you choices"));
        QFont f = heading->font();
        f.setPointSize(12);
        heading->setFont(f);
        l->addWidget(heading);

        _summary = new QLabel;
        f.setPointSize(10);
        _summary->setFont(f);
        _summary->setWordWrap(true);
        l->addWidget(_summary);

        setLayout(l);
    }

    void showEvent(QShowEvent*)
    {
        _summary->setText(_config->summary());
    }

    bool isValid()
    {
        return true;
    }

    QString validationError()
    {
        return QString();
    }

private:
    QLabel* _summary;
    std::shared_ptr<Configuration> _config;
};

#include "wizardbase.moc"

WizardBase::WizardBase(std::shared_ptr<Configuration> config, bool hasAdvancedSetup, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WizardBase),
      _config(config),
      _hasAdvancedSetup(hasAdvancedSetup)
{
    ui->setupUi(this);
    ui->advancedButton->setVisible(_hasAdvancedSetup);
    ui->createButton->setVisible(false);
    ui->configurationName->setText(_config->name());
    ui->iconView->setPixmap(_config->icon().pixmap(35, 35));

    ui->contentsWidget->addWidget(new SummaryPage(_config));

    connect(ui->backButton, &QPushButton::clicked, this, backButtonClicked);
    connect(ui->nextButton, &QPushButton::clicked, [&]() {
        ui->contentsWidget->setCurrentIndex(ui->contentsWidget->currentIndex() + 1);
    });
    connect(ui->createButton, &QPushButton::clicked, this, createButtonClicked);
    connect(ui->contentsWidget, &QStackedWidget::currentChanged, this, currentPageChanged);
    connect(ui->advancedButton, &QPushButton::clicked, this, advancedSetup);
}

WizardBase::~WizardBase()
{
    delete ui;
}

int WizardBase::addPage(WizardPage *page)
{
    connect(page, &WizardPage::changed, [page, this](bool valid) {
        handleValidity(valid, page->validationError());
    });

    // works because the summary page is added first
    int index = ui->contentsWidget->insertWidget(ui->contentsWidget->count() - 1, page);
    ui->contentsWidget->setCurrentIndex(0);
    return index;
}

void WizardBase::showEvent(QShowEvent *)
{
    ui->nextButton->setFocus();
}

void WizardBase::handleValidity(bool valid, const QString &error)
{
    ui->nextButton->setEnabled(valid);
    ui->errorLabel->setText(error);
}

void WizardBase::backButtonClicked()
{
    int curr = ui->contentsWidget->currentIndex();
    if (curr > 0) {
        ui->contentsWidget->setCurrentIndex(curr-1);
    } else {
        emit canceled();
    }
}

void WizardBase::createButtonClicked()
{
    if (_config->isValid()) {
        emit done(_config);
    } else {
        // should never get here
        QMessageBox::critical(this, tr("Invalid configuration"), tr("The drawing configuration is invalid. Please go back to correct the error."));
    }
}

void WizardBase::currentPageChanged()
{
    WizardPage* page = qobject_cast<WizardPage*> (ui->contentsWidget->currentWidget());
    handleValidity(page->isValid(), page->validationError());

    bool summaryPage = ui->contentsWidget->currentIndex() == ui->contentsWidget->count() - 1;
    ui->createButton->setVisible(summaryPage);
    ui->nextButton->setVisible(!summaryPage);
    ui->advancedButton->setVisible(_hasAdvancedSetup && !summaryPage);
    ui->nextButton->setFocus();
    ui->createButton->setFocus();
}

/*
 * UniqueResultsConfigPage
 */
UniqueResultsConfigPage::UniqueResultsConfigPage(std::shared_ptr<DrawingConfiguration> config)
    : _uniqueWidget(new ConfigureUniqueResultsWidget()),
      _config(config)
{
    QVBoxLayout* l = new QVBoxLayout;
    l->setMargin(0);
    l->addWidget(_uniqueWidget);
    l->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(l);
    setFieldsFromConfig();
    connect(_uniqueWidget, &ConfigureUniqueResultsWidget::changed, this, updateFields);
}

void UniqueResultsConfigPage::setFieldsFromConfig()
{
    _uniqueWidget->init(_config->uniqueResults());
}

void UniqueResultsConfigPage::updateFields()
{
    _config->setUniqueResults(_uniqueWidget->uniqueResults());
    emit changed(isValid());
}
