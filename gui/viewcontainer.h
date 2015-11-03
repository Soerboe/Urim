#ifndef VIEWCONTAINER_H
#define VIEWCONTAINER_H

#include <QWidget>

class LotView;

namespace Ui {
class ViewContainer;
}

class ViewContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ViewContainer(QWidget *parent = 0);
    ~ViewContainer();

    void setLotView(LotView* view);
    void clear();

private:
    Ui::ViewContainer *ui;
    LotView* _lotView;
};

#endif // VIEWCONTAINER_H
