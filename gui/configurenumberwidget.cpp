#include "configurenumberwidget.h"
#include "ui_configurenumberwidget.h"
#include <limits>

ConfigureNumberWidget::ConfigureNumberWidget(bool enableLabel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureNumberWidget)
{
    ui->setupUi(this);

    ui->minSpin->setMinimum(INT_MIN);
    ui->minSpin->setMaximum(INT_MAX);
    ui->minSpin->setValue(1);

    ui->maxSpin->setMinimum(INT_MIN);
    ui->maxSpin->setMaximum(INT_MAX);
    ui->maxSpin->setValue(10);

    if (!enableLabel) {
        ui->useLabel->hide();
        ui->labelEdit->hide();
    }
}

ConfigureNumberWidget::~ConfigureNumberWidget()
{
    delete ui;
}

void ConfigureNumberWidget::init(int min, int max, QString label)
{
    ui->minSpin->setValue(min);
    ui->maxSpin->setValue(max);
    ui->labelEdit->setText(label);
}

bool ConfigureNumberWidget::validate() const
{
    return min() <= max();
}

QString ConfigureNumberWidget::validationError() const
{
    if (min() > max()) {
        return tr("Minimum value is larger than maximum value.");
    } else {
        return QString();
    }
}

int ConfigureNumberWidget::min() const
{
    return ui->minSpin->value();
}

int ConfigureNumberWidget::max() const
{
    return ui->maxSpin->value();
}

QString ConfigureNumberWidget::label() const
{
    return ui->labelEdit->text();
}
