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
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINECRAFTCONNECTION_H
#define MINECRAFTCONNECTION_H

#include "Connection.h"

class MinecraftCommandHandler;
class MinecraftRconPacket;
enum class MinecraftRconCommandType;

class MinecraftConnection : public Connection
{
    Q_OBJECT

public:
    MinecraftConnection(QObject *parent = nullptr);
    ~MinecraftConnection();

    MinecraftCommandHandler *getCommandHandler() const;
    void setCommandHandler(MinecraftCommandHandler *commandHandler);

    void sendPacket(MinecraftRconPacket &packet);
    void sendCommand(const QString &command);

private:
    MinecraftCommandHandler *commandHandler;
    QVector<MinecraftRconPacket> packetSendQueue;

    MinecraftRconCommandType getCommandTypeFromCommand(const QString &command);
    int getRequestIdFromCommand(const QString &command);

private slots:
    void readyRead();

signals:
    // Events
    void onAuthenticated(bool auth);

};

#endif // BFBC2CONNECTION_H
