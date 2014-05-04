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

MinecraftConnection::MinecraftConnection(QObject *parent) : Connection(parent)
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MinecraftConnection::~MinecraftConnection()
{

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
        out << packet.getContent();

        //out.writeRawData(packet.getContent(), packet.getContentSize());

        // Terminate the packet with 2 bytes of zeroes.
        out << (unsigned char) 0;
        out << (unsigned char) 0;

        qDebug() << "Sent packet: ";
        qDebug() << "Length: " << packet.getLength();
        qDebug() << "Request ID: " << packet.getRequestId();
        qDebug() << "Type: " << packet.getType();
        qDebug() << "Payload:" << packet.getContent() << "\n";
        qDebug() << "Hex data:" << QByteArray(packet.getContent()).toHex();

        if (packet.getType() == MinecraftRconPacket::Command) {
            responseDataSentEvent(packet.getContent());
        }
    } else {
        qDebug() << tr("Payload data too long.");
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
        in >> content;

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
        MinecraftRconPacket packet = MinecraftRconPacket(getRequestIdFromCommand(command), MinecraftRconPacket::Command, command.toLatin1().constData());
        sendPacket(packet);
    }
}

void MinecraftConnection::handlePacket(MinecraftRconPacket &packet)
{
    responseDataReceivedEvent(packet.getContent());
    parse(packet);
}

void MinecraftConnection::parse(MinecraftRconPacket &packet)
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
    }
}

int MinecraftConnection::getRequestIdFromCommand(const QString &command)
{
    if (command == "list") {
        return ListCommand;
    } else if (command == "kill") {
        return KillCommand;
    }

    return UnknownCommand;
}

void MinecraftConnection::responseListCommand(MinecraftRconPacket &packet)
{
    QStringList playerList = QString(packet.getContent()).split(" ");

    emit (onListCommand(playerList));
}

