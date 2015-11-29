#ifndef VERTICALTEXTSVIEW_H
#define VERTICALTEXTSVIEW_H

#include "lotviewtextasmain.h"
#include "color.h"
#include <vector>

class QLabel;

namespace Ui {
class VerticalTextsView;
}

class VerticalTextsView : public LotViewTextAsMain
{
    Q_OBJECT

public:
    explicit VerticalTextsView(int numViews, QString longestText, QWidget *parent = 0);
    ~VerticalTextsView();

    virtual void showLot(bool visible);
    virtual LotView* clone() const;

protected:
    Ui::VerticalTextsView *ui;
    void setViewText(size_t index, QString text);
    virtual void calcViewSize();

    void setBorderColor(Color color);
    void initialize() {_initialized = true;}
    void showBorder(bool show) {_showBorder = show;}

private:
    bool _initialized;
    bool _showBorder;
    Color _borderColor;
    int _borderWidth;

    void updateBorder();

    std::vector<QLabel*> _views;
};

#endif // VERTICALTEXTSVIEW_H
