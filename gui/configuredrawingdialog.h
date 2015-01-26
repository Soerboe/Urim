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

#ifndef CONFIGUREDRAWINGDIALOG_H
#define CONFIGUREDRAWINGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigureDrawingDialog;
}

class ConfigureDrawingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureDrawingDialog(const QString name, QWidget* parent = 0);
    ~ConfigureDrawingDialog();

    void init(bool uniqueResults);
    bool uniqueResults() {return _uniqueResults;}

protected:
    virtual bool validate() = 0;
    virtual void prepareResults();
    Ui::ConfigureDrawingDialog* ui;

private slots:
    void okClicked();

private:
    bool _uniqueResults;
};

#endif // CONFIGUREDRAWINGDIALOG_H
