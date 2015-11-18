#include "twotextsview.h"
#include "ui_twotextsview.h"
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
    int bottomSize = GuiUtils::calcMaxFontSize(ui->bottomView->font(), ui->bottomView->text(), bottomRect);

    QRect topRect = ui->topView->rect();
    int topSize = GuiUtils::calcMaxFontSize(ui->topView->font(), ui->topView->text(), topRect);

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
    if (!_showBorder || !_initialized) {
        return;
    }

    ui->innerView->setStyleSheet("");
    ui->mainView->setStyleSheet("");
    ui->borderLayout->setMargin(_borderWidth);
    ui->mainLayout->setMargin(_borderColor.isWhite() ? 1 : 0);
    QString borderStyle;

    if (_borderColor.isWhite()) {
        borderStyle.append("#ID {border: 1px solid black;}");
        ui->innerView->setStyleSheet(QString(borderStyle).replace("ID", "innerView"));
        ui->mainView->setStyleSheet(QString(borderStyle).replace("ID", "mainView"));
    }

    QString colorStyle;
    colorStyle.append("#borderView {border:").append(QString::number(_borderWidth)).append("px ");
    colorStyle.append("solid rgb(");
    colorStyle.append(QString::number(_borderColor.red)).append(",");
    colorStyle.append(QString::number(_borderColor.green)).append(",");
    colorStyle.append(QString::number(_borderColor.blue)).append(");}");

    ui->borderView->setStyleSheet(colorStyle);
}

void TwoTextsView::showLot(bool visible)
{
    ui->mainView->setVisible(visible);
    calcViewSize();
}

LotView *TwoTextsView::clone() const
{
    TwoTextsView* copy = new TwoTextsView;
    copy->_borderColor = this->_borderColor;
    copy->_initialized = this->_initialized;
    copy->_showBorder = this->_showBorder;
    copy->ui->topView->setText(this->ui->topView->text());
    copy->ui->bottomView->setText(this->ui->bottomView->text());
    return copy;
}
