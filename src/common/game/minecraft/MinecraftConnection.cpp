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

#include <QDataStream>

#include "MinecraftConnection.h"
#include "MinecraftCommandHandler.h"
#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"
#include "MinecraftCommandType.h"

#define DATA_BUFFERSIZE 10240

MinecraftConnection::MinecraftConnection(MinecraftCommandHandler *commandHandler, QObject *parent) :
    Connection(parent),
    commandHandler(commandHandler)
{
    if (commandHandler) {
        commandHandler->setConnection(this);
    }

    connect(socket, &QAbstractSocket::readyRead, this, &MinecraftConnection::readyRead);
}

MinecraftConnection::~MinecraftConnection()
{

}

void MinecraftConnection::sendPacket(const MinecraftRconPacket &packet)
{
    QDataStream out(socket);
    out << packet;

    responseDataSent(packet.getContent());
}

void MinecraftConnection::readyRead()
{
    qDebug() << "ReadyRead!";

    MinecraftRconPacket packet;
    QDataStream in(socket);
    in >> packet;

    responseDataReceived(packet.getContent());

    // Handle the packet.
    /*
    if (packet.getType() == MinecraftRconPacketType::Auth) {
        emit (onAuthenticated(true));
    } else {
         //commandHandler->parse(packet);

    }*/
}

void MinecraftConnection::sendCommand(const QString &command)
{
    if (!command.isEmpty()) {
        MinecraftRconPacket packet(198, MinecraftRconPacketType::Command, command.toLatin1().constData());
        sendPacket(packet);
    }
}

MinecraftCommandType MinecraftConnection::getCommandTypeFromCommand(const QString &command)
{
    if (command == "list") {
        return MinecraftCommandType::ListCommand;
    } else if (command == "kill") {
        return MinecraftCommandType::KillCommand;
    }

    return MinecraftCommandType::UnknownCommand;
}

int MinecraftConnection::getRequestIdFromCommand(const QString &command) {
    return static_cast<std::underlying_type<MinecraftRconPacketType>::type>(getCommandTypeFromCommand(command));
}
