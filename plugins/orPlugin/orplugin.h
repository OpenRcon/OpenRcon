/*
 * Copyright (C) 2010 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ORPLUGIN_H
#define ORPLUGIN_H

#include "orPlugin_global.h"

#include <QtGlobal>
#include <QObject>
#include <QDebug>

#include "orplugininterface.h"

class ORPLUGINSHARED_EXPORT orPlugin : public QObject, public orPluginInterface {
    Q_OBJECT
    Q_INTERFACES(orPluginInterface)

public:
    explicit orPlugin();
    ~orPlugin();

    bool isPluginOR();
    bool isUserAllowedToSetPortNumber();
    bool isUserAllowedToSetUsername();
    bool isUserAllowedToSetPassword();

    bool isEnabled();
    bool isSigned();
    qint32 openConnection(QString hostURI, quint32 portNumber, QString username, QString password);
    qint32 closeConnection();
    qint32 enable();
    qint32 disable();
    QString getName();
    QString getVersion();
    QString getDescription();
    QString getDeveloper();
    QString getDeveloperWebsite();
    QString getDeveloperSupportLink();
    QString getPluginSystemVersion();
    QString getPluginSystemType();
    QString getSignature();
    QString getPluginDefaultPortNumber();
    QString getConnectionStatus();
    QIcon getIcon();

};

#endif // ORPLUGIN_H
