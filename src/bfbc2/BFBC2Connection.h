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

#ifndef BFBC2CONNECTION_H
#define BFBC2CONNECTION_H

#include "Connection.h"
#include "BFBC2Commands.h"
#include "BFBC2RconPacket.h"

#include <QObject>
#include <QCryptographicHash>
#include <QDataStream>
#include <QTextDocument>
#include <QVector>
#include <QMap>

#define MIN_PACKET_SIZE 12

typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;

class BFBC2Connection : public Connection
{
    Q_OBJECT

public:
    BFBC2Connection(QObject *parent = 0);
    ~BFBC2Connection();

    BFBC2CommandSignals *commandSignals();

    enum { PacketReadingHeader = 0, PacketReadingData = 1 };

public slots:
    void hostConnect(const QString &host, const int &port);
    void send(const BFBC2RconPacket &packet, bool response = false);
    void sendCommand(const QString &cmd);
    bool isAuthenticated();
    const PlayerList& getPlayerList();

private:
    BFBC2CommandSignals *mCommandSignals;

    void handlePacket(const BFBC2RconPacket &packet);
    int packetReadState;
    char lastHeader[MIN_PACKET_SIZE];
    bool auth;
    QByteArray loginSalt;
    QString gameName;
    QVector<BFBC2RconPacket> packetSendQueue;
    quint32 nextPacketSeq;
    PlayerList players;

private slots:
    void tcpSocketReadyRead();
    void tcpSocketStateChanged(QAbstractSocket::SocketState state);
    void authenticateSlot();

};

#endif // BFBC2CONNECTION_H
