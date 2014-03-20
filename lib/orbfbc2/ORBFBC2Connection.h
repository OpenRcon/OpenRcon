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

#ifndef ORBFBC2Connection_H
#define ORBFBC2Connection_H

#include "ORBFBC2_global.h"

#include <QObject>
#include <QCryptographicHash>
#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>

#include "ORBFBC2Commands.h"
#include "ORBFBC2RconPacket.h"

#define MIN_PACKET_SIZE 12

class OR_BFBC2_EXPORT ORBFBC2Connection : public QObject
{
    Q_OBJECT

public:
    explicit ORBFBC2Connection(QTcpSocket *tcpSocket);
    ~ORBFBC2Connection();

    enum { PacketReadingHeader = 0, PacketReadingData = 1 };

public slots:
    void hostConnect(const QString &host, int& port);
    void hostDisconnect();
    void send(const ORBFBC2RconPacket &packet, bool response = false);
    void sendCommand(const QString &cmd);
    bool isAuthenticated();

private:
    ORBFBC2Commands *com;
    QTcpSocket *tcpSocket;
    int packetReadState;
    char lastHeader[MIN_PACKET_SIZE];
    bool auth;
    QByteArray loginSalt;
    QVector<ORBFBC2RconPacket> packetSendQueue;
    quint32 nextPacketSeq;

    void handlePacket(const ORBFBC2RconPacket &packet);

private slots:
    void tcpSocketReadyRead();
    void tcpSocketStateChanged(QAbstractSocket::SocketState state);
    void authenticateSlot();

signals:
    void connected();
    void disconnected();

    void outPacket(const QString &packet);
    void inPacket(const QString &packet);

};

#endif // BFBC2Connection_H
