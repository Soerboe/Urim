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

#include "singlenumberview.h"
#include "ui_singlenumberview.h"
#include "numberlotelement.h"

SingleNumberView::SingleNumberView(const QString& longestText, QWidget *parent) :
    LotViewTextAsMain(longestText, parent),
    ui(new Ui::SingleNumberView)
{
    ui->setupUi(this);
}

SingleNumberView::~SingleNumberView()
{
    delete ui;
}

void SingleNumberView::view(const NumberLotElement& numberLotElement, int id)
{
    ignore_unused(id);

    if (numberLotElement.name().length() > 0) {
        ui->label->setText(QString(numberLotElement.name().c_str()).append(":"));
    }

    ui->numberView->setText(QString::number(numberLotElement.number()));

    calcLocalFontSize(ui->numberView->font());
}

void SingleNumberView::calcViewSize()
{
    QFont f = ui->numberView->font();

    int fontSize = calcMaxFontSize(f, _longestText, ui->numberView->rect());
    if (fontSize <= 0) {
        return;
    }

    f.setPointSize(fontSize);
    ui->numberView->setFont(f);

    calcLocalFontSize(f);
}

void SingleNumberView::calcLocalFontSize(const QFont& font)
{
    QFont f = font;
    QRect boundingBox = ui->numberView->rect();
    int size = f.pointSize() * 0.3;
    bool tooLarge = true;
    for (; tooLarge && size > 1; --size) {
        f.setPointSize(size);
        QFontMetrics fm(f);
        tooLarge = fm.width(ui->label->text()) >= boundingBox.width();
    }

    QFont labelFont = ui->label->font();
    labelFont.setPointSize(size);
    ui->label->setFont(labelFont);
}

