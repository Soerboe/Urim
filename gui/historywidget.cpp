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

#include "historywidget.h"
#include "ui_historywidget.h"
#include "guiutils.h"
#include <QResizeEvent>
#include "lotview.h"
#include "guiutils.h"
#include <QScrollBar>
#include <QLabel>

#define ASPECT_RATIO (10.0 / 16.0)

HistoryWidget::HistoryWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    QPalette p =  ui->scrollAreaWidgetContents->palette();
    p.setColor(backgroundRole(), GuiUtils::backgroundColor());
    ui->scrollAreaWidgetContents->setPalette(p);

    ui->viewsLayout->setAlignment(Qt::AlignTop);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::addItem(LotView *lotView)
{
    lotView->setFixedHeight(lotViewHeight());

    QHBoxLayout* layout = new QHBoxLayout();
    int index = ui->viewsLayout->count() + 1;
    QLabel* label = new QLabel(QString("%1.").arg(index));
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    QFont f = label->font();
    f.setPointSize(12);
    label->setFont(f);
    layout->addWidget(label);
    layout->addWidget(lotView);
    ui->viewsLayout->insertLayout(0, layout);

    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void HistoryWidget::clear()
{
    GuiUtils::clearLayout(ui->viewsLayout);
}

void HistoryWidget::updateLotViews()
{
    int height = lotViewHeight();

    for (int i = 0; i < ui->viewsLayout->count(); ++i) {
        QWidget* w = ui->viewsLayout->itemAt(i)->layout()->itemAt(1)->widget();
        w->setFixedHeight(height);
    }
}

void HistoryWidget::showEvent(QShowEvent *)
{
    updateLotViews();
}

void HistoryWidget::resizeEvent(QResizeEvent *event)
{
    updateLotViews();
    event->accept();
}

int HistoryWidget::lotViewHeight()
{
    int w = this->width() - 20;  // width minus margins (mas o menos)
    return w * ASPECT_RATIO;
}
