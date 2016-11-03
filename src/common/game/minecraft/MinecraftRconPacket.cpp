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

#include <QDebug>
#include <QString>

#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"

MinecraftRconPacket::MinecraftRconPacket()
{

}

MinecraftRconPacket::MinecraftRconPacket(int requestId, MinecraftRconPacketType type, const char *content) :
    requestId(requestId),
    type(type),
    content(content)
{

}

MinecraftRconPacket::~MinecraftRconPacket()
{

}

unsigned int MinecraftRconPacket::getLength() const
{
    return 10 + strlen(content);
}

unsigned int MinecraftRconPacket::getRequestId() const
{
    return requestId;
}

void MinecraftRconPacket::setRequestId(int requestId)
{
    this->requestId = requestId;
}

MinecraftRconPacketType MinecraftRconPacket::getType() const
{
    return type;
}

void MinecraftRconPacket::setType(const MinecraftRconPacketType &type)
{
    this->type = type;
}

const char *MinecraftRconPacket::getContent() const
{
    return content;
}

void MinecraftRconPacket::setContent(char *content)
{
    this->content = content;
}

unsigned int MinecraftRconPacket::getContentSize() const
{
    return strlen(content);
}

QDataStream &operator <<(QDataStream &out, const MinecraftRconPacket &packet)
{
    if (out.byteOrder() != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    //if (packet.getLength() < 1460 - 10) {
        out << packet.getLength();
        out << packet.getRequestId();
        out << static_cast<std::underlying_type<MinecraftRconPacketType>::type>(packet.getType());

        if (packet.getContentSize() > 0) {
            out.writeRawData(packet.getContent(), packet.getContentSize());
        }

        // Terminate the packet with 2 bytes of zeroes.
        signed char terminator = 0;
        out << terminator;
        out << terminator;

        qDebug() << "Sent packet:";
        qDebug() << "Length:" << packet.getLength();
        qDebug() << "Request ID:" << packet.getRequestId();
        qDebug() << "Type: " << static_cast<std::underlying_type<MinecraftRconPacketType>::type>(packet.getType());

        // Only display payload if it exists.
        if (packet.getLength() > 10) {
            qDebug() << "Payload:" << packet.getContent();
            qDebug() << "Hex data:" << QByteArray(packet.getContent()).toHex();
        }
    //}

    return out;
}

QDataStream &operator >>(QDataStream &in, MinecraftRconPacket &packet)
{
    if (in.byteOrder() != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    // Read the headers for later use.
    int length, id, type;
    in >> length;
    in >> id;
    in >> type;

    // Read the data.
    char *content = new char[length - 8];
    in.readRawData(content, length - 8);

    // Terminate the packet with 2 bytes of zeroes.
    signed char terminator1 = 0;
    signed char terminator2 = 0;
    in >> terminator1;
    in >> terminator2;

    qDebug() << "Read packet:";
    qDebug() << "Length: " << length;
    qDebug() << "Request ID: " << id;
    qDebug() << "Type: " << type;

    // If the length is 10, there is no payload.
    if (length > 10) {
        qDebug() << "Payload:" << content;
        qDebug() << "Hex data:" << QByteArray(content).toHex();
    }

    packet.setRequestId(id);
    packet.setType(static_cast<MinecraftRconPacketType>(type));
    packet.setContent(content);

    /*
    if (content) {
        delete[] content;
    }
    */

    return in;
}
