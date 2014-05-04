/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#ifndef MINECRAFTCONNECTION_H
#define MINECRAFTCONNECTION_H

#include "Connection.h"

#include "MinecraftRconPacket.h"
#include "MinecraftCommandHandler.h"

class MinecraftConnection : public Connection
{
    Q_OBJECT

public:
    explicit MinecraftConnection(QObject *parent = 0);
    ~MinecraftConnection();

    void sendPacket(MinecraftRconPacket &packet);
    void sendCommand(const QString &command);

private:
    QVector<MinecraftRconPacket> packetSendQueue;

    enum CommandType {
        ListCommand = 8,
        KillCommand = 9,
        UnknownCommand = 255
    };

    int getRequestIdFromCommand(const QString &command);
    void handlePacket(MinecraftRconPacket &packet);

    void parse(MinecraftRconPacket &packet);

    void responseListCommand(MinecraftRconPacket &packet);

private slots:
    void readyRead();

signals:
    // Events
    void onAuthenticated(const bool &auth);

    // Commands
    void onListCommand(const QStringList &list);

};

#endif // BFBC2CONNECTION_H
