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

#include "colorandnumberview_pog.h"
#include "ui_colorandnumberview_pog.h"
#include "utils.h"
#include "color.h"
#include "numberlotelement.h"
#include "colorlotelement.h"

ColorAndNumberView_POG::ColorAndNumberView_POG(const QString& longestText, QWidget *parent) :
    LotViewTextAsMain(longestText, parent),
    ui(new Ui::ColorAndNumberView_POG),
    _init(false)
{
    ui->setupUi(this);
    ui->colorView->setAutoFillBackground(true);
    ui->colorView->raise();
}

ColorAndNumberView_POG::~ColorAndNumberView_POG()
{
    delete ui;
}

void ColorAndNumberView_POG::updateView()
{
    if (!_init) {
        return;
    }

    ui->numberView->setText(QString::number(_number));

    QPalette palette = ui->colorView->palette();
    palette.setColor(backgroundRole(), QColor(_color.red, _color.green, _color.blue));
    ui->colorView->setPalette(palette);
    ui->colorNameView->setText(_color.name);

    calcViewSize();
}

void ColorAndNumberView_POG::view(const NumberLotElement& numberLotElement, int id)
{
    ignore_unused(id);

    _number = numberLotElement.number();
    _init = true;
    updateView();
}

void ColorAndNumberView_POG::view(const ColorLotElement& colorLotElement, int id)
{
    ignore_unused(id);

    _color = colorLotElement.color();
    _init = true;
    updateView();
}

void ColorAndNumberView_POG::calcViewSize()
{
    QFont f = ui->numberView->font();

    int fontSize = calcMaxFontSize(f, _longestText, ui->numberView->rect());
    if (fontSize <= 0) {
        return;
    }

    f.setPointSize(fontSize);
    ui->numberView->setFont(f);

    ui->colorView->setFixedWidth(ui->mainView->width() * 0.15);
    ui->colorView->setFixedHeight(ui->colorNameView->height() + ui->numberView->height());

    calcLocalFontSize(f);
}

void ColorAndNumberView_POG::showLot(bool visible)
{
    ui->mainView->setVisible(visible);
    updateView();
}

void ColorAndNumberView_POG::calcLocalFontSize(const QFont& font)
{
    QFont f = font;
    QRect boundingBox = ui->numberView->rect();
    int size = f.pointSize() * 0.4;
    bool tooLarge = true;
    for (; tooLarge && size > 1; --size) {
        f.setPointSize(size);
        QFontMetrics fm(f);
        tooLarge = fm.width(ui->colorNameView->text()) >= boundingBox.width();
    }

    QFont newFont = ui->colorNameView->font();
    newFont.setPointSize(size);
    ui->colorNameView->setFont(newFont);
}
