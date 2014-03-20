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

#include "BFBC2Connection.h"

BFBC2Connection::BFBC2Connection(QObject *parent) : Connection(parent), packetReadState(PacketReadingHeader), auth(false), nextPacketSeq(0)
{
    mCommandSignals = new BFBC2CommandSignals(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpSocketReadyRead()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(tcpSocketStateChanged(QAbstractSocket::SocketState)));
}

BFBC2Connection::~BFBC2Connection()
{
    delete tcpSocket;
    delete mCommandSignals;
}

BFBC2CommandSignals *BFBC2Connection::commandSignals()
{
    return mCommandSignals;
}

void BFBC2Connection::hostConnect(const QString &host, const int &port)
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        packetSendQueue.clear();
        packetReadState = PacketReadingHeader;
        nextPacketSeq = 0;
        auth = false;

        tcpSocket->connectToHost(host, port);

        qDebug() << QString("Connection started: %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
    } else {
        if (tcpSocket) {
            qDebug() << QString("Already connected to %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
        } else {
            qDebug() << "ERROR: Connection::hostConnect tcpSocket = 0";
        }
    }
}

void BFBC2Connection::tcpSocketStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << QString("tcpSocket state changed: %1").arg(state);

    switch (state) {
    case QAbstractSocket::ConnectedState:
        mCommandSignals->signalLogMessage("info", "Connected.");
        mCommandSignals->signalStartConnection();
        break;
    case QAbstractSocket::UnconnectedState:
        mCommandSignals->signalLogMessage("info", "Disconnected.");
        break;
    default:
        break;
    }
}

void BFBC2Connection::authenticateSlot()
{
    auth = true;
}

void BFBC2Connection::send(const BFBC2RconPacket &packet, bool response)
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

void BFBC2Connection::sendCommand(const QString &cmd)
{
    if (!cmd.isEmpty()) {
        BFBC2RconPacket packet(BFBC2RconPacket::ServerOrigin, BFBC2RconPacket::Request, nextPacketSeq);
        QStringList cmdList;
        cmdList = cmd.split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "");
        for (int i = 0; i < cmdList.size(); i++) {
            packet.packWord(BFBC2RconWord(cmdList.at(i).toUtf8().constData()));
        }
        send(packet);
        nextPacketSeq++;
    }
}

bool BFBC2Connection::isAuthenticated()
{
    return auth;
}

void BFBC2Connection::tcpSocketReadyRead()
{
    qDebug() << "Data ready.";
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
                    char * data = new char[len];
                    memcpy(data, lastHeader, MIN_PACKET_SIZE);
                    if (tcpSocket->read(data + MIN_PACKET_SIZE, len - MIN_PACKET_SIZE) == len - MIN_PACKET_SIZE) {
                        QDataStream pstream(QByteArray(data, len));
                        BFBC2RconPacket packet;
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

void BFBC2Connection::handlePacket(const BFBC2RconPacket &packet)
{
    qDebug() << QString("We have %1 words in this packet:").arg(packet.getWordCount());

    if (packet.isResponse()) {
        QVector<BFBC2RconPacket>::iterator it;

        for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
            if (it->getSequenceNum() == packet.getSequenceNum()) {
                break;
            }
        }

        if (it != packetSendQueue.end()) {
            const BFBC2RconPacket& lastSentPacket = *it;

            if (lastSentPacket.getSequenceNum() == packet.getSequenceNum()) {

                if (lastSentPacket.getWordCount() > 0) {
                    QString command(lastSentPacket.getWord(0).getContent());

                    if (packet.getWordCount() > 0) {
                        BFBC2CommandWarper commandWarper = BFBC2CommandWarper(command, mCommandSignals, packet, lastSentPacket, players);
                        quint32 lastPacketWordCount= lastSentPacket.getWordCount();
                        QString messages = command + " ";
                        for (quint32 i = 1; i < lastPacketWordCount; i++) {
                            messages += lastSentPacket.getWord(i).getContent();
                            messages += " ";
                        }
                        mCommandSignals->signalLogMessage("server_send", tr("%1").arg(messages));
                        QString messager;
                        quint32 packetWordCount = packet.getWordCount();
                        for (quint32 i = 0; i < packetWordCount; i++) {
                            messager += packet.getWord(i).getContent();
                            messager += " ";
                        }
                        mCommandSignals->signalLogMessage("server_receive", tr("%1").arg(messager));
                        commandWarper.exec();
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
        quint32 packetWordCount = packet.getWordCount();
        for (quint32 i = 0; i < packetWordCount; i++) {
            message += packet.getWord(i).getContent();
            message += " ";
        }
        mCommandSignals->signalLogMessage("server_receive",tr("%1").arg(message));

        BFBC2CommandWarper commandWarper = BFBC2CommandWarper(command, mCommandSignals, packet, BFBC2RconPacket(), players);
        commandWarper.exec();
    }
}

const PlayerList& BFBC2Connection::getPlayerList()
{
    return players;
}
