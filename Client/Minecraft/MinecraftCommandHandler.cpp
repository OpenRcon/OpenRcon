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

MinecraftCommandHandler::MinecraftCommandHandler(QObject *parent) : QObject(parent)
{

}

MinecraftCommandHandler::~MinecraftCommandHandler()
{

}

void MinecraftCommandHandler::exec(MinecraftRconPacket &packet)
{
    switch (packet.getRequestId()) {
        case 2:
            helpCommand(packet);
            break;

        case 3:
            listCommand(packet);
            break;

        default:
            unknownCommand(packet);
    }
}

int MinecraftCommandHandler::getRequestIdForCommand(const QString &command)
{
    if (command == "help") {
        return 2;
    } else if (command == "list") {
        return 3;
    }

    return 0;
}

void MinecraftCommandHandler::helpCommand(MinecraftRconPacket &packet)
{
    Q_UNUSED(packet);

    //emit (onHelpCommand(packet));
}

void MinecraftCommandHandler::listCommand(MinecraftRconPacket &packet)
{
    QStringList playerList = QString(packet.getContent()).split(" ");

    emit (onListCommand(playerList));
}

void MinecraftCommandHandler::unknownCommand(MinecraftRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onUnknownCommand());
}
