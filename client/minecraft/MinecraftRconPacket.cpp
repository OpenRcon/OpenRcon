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

#include <QString>

#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"

MinecraftRconPacket::MinecraftRconPacket(int requestId, MinecraftRconPacketType type, char* content) : requestId(requestId), type(type), content(content)
{

}

MinecraftRconPacket::MinecraftRconPacket(int requestId,  MinecraftRconPacketType type) : MinecraftRconPacket(requestId, type, nullptr)
{

}

MinecraftRconPacket::MinecraftRconPacket() : MinecraftRconPacket(0,  MinecraftRconPacketType::CommandResponse, nullptr)
{

}

MinecraftRconPacket::~MinecraftRconPacket()
{

}

int MinecraftRconPacket::getLength()
{
    return 10 + strlen(content);
}

int MinecraftRconPacket::getRequestId()
{
    return requestId;
}

MinecraftRconPacketType MinecraftRconPacket::getType()
{
    return type;
}

char* MinecraftRconPacket::getContent()
{
    return content;
}

int MinecraftRconPacket::getContentSize()
{
    return strlen(content);
}
