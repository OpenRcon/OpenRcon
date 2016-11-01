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

#include <QDataStream>

#include "MinecraftConnection.h"
#include "MinecraftCommandHandler.h"
#include "MinecraftRconPacket.h"
#include "MinecraftRconPacketType.h"
#include "MinecraftCommandType.h"

#define DATA_BUFFERSIZE 10240

MinecraftConnection::MinecraftConnection(MinecraftCommandHandler *commandHandler, QObject *parent) :
    Connection(parent),
    commandHandler(commandHandler)
{
    if (commandHandler) {
        commandHandler->setConnection(this);
    }

    connect(socket, &QAbstractSocket::readyRead, this, &MinecraftConnection::readyRead);
}

MinecraftConnection::~MinecraftConnection()
{

}

void MinecraftConnection::sendPacket(const MinecraftRconPacket &packet)
{
    QDataStream out(socket);
    out.setByteOrder(QDataStream::LittleEndian);

    if (packet.getLength() < 1460 - 10) {
        out << packet.getLength();
        out << packet.getRequestId();
        out << static_cast<std::underlying_type<MinecraftRconPacketType>::type>(packet.getType());

        if (packet.getContentSize() > 0) {
            //out << packet.getContent();
            out.writeRawData(packet.getContent(), packet.getContentSize());
        }

        // Terminate the packet with 2 bytes of zeroes.
        signed char terminator1;
        signed char terminator2;
        out << terminator1;
        out << terminator2;

        //uint8_t terminator2;
        //out << terminator2;

        qDebug() << "Sent packet:";
        qDebug() << "Length:" << packet.getLength();
        qDebug() << "Request ID:" << packet.getRequestId();
        qDebug() << "Type: " << static_cast<std::underlying_type<MinecraftRconPacketType>::type>(packet.getType());

        // Only display payload if it exists.
        if (packet.getLength() > 10) {
            qDebug() << "Payload:" << packet.getContent();
            qDebug() << "Hex data:" << QByteArray(packet.getContent()).toHex();
        }

        if (packet.getType() == MinecraftRconPacketType::Command) {

        }

        responseDataSent(packet.getContent());
    } else {
        qDebug() << tr("Payload data too long.");
    }
}

void MinecraftConnection::readyRead()
{
    qDebug() << "Readyread!";

    QDataStream in(socket);
    in.setByteOrder(QDataStream::LittleEndian);

    if (socket->bytesAvailable()) {
        // Read the headers for later use.
        signed int length, id, type;
        in >> length;
        in >> id;
        in >> type;

        // Read the data.
        char* content = new char[length - 10];
        in >> content;

        // Terminate the packet with 2 bytes of zeroes.
        signed char terminator1;
        signed char terminator2;
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

        // Create and handle the packet.
        MinecraftRconPacket packet(id, static_cast<MinecraftRconPacketType>(type), content);

        if (packet.getType() == MinecraftRconPacketType::Auth) {
            emit (onAuthenticated(true));
        } else {
             commandHandler->parse(packet);
             //responseDataReceived(packet.getContent());
        }

        delete[] content;
    }
}

void MinecraftConnection::sendCommand(const QString &command)
{
    if (!command.isEmpty()) {
        MinecraftRconPacket packet(getRequestIdFromCommand(command), MinecraftRconPacketType::Command, command.toLatin1().data());
        sendPacket(packet);
    }
}

MinecraftCommandType MinecraftConnection::getCommandTypeFromCommand(const QString &command)
{
    if (command == "list") {
        return MinecraftCommandType::ListCommand;
    } else if (command == "kill") {
        return MinecraftCommandType::KillCommand;
    }

    return MinecraftCommandType::UnknownCommand;
}

int MinecraftConnection::getRequestIdFromCommand(const QString &command) {
    return static_cast<std::underlying_type<MinecraftRconPacketType>::type>(getCommandTypeFromCommand(command));
}
