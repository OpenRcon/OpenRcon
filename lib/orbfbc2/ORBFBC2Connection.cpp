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

#include "ORBFBC2Connection.h"

ORBFBC2Connection::ORBFBC2Connection(QTcpSocket *tcpSocket) : tcpSocket(tcpSocket), packetReadState(PacketReadingHeader), auth(false), nextPacketSeq(0)
{
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpSocketReadyRead()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(tcpSocketStateChanged(QAbstractSocket::SocketState)));
}

ORBFBC2Connection::~ORBFBC2Connection()
{
    delete tcpSocket;
}

void ORBFBC2Connection::hostConnect(const QString &host, int &port)
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        packetSendQueue.clear();
        packetReadState = PacketReadingHeader;
        nextPacketSeq = 0;
        auth = false;

        tcpSocket->connectToHost(host, port);

        qDebug() << QString("Connection started: %1:%2").arg(host, port);
    } else {
        if (tcpSocket) {
            qDebug() << QString("Already connected to %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
        } else {
            qDebug() << "ERROR: Connection::hostConnect tcpSocket = 0";
        }
    }
}

void ORBFBC2Connection::hostDisconnect()
{

}

void ORBFBC2Connection::tcpSocketStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << QString("tcpSocket state changed: %1").arg(state);

    switch (state) {
    case QAbstractSocket::ConnectedState:
        emit(connected());
        //mCommandSignals->signalLogMessage("Connected.");
        //mCommandSignals->signalStartConnection();
        break;
    case QAbstractSocket::UnconnectedState:
        emit(disconnected());
        //mCommandSignals->signalLogMessage("info", "Disconnected.");
        break;
    default:
        break;
    }
}

void ORBFBC2Connection::send(const ORBFBC2RconPacket &packet, bool response)
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

void ORBFBC2Connection::sendCommand(const QString &cmd)
{
    if (!cmd.isEmpty()) {
        ORBFBC2RconPacket packet(ORBFBC2RconPacket::ServerOrigin, ORBFBC2RconPacket::Request, nextPacketSeq);
        QStringList cmdList;
        cmdList = cmd.split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "");
        for (int i = 0; i < cmdList.size(); i++) {
            packet.packWord(ORBFBC2RconWord(cmdList.at(i).toUtf8().constData()));
        }
        send(packet);
        nextPacketSeq++;
    }
}

void ORBFBC2Connection::tcpSocketReadyRead()
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
                            // TODO: Fix pstream
                            //QDataStream pstream(QByteArray(data, len));
                            QDataStream pstream;
                            ORBFBC2RconPacket packet;
                            pstream >> packet;
                            qDebug() << QByteArray(data, len).toHex();
                            handlePacket(packet);
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

void ORBFBC2Connection::handlePacket(const ORBFBC2RconPacket &packet)
{
    qDebug() << QString("We have %1 words in this packet:").arg(packet.getWordCount());

    if (packet.isResponse()) {

        QVector<ORBFBC2RconPacket>::iterator it;
        for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
            if (it->getSequenceNum() == packet.getSequenceNum()) {
                break;
            }
        }

        if (it != packetSendQueue.end()) {
            const ORBFBC2RconPacket &lastSentPacket = *it;

            if (lastSentPacket.getSequenceNum() == packet.getSequenceNum()) {
                if (lastSentPacket.getWordCount() > 0) {

                    QString command(lastSentPacket.getWord(0).getContent());
                    if (packet.getWordCount() > 0) {
                        //mCommands = new BFBC2Commands(command, packet, lastSentPacket, this);
                        quint32 lastPacketWordCount= lastSentPacket.getWordCount();
                        QString messages = command + " ";

                        for (quint32 i = 1; i < lastPacketWordCount; i++) {
                            messages += lastSentPacket.getWord(i).getContent();
                            messages += " ";
                        }
                        emit(outPacket(messages));
                        //mCommandSignals->signalLogMessage("send", messages);

                        QString messager;
                        quint32 packetWordCount = packet.getWordCount();
                        for (quint32 i = 0; i < packetWordCount; i++) {
                            messager += packet.getWord(i).getContent();
                            messager += " ";
                        }
                        emit(inPacket(messager));
                        //mCommandSignals->signalLogMessage("recive", messager);
                        //commandWarper.exec();

                        com = new ORBFBC2Commands(command, packet, ORBFBC2RconPacket());
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
        for (quint32 i = 0; i <packetWordCount; i++) {
            message += packet.getWord(i).getContent();
            message += " ";
        }
        emit(inPacket(message));
        //mCommandSignals->signalLogMessage("recive", message);

        com = new ORBFBC2Commands(command, packet, ORBFBC2RconPacket());
    }
}

bool ORBFBC2Connection::isAuthenticated()
{
    return auth;
}

void ORBFBC2Connection::authenticateSlot()
{
    auth = true;
}
