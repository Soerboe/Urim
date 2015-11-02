#ifndef TWOTEXTSVIEW_H
#define TWOTEXTSVIEW_H

#include "lotview.h"
#include "color.h"

namespace Ui {
class TwoTextsView;
}

class TwoTextsView : public LotView
{
    Q_OBJECT

public:
    explicit TwoTextsView(QWidget *parent = 0);
    ~TwoTextsView();

    virtual void showLot(bool visible);

protected:
    Ui::TwoTextsView *ui;
    void setTopText(QString text);
    void setBottomText(QString text);
    virtual void calcViewSize();

    void setBorderColor(Color color);
    void initialize() {_initialized = true;}
    void showBorder() {_showBorder = true;}

private:
    bool _initialized;
    bool _showBorder;
    Color _borderColor;
    int _borderWidth;

    void updateBorder();
};

#endif // TWOTEXTSVIEW_H
