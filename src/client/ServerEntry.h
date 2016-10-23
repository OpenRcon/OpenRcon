/*
 * Copyright (C) 2016 The OpenRcon Project.
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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SERVERENTRY_H
#define SERVERENTRY_H

#include <QMetaType>
#include <QString>

#include "GameType.h"

class ServerEntry
{
public:
    ServerEntry(GameType gameType, const QString &name, const QString &host, int port, const QString &password, bool autoConnect);
    ServerEntry();
    ~ServerEntry();

    GameType getGameType();
    QString getName();
    QString getHost();
    int getPort();
    QString getPassword();
    bool getAutoConnect();
    void setAutoConnect(bool autoConnect);

private:
    GameType gameType;
    QString name;
    QString host;
    int port;
    QString password;
    bool autoConnect;

};

// For use with QVariant
Q_DECLARE_METATYPE(ServerEntry*)

#endif // SERVERENTRY_H
