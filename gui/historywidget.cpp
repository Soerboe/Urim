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

    QString style("#HistoryWidget, #spacer1, #spacer2 {background-color: #F0F0F0;}");
    style.append("#heading {border-bottom: 1px solid #606060; background-color: #F0F0F0; color: #606060}");
    setStyleSheet(style);

    ui->verticalLayout->setAlignment(Qt::AlignTop);
    ui->viewsLayout->setAlignment(Qt::AlignTop);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::addItem(LotView *lotView)
{
    lotView->setFixedHeight(lotViewHeight());
    ui->viewsLayout->insertWidget(0, lotView);
    ui->scrollArea->verticalScrollBar()->setValue(0);
    updateLotViews();
}

void HistoryWidget::clear()
{
    GuiUtils::clearLayout(ui->viewsLayout);
}

void HistoryWidget::updateLotViews()
{
    int height = lotViewHeight();

    for (int i = 0; i < ui->viewsLayout->count(); ++i) {
        QWidget* w = ui->viewsLayout->itemAt(i)->widget();
        w->setFixedHeight(height);
    }
}

void HistoryWidget::updateHeaderFont()
{
    int fontSize = GuiUtils::calcMaxFontSize(ui->heading->font(), ui->heading->text(), ui->heading->rect());
    QFont f = ui->heading->font();
    f.setPointSize(fontSize * 0.7);
    ui->heading->setFont(f);
}

void HistoryWidget::showEvent(QShowEvent *)
{
    updateLotViews();
    updateHeaderFont();
}

void HistoryWidget::resizeEvent(QResizeEvent *event)
{
    updateLotViews();
    updateHeaderFont();
    event->accept();
}

int HistoryWidget::lotViewHeight()
{
    int w = this->width() - 20;  // width minus margins (mas o menos)
    return w * ASPECT_RATIO;
}
