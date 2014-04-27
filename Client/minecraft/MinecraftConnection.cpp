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

#include "MinecraftConnection.h"

MinecraftConnection::MinecraftConnection(QObject *parent) : Connection(parent), commandHandler(new MinecraftCommandHandler(this))
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MinecraftConnection::~MinecraftConnection()
{
    delete commandHandler;
}

/* Length 	int 	Length of remainder of packet
 * Request ID 	int 	Client-generated ID
 * Type 	int 	3 for login, 2 to run a command
 * Payload 	byte[] 	ASCII text
 * 2-byte pad 	byte, byte 	Two null bytes
 */

void MinecraftConnection::sendPacket(MinecraftRconPacket &packet)
{
    QDataStream out(tcpSocket);
    out.setByteOrder(QDataStream::LittleEndian);

    if (packet.getLength() < 1460 - 10) {    
        out << packet.getLength();
        out << packet.getRequestId();
        out << packet.getType();
        out.writeRawData(packet.getContent(), packet.getContentSize());

        // Terminate the packet with 2 bytes of zeroes.
        out << (unsigned char) 0;
        out << (unsigned char) 0;

        qDebug() << "Sent packet: ";
        qDebug() << "Length: " << packet.getLength();
        qDebug() << "Request ID: " << packet.getRequestId();
        qDebug() << "Type: " << packet.getType();
        qDebug() << "Payload:" << packet.getContent() << "\n";

        commandHandler->onDataSentEvent(packet.getContent());
    } else {
        qDebug() << "Payload data too long.";
    }
}

/* Length 	int 	Length of remainder of packet
 * Request ID 	int 	Client-generated ID
 * Type 	int 	3 for login, 2 to run a command
 * Payload 	byte[] 	ASCII text
 * 2-byte pad 	byte, byte 	Two null bytes
 */

void MinecraftConnection::readyRead()
{
    QDataStream in(tcpSocket);
    in.setByteOrder(QDataStream::LittleEndian);

    if (tcpSocket->bytesAvailable()) {
        int length, id, type;
        in >> length;
        in >> id;
        in >> type;

        char* content = new char[length - 10];
        in.readRawData(content, length - 10);

        // Terminate the packet with 2 bytes of zeroes.
        unsigned char pad1, pad2;
        in >> pad1;
        in >> pad2;

        qDebug() << "Read packet:";
        qDebug() << "Length: " << length;
        qDebug() << "Request ID: " << id;
        qDebug() << "Type: " << type;
        qDebug() << "Payload:" << content;
        qDebug() << "Hex data:" << QByteArray(content).toHex();

        // Create and handle the packet.
        MinecraftRconPacket packet(id, type, content);
        handlePacket(packet);

        delete[] content;
    }
}

void MinecraftConnection::sendCommand(const QString &command)
{
    if (!command.isEmpty()) {
        MinecraftRconPacket packet = MinecraftRconPacket(commandHandler->getRequestIdFromCommand(command), MinecraftRconPacket::Command, command.toLatin1().constData());
        sendPacket(packet);
    }
}

void MinecraftConnection::handlePacket(MinecraftRconPacket &packet)
{
    commandHandler->responseDataReceivedEvent(packet.getContent());
    commandHandler->parse(packet);
}
