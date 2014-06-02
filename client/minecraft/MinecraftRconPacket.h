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

#ifndef MINECRAFTRCONPACKET_H
#define MINECRAFTRCONPACKET_H

//Length 	int 	Length of remainder of packet
//Request ID 	int 	Client-generated ID
//Type 	int 	3 for login, 2 to run a command
//Payload 	byte[] 	ASCII text
//2-byte pad 	byte, byte 	Two null bytes

#include <QVector>

enum class MinecraftRconPacketType;

class MinecraftRconPacket
{
public:
    MinecraftRconPacket(int requestId, MinecraftRconPacketType type, char* content);
    MinecraftRconPacket(int requestId, MinecraftRconPacketType type);
    MinecraftRconPacket();
    ~MinecraftRconPacket();

    int getLength();
    int getRequestId();
    MinecraftRconPacketType getType();
    char *getContent();
    int getContentSize();

private:
    int requestId;
    MinecraftRconPacketType type;
    char *content;

};

#endif // MINECRAFTRCONPACKET_H
