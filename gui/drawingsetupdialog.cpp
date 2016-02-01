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

#include "drawingsetupdialog.h"
#include "ui_drawingsetupdialog.h"
#include <QMessageBox>
#include <QSvgWidget>
#include "wizardbase.h"
#include <QCommandLinkButton>
#include <QDesktopWidget>
#include "configurecolorwidget.h"

using namespace std;

DrawingSetupDialog::DrawingSetupDialog(DrawingSetupController* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawingSetupDialog),
    _controller(controller)
{
    ui->setupUi(this);
    setWindowTitle(tr("Setup drawing"));
    ui->headingLabel->setText(qApp->applicationName());

    QSvgWidget* svg = new QSvgWidget(":/gui/icons/lots.svg");
    svg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    svg->setFixedSize(64, 64);
    ui->headerLayout->insertWidget(0, svg);

    QString style("border-bottom: 2px dotted #C0C0C0;");
    ui->header->setStyleSheet(style);
    ui->indexPageLayout->setAlignment(Qt::AlignTop);
    setupConfigurations();
}

DrawingSetupDialog::~DrawingSetupDialog()
{
    delete ui;
}

shared_ptr<DrawingSession> DrawingSetupDialog::getDrawingSession()
{
    return _selectedConfiguration->createDrawingSession();
}

LotView* DrawingSetupDialog::getView()
{
    return _selectedConfiguration->createView();
}

void DrawingSetupDialog::resetWizards()
{
    ui->wizardWidget->setCurrentIndex(0);
}

void DrawingSetupDialog::setupConfigurations()
{
    for(int i = 0; i < _controller->configurationsCount(); ++i) {
        shared_ptr<Configuration> config = _controller->at(i);
        QCommandLinkButton* btn = new QCommandLinkButton(config->name(), config->description());
        btn->setStyleSheet("color: black;");
        btn->setIcon(config->icon());
        btn->setIconSize(QSize(35, 35));
        QFont f = btn->font();
        f.setPointSize(10);
        btn->setFont(f);
        btn->setCursor(Qt::PointingHandCursor);
        connect(btn, &QCommandLinkButton::clicked, [i, this]() {
            shared_ptr<Configuration> config = _controller->at(i);
            if (config->configurable()) {
                startWizard(config->wizard());
            } else {
                _selectedConfiguration = config;
                accept();
            }
        });

        ui->indexPageLayout->addWidget(btn);
    }
}

void DrawingSetupDialog::startWizard(WizardBase* wizard)
{
    connect(wizard, SIGNAL(canceled()), SLOT(resetWizards()));
    connect(wizard, &WizardBase::done, [&](shared_ptr<Configuration> config) {
        _selectedConfiguration = config;
        resetWizards();
        accept();
    });

    if (ui->wizardWidget->widget(1) != 0) {
        delete ui->wizardWidget->widget(1);
    }

    ui->wizardWidget->insertWidget(1, wizard);
    ui->wizardWidget->setCurrentIndex(1);
}
