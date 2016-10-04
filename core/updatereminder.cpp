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

#include "updatereminder.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>
#include "settingshandler.h"
#include <QXmlStreamReader>

#define UPDATE_URL "http://lioddensorbo.com/urim/updates/"

UpdateReminder::UpdateReminder(std::function<void (UpdateInfo)> callback)
    : _reply(0),
      _callback(callback)
{
    _timeoutTimer.setInterval(60000);
    _timeoutTimer.setSingleShot(true);

    connect(&_timeoutTimer, SIGNAL(timeout()), SLOT(timeout()));
}

void UpdateReminder::checkForUpdate()
{
    QString url = QString(UPDATE_URL)
            .append("?v=").append(QCoreApplication::applicationVersion())
            .append("&lang=").append(SettingsHandler::language());

    QNetworkRequest req(url);
    req.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    _reply = _manager.get(req);
    _timeoutTimer.start();
    connect(_reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void UpdateReminder::setCallback(std::function<void (UpdateInfo)> callback)
{
    _callback = callback;
}

void UpdateReminder::httpFinished()
{
    _timeoutTimer.stop();
    QString reply(_reply->readAll());
    UpdateInfo info = parseReply(reply);

    if (_reply->error() != QNetworkReply::NoError) {
        info.hasError = true;
    }

    _callback(info);
}

void UpdateReminder::timeout()
{
    _reply->abort();
    UpdateInfo info;
    info.hasError = true;
    _callback(info);
}

UpdateInfo UpdateReminder::parseReply(QString reply)
{
    QXmlStreamReader xml(reply);
    UpdateInfo info;

    if (xml.readNextStartElement()) {
        if (xml.name() == "application-info" && xml.attributes().value("version") == "1.0") {
            info = readApplicationInfoXml(xml);
        } else {
            xml.raiseError("Not an application-info version 1.0 XML file");
        }
    }

    info.hasError = xml.hasError();
    return info;
}

UpdateInfo UpdateReminder::readApplicationInfoXml(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "application-info");

    UpdateInfo info;

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            QString appName = xml.readElementText();
            if (appName != QCoreApplication::applicationName()) {
                xml.raiseError("Wrong application name in XML");
            } else {
                info.appName = appName;
            }
        } else if (xml.name() == "has-update") {
            QString hasUpdate = xml.readElementText();
            info.hasUpdate = (hasUpdate == "true") ? true : false;
        } else if (xml.name() == "latest-version") {
            info.latestVersion = xml.readElementText();
        } else if (xml.name() == "download-page-url") {
            info.downloadPageUrl = xml.readElementText();
        } else {
            xml.skipCurrentElement();
        }
    }

    return info;
}

