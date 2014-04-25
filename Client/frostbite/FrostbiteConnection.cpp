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

FrostbiteConnection::FrostbiteConnection(FrostbiteCommandHandler *commandHandler, QObject *parent) : Connection(parent), commandHandler(commandHandler), packetReadState(PacketReadingHeader), nextPacketSequence(0)
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
    if (!tcpSocket->isOpen()) {
        clear();
        tcpSocket->connectToHost(host, port);
    } else {
        qDebug() << tr("Already connected to %1:%2.").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
    }
}

void FrostbiteConnection::sendPacket(const FrostbiteRconPacket &packet, bool response)
{
    QDataStream out(tcpSocket);
    out << packet;

    if (!response) {
        packetSendQueue.push_back(packet);
    }
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

            unsigned int seq, len, words;
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

void FrostbiteConnection::clear()
{
    packetSendQueue.clear();
    packetReadState = PacketReadingHeader;
    nextPacketSequence = 0;
}

void FrostbiteConnection::sendCommand(const QString &command)
{
    if (!command.isEmpty()) {
        FrostbiteRconPacket packet(FrostbiteRconPacket::ServerOrigin, FrostbiteRconPacket::Request, nextPacketSequence);
        QStringList cmdList;
        cmdList = command.split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "", Qt::CaseSensitive);

        for (int i = 0; i < cmdList.size(); i++) {
            packet.packWord(FrostbiteRconWord(cmdList.at(i).toLatin1().constData()));
        }

        sendPacket(packet);
        nextPacketSequence++;
    }
}

void FrostbiteConnection::handlePacket(const FrostbiteRconPacket &packet)
{
    qDebug() << tr("We have %1 words in this packet:").arg(packet.getWordCount());

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
                    QString request = lastSentPacket.getWord(0).getContent();

                    if (packet.getWordCount() > 0) {
                        QString messages = request + " ";

                        for (unsigned int i = 1; i < lastSentPacket.getWordCount(); i++) {
                            messages += lastSentPacket.getWord(i).getContent();
                            messages += " ";
                        }

                        commandHandler->responseDataSentEvent(messages);
                        qDebug() << messages;

                        QString messager;
                        unsigned int packetWordCount = packet.getWordCount();

                        for (unsigned int i = 0; i < packetWordCount; i++) {
                            messager += packet.getWord(i).getContent();
                            messager += " ";
                        }

                        commandHandler->responseDataReceivedEvent(messager);
                        commandHandler->parse(request, packet, lastSentPacket);
                        qDebug() << messager;
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
        QString request = packet.getWord(0).getContent();
        QString message;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            message += packet.getWord(i).getContent();
            message += " ";
        }

        commandHandler->responseDataReceivedEvent(message);
        commandHandler->parse(request, packet, FrostbiteRconPacket());
    }
}

FrostbiteCommandHandler* FrostbiteConnection::getCommandHandler()
{
    return commandHandler;
}
