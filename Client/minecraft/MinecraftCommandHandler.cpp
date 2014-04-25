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

#include "MinecraftCommandHandler.h"

MinecraftCommandHandler::MinecraftCommandHandler(QObject *parent) : CommandHandler(parent)
{

}

MinecraftCommandHandler::~MinecraftCommandHandler()
{

}

void MinecraftCommandHandler::parse(MinecraftRconPacket &packet)
{
    switch (packet.getRequestId()) {
        case 1:
            if (packet.getType() == MinecraftRconPacket::Login) {
                emit (onAuthenticated(true));
            } else {
                emit (onAuthenticated(false));
            }

            break;

        case ListCommand:
            responseListCommand(packet);
            break;

        default:
            responseUnknownCommand();
    }
}

int MinecraftCommandHandler::getRequestIdFromCommand(const QString &command)
{
    if (command == "list") {
        return ListCommand;
    } else if (command == "kill") {
        return KillCommand;
    }

    return UnknownCommand;
}

void MinecraftCommandHandler::responseListCommand(MinecraftRconPacket &packet)
{
    QStringList playerList = QString(packet.getContent()).split(" ");

    emit (onListCommand(playerList));
}
