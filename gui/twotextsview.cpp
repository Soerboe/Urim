#include "twotextsview.h"
#include "ui_twonumbersview.h"
#include "guiutils.h"

TwoTextsView::TwoTextsView(QWidget *parent) :
    LotView(parent),
    ui(new Ui::TwoTextsView),
    _initialized(false),
    _showBorder(false),
    _borderWidth(0)
{
    ui->setupUi(this);
}

TwoTextsView::~TwoTextsView()
{
    delete ui;
}

void TwoTextsView::setTopText(QString text)
{
    ui->topView->setText(text);
    initialize();
    calcViewSize();
}

void TwoTextsView::setBottomText(QString text)
{
    ui->bottomView->setText(text);
    initialize();
    calcViewSize();
}

void TwoTextsView::calcViewSize()
{
    if (_showBorder && _initialized) {
        _borderWidth = qMax(5.0, ui->mainView->width() * ui->mainView->height() * 0.00005);
        updateBorder();
    }

    QRect bottomRect = ui->bottomView->rect();
    bottomRect.adjust(0, 0, -(_borderWidth * 2), -_borderWidth);
    int bottomSize = calcMaxFontSize(ui->bottomView->font(), ui->bottomView->text(), bottomRect);

    QRect topRect = ui->topView->rect();
    topRect.adjust(0, 0, -(_borderWidth * 2), -_borderWidth);
    int topSize = calcMaxFontSize(ui->topView->font(), ui->topView->text(), topRect);

    int fontSize = qMin(bottomSize, topSize);
    if (fontSize > 0) {
        QFont f = font();
        f.setPointSize(fontSize);
        ui->topView->setFont(f);
        ui->bottomView->setFont(f);
    }
}

void TwoTextsView::setBorderColor(Color color)
{
    _borderColor = color;
    updateBorder();
}

void TwoTextsView::updateBorder()
{
    QString style("#mainView {border:");
    // if color is white
    if (_borderColor.red == 255 && _borderColor.green == 255 && _borderColor.blue == 255) {
        style.append("1px solid black;}");
    } else {
        style.append(QString::number(_borderWidth)).append("px ");
        style.append("solid rgb(");
        style.append(QString::number(_borderColor.red)).append(",");
        style.append(QString::number(_borderColor.green)).append(",");
        style.append(QString::number(_borderColor.blue)).append(");}");
    }

    ui->mainView->setStyleSheet(style);
}

void TwoTextsView::showLot(bool visible)
{
    ui->mainView->setVisible(visible);
    calcViewSize();
}
