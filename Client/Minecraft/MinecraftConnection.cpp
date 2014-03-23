/*
 * Copyright (C) 2010 The OpenRcon Project.
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

MinecraftConnection::MinecraftConnection(QObject *parent) : Connection(parent), requestId(0)
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MinecraftConnection::~MinecraftConnection()
{
    delete tcpSocket;
}

void MinecraftConnection::hostConnect(const QString &host, const int &port)
{
    tcpSocket->connectToHost(host, port);
}

/*
 * Length 	int 	Length of remainder of packet
 * Request ID 	int 	Client-generated ID
 * Type 	int 	3 for login, 2 to run a command
 * Payload 	byte[] 	ASCII text
 * 2-byte pad 	byte, byte 	Two null bytes
 */

void MinecraftConnection::sendPacket(const int &type, const char* payload)
{
    int length = 10 + strlen(payload);

    QDataStream out(tcpSocket);
    out.setByteOrder(QDataStream::LittleEndian);
    out << length;
    out << requestId;
    out << type;
    out.writeRawData(payload, strlen(payload));
    out << (qint8) 0;
    out << (qint8) 0;

    requestId = rand();

    qDebug() << "Sent data is: ";
    qDebug() << "Length: " << length;
    qDebug() << "Request ID: " << requestId;
    qDebug() << "Type: " << type;
    qDebug() << "Payload:" << payload;
}

void MinecraftConnection::sendCommand(const QString &command)
{
    sendPacket(2, command.toLatin1());
}

/*
 * Length 	int 	Length of remainder of packet
 * Request ID 	int 	Client-generated ID
 * Type 	int 	3 for login, 2 to run a command
 * Payload 	byte[] 	ASCII text
 * 2-byte pad 	byte, byte 	Two null bytes
 */

void MinecraftConnection::readyRead()
{
    int length, id, type;
    char* payload;
    int pad1, pad2;

    QDataStream in(tcpSocket);
    in.setByteOrder(QDataStream::LittleEndian);
    in >> length;
    in >> id;
    in >> type;
    in.readRawData(payload, length - 10);
    in >> pad1;
    in >> pad2;

    //qDebug() << "Read packet with length " << length << " and type " << type;
    qDebug() << "Data: " << payload;

    if (id == 0 && type == 2) {
        qDebug() << "You are successfully logged in!";

        emit (signalAuthenticated(true));
    } else if (id == -1) {
        qDebug() << "Login failed!";

        emit (signalAuthenticated(false));
    }

    handlePacket(payload);
}

void MinecraftConnection::handlePacket(const QString &packet)
{
    emit (signalPacket(packet));
}
