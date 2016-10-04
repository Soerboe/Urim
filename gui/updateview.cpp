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

#include "updateview.h"
#include "ui_updateview.h"
#include <QCoreApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

UpdateView::UpdateView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateView),
    _isUpdating(false)
{
    ui->setupUi(this);

    connect(ui->ignoreButton, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->updateButton, SIGNAL(clicked()), SLOT(updateClicked()));
}

UpdateView::~UpdateView()
{
    delete ui;
}

void UpdateView::setUpdateInfo(UpdateInfo info)
{
    QString description(tr(
"Version <strong>%1</strong> has been released. You are using version <strong>%2</strong>. \
Click the update button below to download the new version from the application website.")
.arg(info.latestVersion).arg(QCoreApplication::applicationVersion()));

    ui->updateDescription->setText(description);
    _downloadPage = info.downloadPageUrl;
}

void UpdateView::checkForUpdate()
{
    if (_isUpdating) {
        return;
    }

    _isUpdating = true;
    _reminder.setCallback([&](UpdateInfo info) {
        if (info.hasError) {
            QMessageBox::warning(parentWidget(), tr("Update error"), tr("An error occured while checking for a new version. Please try again later."));
        } else if (!info.hasUpdate) {
            QMessageBox::information(parentWidget(), tr("No update"), tr("There are currently no updates available."));
        } else { // has update
            this->setUpdateInfo(info);
            this->show();
        }

        _isUpdating = false;
    });
    _reminder.checkForUpdate();
}

void UpdateView::updateClicked()
{
    bool ok = QDesktopServices::openUrl(QUrl(_downloadPage));

    if (!ok) {
        QMessageBox::information(this,
                                 tr("Failed to open download page"),
                                 tr("Could not open download page in your default browser. Please enter the following URL into your browser to update the application: <strong>%1</strong>").arg(_downloadPage));
    }

    accept();
}
