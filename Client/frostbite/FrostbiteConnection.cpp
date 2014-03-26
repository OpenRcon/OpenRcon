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

#include "FrostbiteConnection.h"

FrostbiteConnection::FrostbiteConnection(FrostbiteCommandHandler *commandHandler, QObject *parent) : Connection(parent), commandHandler(commandHandler), packetReadState(PacketReadingHeader), auth(false), nextPacketSeq(0)
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

FrostbiteConnection::~FrostbiteConnection()
{
    delete tcpSocket;
    delete commandHandler;
}

void FrostbiteConnection::hostConnect(const QString &host, const int &port)
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        packetSendQueue.clear();
        packetReadState = PacketReadingHeader;
        nextPacketSeq = 0;
        auth = false;

        tcpSocket->connectToHost(host, port);
    } else {
        if (tcpSocket) {
            qDebug() << QString("Already connected to %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
        } else {
            qDebug() << "ERROR: Connection::hostConnect tcpSocket = 0";
        }
    }
}

void FrostbiteConnection::authenticateSlot()
{
    auth = true;
}

void FrostbiteConnection::sendPacket(const FrostbiteRconPacket &packet, bool response)
{
    if (response) {
        QDataStream out(tcpSocket);
        out << packet;
    } else {
        QDataStream out(tcpSocket);
        out << packet;
        packetSendQueue.push_back(packet);
    }
}

void FrostbiteConnection::sendCommand(const QString &cmd)
{
    if (!cmd.isEmpty()) {
        FrostbiteRconPacket packet(FrostbiteRconPacket::ServerOrigin, FrostbiteRconPacket::Request, nextPacketSeq);
        QStringList cmdList;
        cmdList = cmd.split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "");

        for (int i = 0; i < cmdList.size(); i++) {
            packet.packWord(FrostbiteRconWord(cmdList.at(i).toUtf8().constData()));
        }

        sendPacket(packet);
        nextPacketSeq++;
    }
}

bool FrostbiteConnection::isAuthenticated()
{
    return auth;
}

void FrostbiteConnection::readyRead()
{
    bool exit = false;

    while (!exit) {
        switch (packetReadState) {
        case PacketReadingHeader:
            if (tcpSocket->bytesAvailable() >= MIN_PACKET_SIZE) {
                if (tcpSocket->read(lastHeader, MIN_PACKET_SIZE) != MIN_PACKET_SIZE) {
                    qDebug() << "Error while reading header.";
                    exit = true;
                    break;
                }
            } else {
                exit = true;
                break;
            }
            // *Intentionally* not breaking.

        case PacketReadingData:
            QDataStream hdrstream(QByteArray(lastHeader, MIN_PACKET_SIZE));
            hdrstream.setByteOrder(QDataStream::LittleEndian);

            quint32 seq, len, words;
            hdrstream >> seq;
            hdrstream >> len;
            hdrstream >> words;

            if (tcpSocket->bytesAvailable() >= len - MIN_PACKET_SIZE) {
                if (len >= MIN_PACKET_SIZE) {
                    char* data = new char[len];
                    memcpy(data, lastHeader, MIN_PACKET_SIZE);
                    if (tcpSocket->read(data + MIN_PACKET_SIZE, len - MIN_PACKET_SIZE) == len - MIN_PACKET_SIZE) {
                        QDataStream pstream(QByteArray(data, len));
                        FrostbiteRconPacket packet;
                        pstream >> packet;
                        handlePacket(packet);
                        qDebug() << QByteArray(data, len).toHex();
                    } else {
                        qDebug() << "Error while reading data.";
                    }

                    delete[] data;
                } else {
                    qDebug() << "Malformed packet, ignoring...";
                }

                packetReadState = PacketReadingHeader;
            } else {
                packetReadState = PacketReadingData;
                exit = true;
            }

            break;
        }
    }
}

void FrostbiteConnection::handlePacket(const FrostbiteRconPacket &packet)
{
    qDebug() << QString("We have %1 words in this packet:").arg(packet.getWordCount());

    if (packet.isResponse()) {
        QVector<FrostbiteRconPacket>::iterator it;

        for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
            if (it->getSequenceNum() == packet.getSequenceNum()) {
                break;
            }
        }

        if (it != packetSendQueue.end()) {
            const FrostbiteRconPacket& lastSentPacket = *it;

            if (lastSentPacket.getSequenceNum() == packet.getSequenceNum()) {
                if (lastSentPacket.getWordCount() > 0) {
                    QString command(lastSentPacket.getWord(0).getContent());

                    if (packet.getWordCount() > 0) {
                        quint32 lastPacketWordCount = lastSentPacket.getWordCount();
                        QString messages = command + " ";

                        for (quint32 i = 1; i < lastPacketWordCount; i++) {
                            messages += lastSentPacket.getWord(i).getContent();
                            messages += " ";
                        }

                        commandHandler->eventOnDataSent(messages);
                        qDebug() << messages;

                        QString messager;
                        quint32 packetWordCount = packet.getWordCount();

                        for (quint32 i = 0; i < packetWordCount; i++) {
                            messager += packet.getWord(i).getContent();
                            messager += " ";
                        }


                        commandHandler->eventOnDataReceived(messager);
                        qDebug() << messager;

                        commandHandler->exec(command, packet, lastSentPacket);
                    }
                }
            }

            // BIG MISTAKE HERE: packetSendQueue.erase(it);
            for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
                if (it->getSequenceNum() == packet.getSequenceNum()) {
                    packetSendQueue.erase(it);
                    break;
                }
            }
        }
    } else if (packet.getWordCount() > 0) {
        QString command(packet.getWord(0).getContent());
        QString message;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            message += packet.getWord(i).getContent();
            message += " ";
        }

        commandHandler->eventOnDataReceived(message);
        commandHandler->exec(command, packet, FrostbiteRconPacket());
    }
}

PlayerList FrostbiteConnection::getPlayerList()
{
    return playerList;
}
