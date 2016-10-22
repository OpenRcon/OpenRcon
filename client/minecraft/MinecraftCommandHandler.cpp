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

#include "MinecraftCommandHandler.h"
#include "MinecraftConnection.h"
#include "MinecraftRconPacket.h"
#include "MinecraftRconCommandType.h"

MinecraftCommandHandler::MinecraftCommandHandler(MinecraftConnection *parent) : CommandHandler(parent), connection(parent)
{
    if (parent) {
        parent->setCommandHandler(this);
    }
}

MinecraftCommandHandler::~MinecraftCommandHandler()
{

}



bool MinecraftCommandHandler::parse(const MinecraftRconPacket &packet)
{
    /*
    typedef void (MinecraftCommandHandler::*ResponseFunction)(const MinecraftRconPacket&);

    static QHash<MinecraftRconCommandType, ResponseFunction> responseList = {
        { MinecraftRconCommandType::ListCommand,    &MinecraftCommandHandler::parseListCommand }
    };

    //MinecraftRconCommandType commandType =

    qDebug() << static_cast<MinecraftRconCommandType>(packet.getRequestId());

    if (responseList.contains(commandType)) {
        ResponseFunction response = responseList[commandType];

        if (response) {
            (this->*response)(packet);
        }

        return true;
    }
    */

    return false;
}

void MinecraftCommandHandler::parseListCommand(MinecraftRconPacket &packet)
{
    QStringList playerList = QString(packet.getContent()).split(" ");

    emit (onListCommand(playerList));
}
