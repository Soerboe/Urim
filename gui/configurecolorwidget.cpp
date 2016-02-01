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

#include "configurecolorwidget.h"
#include "ui_configurecolorwidget.h"
#include "settingshandler.h"
#include <qpainter.h>
#include "guiutils.h"
#include <vector>
#include "editcolorsdialog.h"

#define COLS 7

using namespace std;

class ColorFrame : public QWidget
{
    Q_OBJECT

public:
    ColorFrame(Color c)
        : _color(c),
          _selected(false)
    {
        setFixedSize(30, 30);
        setCursor(Qt::PointingHandCursor);
        setToolTip(c.name());
    }

    void select(bool b)
    {
        _selected = b;
        update();
        emit changed();
    }

    bool isSelected() {return _selected;}
    Color color() {return _color;}

protected:
    void mouseReleaseEvent(QMouseEvent*)
    {
        toggleSelection();
    }

    void paintEvent(QPaintEvent* event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::black);
        painter.setBrush(QColor(_color.red(), _color.green(), _color.blue()));
        painter.drawRect(0, 0, width(), height());

        if (_selected) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(255, 255, 255, 180));
            painter.drawEllipse(QPointF(width()/2.0, height()/2.0), width() * 0.3, height() * 0.3);
            painter.setPen(Qt::black);
            painter.drawText(0, 0, width(), height(), Qt::AlignCenter | Qt::AlignHCenter, "✔");
        }
    }

signals:
    void changed();

private:
    Color _color;
    bool _selected;

    void toggleSelection() {
        select(!_selected);
    }

};

#include "configurecolorwidget.moc"

ConfigureColorWidget::ConfigureColorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureColorWidget)
{
    ui->setupUi(this);
    ui->buttonLayout->setAlignment(Qt::AlignTop);

    setupColorPicker();
    connect(this, &ConfigureColorWidget::changed, this, updateSelectedColorsView);
    connect(ui->editColorsButton, &QPushButton::clicked, this, editColorsClicked);
    connect(ui->unselectAllButton, &QPushButton::clicked, this, unselectAllClicked);
}

ConfigureColorWidget::~ConfigureColorWidget()
{
    delete ui;
}

void ConfigureColorWidget::init(const std::vector<Color> &colors)
{
    for (size_t i = 0 ; i < colors.size(); ++i) {
        for (int j = 0; j < ui->colorsLayout->count(); ++j) {
            ColorFrame* item = dynamic_cast<ColorFrame*> (ui->colorsLayout->itemAt(j)->widget());
            if (item && item->color() == colors[i]) {
                item->select(true);
            }
        }
    }

    emit changed();
}

bool ConfigureColorWidget::validate()
{
    return !selectedColors().empty();
}

QString ConfigureColorWidget::validationError()
{
    if (selectedColors().empty()) {
        return tr("No colors selected.");
    } else {
        return QString();
    }
}

std::vector<Color> ConfigureColorWidget::selectedColors()
{
    vector<Color> c;
    for(int i = 0; i < ui->colorsLayout->count(); ++i) {
        ColorFrame* item = dynamic_cast<ColorFrame*> (ui->colorsLayout->itemAt(i)->widget());
        if (item && item->isSelected()) {
            c.push_back(item->color());
        }
    }

    return c;
}

void ConfigureColorWidget::setupColorPicker()
{
    QList<Color> colors = SettingsHandler::colors();

    GuiUtils::clearLayout(ui->colorsLayout);
    _colorFrames.clear();

    for(int i = 0; i < colors.size(); ++i) {
        Color c = colors.at(i);
        ColorFrame* cf = new ColorFrame(c);
        connect(cf, &ColorFrame::changed, [&]() {emit changed();});
        _colorFrames.append(cf);
        ui->colorsLayout->addWidget(cf, i / COLS, i % COLS);
    }
}

void ConfigureColorWidget::updateSelectedColorsView()
{
    ui->selectedColorsLabel->clear();
    QString text(tr("<strong>Selected colors:</strong> "));
    int i = 0;

    for(Color color : selectedColors()) {
        if (i++ != 0) {
            text.append(", ");
        }

        text.append(color.name());
    }

    ui->selectedColorsLabel->setText(text);
}

void ConfigureColorWidget::editColorsClicked()
{
    vector<Color> colors = selectedColors();
    EditColorsDialog dialog;

    dialog.exec();
    setupColorPicker();
    init(colors);
}

void ConfigureColorWidget::unselectAllClicked()
{
    for (int i = 0; i < ui->colorsLayout->count(); ++i) {
        ColorFrame* item = dynamic_cast<ColorFrame*> (ui->colorsLayout->itemAt(i)->widget());
        if (item) {
            item->select(false);
        }
    }

    emit changed();
}
