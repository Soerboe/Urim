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

#include "colorandnumberview_border.h"
#include "ui_colorandnumberview_border.h"
#include "numberlotelement.h"
#include "colorlotelement.h"

ColorAndNumberView_Border::ColorAndNumberView_Border(QWidget *parent) :
    LotView(parent),
    ui(new Ui::ColorAndNumberView_Border),
    _drawn(false),
    _borderColor(),
    _borderThickness(1)
{
    ui->setupUi(this);
}

ColorAndNumberView_Border::~ColorAndNumberView_Border()
{
    delete ui;
}

void ColorAndNumberView_Border::view(const NumberLotElement& numberLotElement, int id)
{
    ignore_unused(id);

    ui->numberView->setText(QString::number(numberLotElement.number()));
    calcViewSize();
    _drawn = true;
}

void ColorAndNumberView_Border::view(const ColorLotElement& colorLotElement, int id)
{
    ignore_unused(id);

    _borderColor = colorLotElement.color();
    ui->colorNameView->setText(_borderColor.name);
    ui->mainView->setStyleSheet(buildStyleSheet());
    calcViewSize();
    _drawn = true;
}

void ColorAndNumberView_Border::calcViewSize()
{
    _borderThickness = qMax(5.0, ui->mainView->width() * ui->mainView->height() * 0.00005);
    if (_drawn) {
        ui->mainView->setStyleSheet(buildStyleSheet());
    }

    QRect numberRect = ui->numberView->rect();
    numberRect.adjust(0, 0, -(_borderThickness * 2), -_borderThickness);
    int numberSize = calcMaxFontSize(ui->numberView->font(), ui->numberView->text(), numberRect);

    QRect colorRect = ui->colorNameView->rect();
    colorRect.adjust(0, 0, -(_borderThickness * 2), -_borderThickness);
    int colorSize = calcMaxFontSize(ui->colorNameView->font(), ui->colorNameView->text(), colorRect);

    int fontSize = qMin(numberSize, colorSize);
    if (fontSize > 0) {
        QFont f = font();
        f.setPointSize(fontSize);
        ui->numberView->setFont(f);
        ui->colorNameView->setFont(f);
    }
}

void ColorAndNumberView_Border::showLot(bool visible)
{
    ui->mainView->setVisible(visible);
    calcViewSize();
}

QString ColorAndNumberView_Border::buildStyleSheet()
{
    QString s("#mainView {border:");
    // if color is white
    if (_borderColor.red == 255 && _borderColor.green == 255 && _borderColor.blue == 255) {
        s.append("1px solid black;}");
    } else {
        s.append(QString::number(_borderThickness)).append("px ");
        s.append("solid rgb(");
        s.append(QString::number(_borderColor.red)).append(",");
        s.append(QString::number(_borderColor.green)).append(",");
        s.append(QString::number(_borderColor.blue)).append(");}");
    }
    return s;
}
