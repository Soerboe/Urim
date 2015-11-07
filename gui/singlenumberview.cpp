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
#include "guiutils.h"

SingleNumberView::SingleNumberView(const QString& longestText, bool showLabel, QWidget *parent) :
    LotViewTextAsMain(longestText, parent),
    ui(new Ui::SingleNumberView),
    _showLabel(showLabel),
    _init(false)
{
    ui->setupUi(this);
    ui->label->setVisible(_showLabel);
}

SingleNumberView::~SingleNumberView()
{
    delete ui;
}

void SingleNumberView::view(const NumberLotElement& numberLotElement, int id)
{
    ignore_unused(id);

    _number = numberLotElement.number();
    _label = QString(numberLotElement.name().c_str());
    _init = true;
    updateView();
}

void SingleNumberView::calcViewSize()
{
    QFont f = ui->numberView->font();
    QRect rect = ui->mainView->rect();
    rect.setHeight(rect.height() - ui->label->height());

    int fontSize = GuiUtils::calcMaxFontSize(f, _longestText, rect);
    if (fontSize <= 0) {
        return;
    }

    f.setPointSize(fontSize);
    ui->numberView->setFont(f);

    calcLocalFontSize(f);
}

void SingleNumberView::showLot(bool visible)
{
    if (_showLabel) {
        ui->label->setVisible(visible);
    }
    ui->numberView->setVisible(visible);
    updateView();
}

void SingleNumberView::updateView()
{
    if (!_init) {
        return;
    }

    if (!_label.isEmpty()) {
        ui->label->setText(QString(_label).append(":"));
    }

    ui->numberView->setText(QString::number(_number));

    calcViewSize();
}

void SingleNumberView::calcLocalFontSize(const QFont& font)
{
    QFont f = font;
    QRect boundingBox = ui->mainView->rect();
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

