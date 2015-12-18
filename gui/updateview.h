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

#ifndef UPDATEVIEW_H
#define UPDATEVIEW_H

#include <QDialog>
#include "updateinfo.h"
#include "updatereminder.h"


namespace Ui {
class UpdateView;
}

class UpdateView : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateView(QWidget *parent = 0);
    ~UpdateView();

    void setUpdateInfo(UpdateInfo info);
    void checkForUpdate();

private slots:
    void updateClicked();

private:
    Ui::UpdateView *ui;

    QString _downloadPage;
    UpdateReminder _reminder;
    bool _isUpdating;
};

#endif // UPDATEVIEW_H
