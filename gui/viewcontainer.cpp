#include "viewcontainer.h"
#include "ui_viewcontainer.h"
#include <QLayoutItem>
#include "lotview.h"

ViewContainer::ViewContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewContainer)
{
    ui->setupUi(this);
}

ViewContainer::~ViewContainer()
{
    delete ui;
}

void ViewContainer::setLotView(LotView *view)
{
    clear();
    ui->lotViewLayout->addWidget(view);
    _lotView = view;
}

void ViewContainer::clear()
{
    QLayoutItem* oldView = ui->lotViewLayout->takeAt(0);
    if (oldView) {
        delete oldView->widget();
        delete oldView;
    }
}
