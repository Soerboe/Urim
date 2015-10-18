#ifndef LOTVIEWSELECTOR_H
#define LOTVIEWSELECTOR_H

#include <QWidget>

class QButtonGroup;
class LotView;

namespace Ui {
class LotViewSelector;
}

class LotViewSelector : public QWidget
{
    Q_OBJECT

public:
    explicit LotViewSelector(QWidget *parent = 0);
    ~LotViewSelector();

    void init(int viewIndex);
    void addView(LotView* lotView);
    int selectedViewIndex();

private:
    Ui::LotViewSelector *ui;
    QButtonGroup* _radioGroup;
};

#endif // LOTVIEWSELECTOR_H
