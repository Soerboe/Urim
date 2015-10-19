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

#include "loadingwidget.h"
#include "ui_loadingwidget.h"
#include <QLabel>
#include <QResizeEvent>

LoadingWidget::LoadingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingWidget),
    _movie(":/gui/icons/loader64.gif")
{
    ui->setupUi(this);

    QLabel* processLabel = new QLabel(this);
    processLabel->setAlignment(Qt::AlignCenter);
    ui->verticalLayout->insertWidget(0, processLabel);
    processLabel->setMovie(&_movie);
}

LoadingWidget::~LoadingWidget()
{
    delete ui;
}

void LoadingWidget::showEvent(QShowEvent*)
{
    _movie.start();
}

void LoadingWidget::hideEvent(QHideEvent*)
{
    _movie.stop();
}

void LoadingWidget::resizeEvent(QResizeEvent* event)
{
    int heightPercentile = event->size().height() * 0.3;
    int widthPercentile = event->size().width() * 0.3;

    if (heightPercentile > 256 && widthPercentile > 256) {
        _movie.setFileName(":/gui/icons/loader256.gif");
    } else if (heightPercentile > 128 && widthPercentile > 128) {
        _movie.setFileName(":/gui/icons/loader128.gif");
    } else if (heightPercentile > 64 && widthPercentile > 64) {
        _movie.setFileName(":/gui/icons/loader64.gif");
    } else {
        _movie.setFileName(":/gui/icons/loader32.gif");
    }
}
