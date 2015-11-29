#include "verticaltextsview.h"
#include "ui_verticaltextsview.h"
#include "guiutils.h"
#include <QLabel>

VerticalTextsView::VerticalTextsView(int numViews, QString longestText, QWidget *parent)
    : LotViewTextAsMain(longestText, parent),
      ui(new Ui::VerticalTextsView),
      _initialized(false),
      _showBorder(false),
      _borderWidth(0)
{
    ui->setupUi(this);

    for (int i = 0; i < numViews; ++i) {
        QLabel* l = new QLabel("");
        _views.push_back(l);
        l->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->innerLayout->addWidget(l);
    }
}

VerticalTextsView::~VerticalTextsView()
{
    delete ui;
}

void VerticalTextsView::setViewText(size_t index, QString text)
{
    if (index >= _views.size()) {
        return;
    }

    _views.at(index)->setText(text);
    initialize();
    calcViewSize();
}

void VerticalTextsView::calcViewSize()
{
    if (_views.size() == 0) {
        return;
    }

    if (_showBorder && _initialized) {
        _borderWidth = qMax(5.0, ui->mainView->width() * ui->mainView->height() * 0.00005);
        updateBorder();
    }

    QRect rect = _views[0]->rect();
    int fontSize = GuiUtils::calcMaxFontSize(_views[0]->font(), _longestText, rect);

    if (fontSize > 0) {
        QFont f = font();
        f.setPointSize(fontSize);
        for (size_t i = 0; i < _views.size(); ++i) {
            _views[i]->setFont(f);
        }
    }
}

void VerticalTextsView::setBorderColor(Color color)
{
    _borderColor = color;
    updateBorder();
}

void VerticalTextsView::updateBorder()
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

void VerticalTextsView::showLot(bool visible)
{
    ui->mainView->setVisible(visible);
    calcViewSize();
}

LotView *VerticalTextsView::clone() const
{
    VerticalTextsView* copy = new VerticalTextsView(this->_views.size(), _longestText);
    copy->_borderColor = this->_borderColor;
    copy->_initialized = this->_initialized;
    copy->_showBorder = this->_showBorder;
    for (size_t i = 0; i < this->_views.size(); ++i) {
        copy->setViewText(i, this->_views[i]->text());
    }
    return copy;
}
