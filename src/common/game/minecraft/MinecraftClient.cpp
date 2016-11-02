/*
 * Copyright (C) 201 The OpenRcon Project.
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

#include "MinecraftClient.h"
#include "MinecraftCommandHandler.h"
#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"
#include "ServerEntry.h"

MinecraftClient::MinecraftClient(ServerEntry *serverEntry, MinecraftCommandHandler *commandHandler, QObject *parent) :
    Client(serverEntry, parent),
    connection(new MinecraftConnection(commandHandler, this)),
    commandHandler(commandHandler)
{
    connectToHost();

    connect(connection, &Connection::onConnected, this, &MinecraftClient::onConnected);
}

MinecraftClient::~MinecraftClient()
{

}

void MinecraftClient::connectToHost()
{
    connection->hostConnect(serverEntry);
}

void MinecraftClient::disconnectFromHost()
{
    connection->hostDisconnect();
}

void MinecraftClient::reconnectToHost()
{
    if (connection->isConnected()) {
        disconnectFromHost();
    }

    connectToHost();
}

void MinecraftClient::onConnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    MinecraftRconPacket packet(1, MinecraftRconPacketType::Auth, serverEntry->getPassword().toLatin1().constData());
    connection->sendPacket(packet);

    qDebug() << "lololololololololololololo";
}


void MinecraftClient::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    //MinecraftRconPacket packet(1, MinecraftRconPacketType::Login, serverEntry->getPassword().toLatin1().data());
    //connection->sendPacket(packet);
}
