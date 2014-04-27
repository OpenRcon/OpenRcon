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
#include <QString>
#include <QStringList>

class MinecraftRconPacket
{

public:
    explicit MinecraftRconPacket(const int &requestId, const unsigned int &type, const char* content);
    explicit MinecraftRconPacket(const int &requestId, const unsigned int &type);
    explicit MinecraftRconPacket();

    ~MinecraftRconPacket();

    enum PacketType {
        Command = 2,
        Login = 3
    };

    int getLength();
    int getRequestId();
    int getType();
    const char* getContent();
    int getContentSize();

private:
    int requestId;
    unsigned int type;
    const char* content;

};

#endif // MINECRAFTRCONPACKET_H
