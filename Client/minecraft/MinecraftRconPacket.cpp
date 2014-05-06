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

#include "MinecraftRconPacket.h"

MinecraftRconPacket::MinecraftRconPacket(int requestId, unsigned int type, const char* content) : requestId(requestId), type(type), content(content)
{

}

MinecraftRconPacket::MinecraftRconPacket(int requestId, unsigned int type) : MinecraftRconPacket(requestId, type, 0)
{

}

MinecraftRconPacket::MinecraftRconPacket() : MinecraftRconPacket(0, 0, 0)
{

}

MinecraftRconPacket::~MinecraftRconPacket()
{
    // delete[] content; TODO: Fix this, causes SIGABRT.
}

int MinecraftRconPacket::getLength()
{
    return 10 + getContentSize();
}

int MinecraftRconPacket::getRequestId()
{
    return requestId;
}

int MinecraftRconPacket::getType()
{
    return type;
}

const char* MinecraftRconPacket::getContent()
{
    return content;
}

int MinecraftRconPacket::getContentSize()
{
    return strlen(content);
}
