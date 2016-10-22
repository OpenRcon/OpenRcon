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

#include "Minecraft.h"
#include "ServerEntry.h"
#include "MinecraftCommandHandler.h"
#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"

Minecraft::Minecraft(ServerEntry *serverEntry) : GameWidget(serverEntry), connection(new MinecraftConnection(this)), commandHandler(new MinecraftCommandHandler(connection))
{
    connection->hostConnect(serverEntry);

    connect(connection, &Connection::onConnected, this, &Minecraft::onConnected);
}

Minecraft::~Minecraft()
{

}

void Minecraft::onConnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    MinecraftRconPacket packet(1, MinecraftRconPacketType::Auth, serverEntry->getPassword().toUtf8().data());
    connection->sendPacket(packet);

    qDebug() << "lololololololololololololo";
}


void Minecraft::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    //MinecraftRconPacket packet(1, MinecraftRconPacketType::Login, serverEntry->getPassword().toLatin1().data());
    //connection->sendPacket(packet);
}
