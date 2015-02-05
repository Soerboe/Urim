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

#include "lotelementview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

LotElementView::LotElementView(QWidget *parent) :
    QFrame(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _layout = new QVBoxLayout(this);
    setLayout(_layout);
    _label = new QLabel;
    _label->setAlignment(Qt::AlignBaseline | Qt::AlignHCenter);
    _label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    _layout->addWidget(_label);
}

LotElementView::~LotElementView()
{
    delete _layout;
}

int LotElementView::calcMaxFontSize()
{
    QFont parentFont = parentWidget()->font();
    QFontMetrics parentMetrics(parentFont);
    QFont f = parentFont;
    int size = parentFont.pointSize();
    int inc = 1;
    bool fontTooLarge = parentMetrics.width(_longestResultText) >= subviewWidth() || parentMetrics.height() >= subviewHeight();

    for (int i = 1; i <= MAX_FONT_SIZE; i += inc) {
        // try to increase font size
        if (!fontTooLarge) {
            f.setPointSize(size + i);
            QFontMetrics fm(f);
            if (fm.width(_longestResultText) >= subviewWidth() || fm.height() >= subviewHeight()) {
                return size + i - inc;
            }
        }

        // try to decrease font size
        if (fontTooLarge) {
            f.setPointSize(size - i);
            QFontMetrics fm(f);
            if (fm.width(_longestResultText) < subviewWidth() && fm.height() < subviewHeight()) {
                return size - i;
            }
        }
    }

    return size; // should never get this far
}

void LotElementView::calcLocalFontSize(const QString& text)
{
    QFont f = parentWidget()->font();
    int size = f.pointSize() * 0.3;
    bool tooLarge = true;
    for (; tooLarge && size > 1; --size) {
        f.setPointSize(size);
        QFontMetrics fm(f);
        tooLarge = fm.width(text) >= subviewWidth() || fm.height() >= subviewHeight();
    }

    _label->setFont(f);
}

void LotElementView::setLabelText(const LotElement& lotElement)
{
    QString text(lotElement.name().c_str());
    if (!text.isEmpty()) {
        text.append(":");
    }
    _label->setText(text);
}
