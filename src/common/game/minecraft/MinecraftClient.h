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

#ifndef MINECRAFTCLIENT_H
#define MINECRAFTCLIENT_H

#include "Client.h"
#include "MinecraftConnection.h"
#include "MinecraftCommandHandler.h"

class MinecraftClient : public Client
{
    Q_OBJECT

public:
    MinecraftClient(ServerEntry *serverEntry, MinecraftCommandHandler *commandHandler, QObject *parent = nullptr);
    ~MinecraftClient() final;

    MinecraftConnection *getConnection() final {
        return connection;
    }

    MinecraftCommandHandler *getCommandHandler() final {
        return commandHandler;
    }

    void connectToHost();
    void disconnectFromHost();
    void reconnectToHost();

protected:
    MinecraftConnection *connection;
    MinecraftCommandHandler *commandHandler;

private slots:
    void onConnected(QAbstractSocket *socket);
    void onDisconnected(QAbstractSocket *socket);

};

#endif // MINECRAFTCLIENT_H
