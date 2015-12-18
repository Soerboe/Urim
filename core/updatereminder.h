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

#ifndef UPDATEREMINDER_H
#define UPDATEREMINDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <functional>
#include <QTimer>
#include "updateinfo.h"

class QXmlStreamReader;

class UpdateReminder : public QObject
{
    Q_OBJECT

public:
    UpdateReminder();
    UpdateReminder(std::function<void (UpdateInfo)> callback);
    void checkForUpdate();
    void setCallback(std::function<void (UpdateInfo)> callback);

private slots:
    void httpFinished();
    void timeout();

private:
    QNetworkAccessManager _manager;
    QNetworkReply* _reply;
    QTimer _timeoutTimer;

    std::function<void (UpdateInfo)> _callback;

    UpdateInfo parseReply(QString reply);
    UpdateInfo readApplicationInfoXml(QXmlStreamReader& xml);
};

#endif // UPDATEREMINDER_H
