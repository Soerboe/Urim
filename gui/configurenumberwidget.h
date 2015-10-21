#ifndef CONFIGURENUMBERWIDGET_H
#define CONFIGURENUMBERWIDGET_H

#include <QWidget>

namespace Ui {
class ConfigureNumberWidget;
}

class ConfigureNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureNumberWidget(bool enableLabel = true, QWidget *parent = 0);
    ~ConfigureNumberWidget();

    void init(int min, int max, QString label);
    bool validate() const;
    QString validationError() const;
    int min() const;
    int max() const;
    QString label() const;

private:
    Ui::ConfigureNumberWidget *ui;
};

#endif // CONFIGURENUMBERWIDGET_H
