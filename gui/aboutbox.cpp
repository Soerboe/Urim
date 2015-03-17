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

#include "aboutbox.h"
#include "ui_aboutbox.h"
#include <QSvgWidget>
#include "urimthummim.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);

    QSvgWidget* svg = new QSvgWidget(":/gui/icons/lots.svg");
    svg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    svg->setFixedSize(128, 128);
    ui->iconLayout->insertWidget(0, svg);

    QString mainInfo;
    mainInfo.append("<html><head/><body>")
            .append("<p><span style=\"font-size:20pt;\">").append(APPLICATION_NAME).append("</span></p>")
            .append("<p><span style=\"font-size:14pt;\">").append(tr("Version")).append(" ").append(APPLICATION_VERSION).append("</span></p>")
            .append("</body></html>");
    ui->mainInfo->setText(mainInfo);

    QString extraInfo;
    extraInfo.append("<html><head/><body><span style=\"font-size:9pt;\"><br/>")
             .append("<p>Copyright (C) Dag Henning Liodden Sørbø - daghenning@lioddensorbo.com</p>")
             .append(tr("<p>This program is free software: you can redistribute it and/or modify<br/>\
                        it under the terms of the GNU General Public License version 2 as<br/>\
                        published by the Free Software Foundation. See http://www.gnu.org/licenses/.</p>"))
             .append("</span></body></html>");
    ui->extraInfo->setText(extraInfo);

    setWindowTitle(tr("About %1").arg(APPLICATION_NAME));
    adjustSize();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

AboutBox::~AboutBox()
{
    delete ui;
}
