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

#include "lotviewselector.h"
#include "ui_lotviewselector.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "lotview.h"

class LotViewSelectorContainer : public QFrame
{
public:
    LotViewSelectorContainer(LotView* lotview, QRadioButton* button)
        : _radioButton(button)
    {
        _layout = new QVBoxLayout();
        setLayout(_layout);
        setFrameShape(QFrame::Box);
        setFixedSize(200, 150);
        setCursor(Qt::PointingHandCursor);
        _layout->addWidget(lotview);
    }

    void mouseReleaseEvent(QMouseEvent *)
    {
        _radioButton->setChecked(true);
    }

private:
    QVBoxLayout* _layout;
    QRadioButton* _radioButton;
};

LotViewSelector::LotViewSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LotViewSelector)
{
    ui->setupUi(this);
    _radioGroup = new QButtonGroup();
}

LotViewSelector::~LotViewSelector()
{
    delete ui;
}

void LotViewSelector::init(int viewIndex)
{
    if (viewIndex >= 0 && viewIndex < _radioGroup->buttons().count()) {
        _radioGroup->button(viewIndex)->setChecked(true);
    }
}

void LotViewSelector::addView(LotView *lotView)
{
    int count = _radioGroup->buttons().size();
    QRadioButton* button = new QRadioButton();
    button->setText(" ");
    if (count == 0) {
        button->setChecked(true);
    }
    _radioGroup->addButton(button, count);
    ui->viewsLayout->addWidget(button, count, 0);

    lotView->showLot(true);
    ui->viewsLayout->addWidget(new LotViewSelectorContainer(lotView, button), count, 1);
}

int LotViewSelector::selectedViewIndex()
{
    return _radioGroup->checkedId();
}
