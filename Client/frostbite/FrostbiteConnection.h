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

#ifndef FROSTBITECONNECTION_H
#define FROSTBITECONNECTION_H

#include "Connection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteCommandHandler.h"

#include "BFBC2CommandHandler.h"

#define MIN_PACKET_SIZE 12

class FrostbiteConnection : public Connection
{
    Q_OBJECT

public:
    explicit FrostbiteConnection(FrostbiteCommandHandler *commandHandler, QObject *parent = 0);
    ~FrostbiteConnection();

    FrostbiteCommandHandler *commandHandler;

public slots:
    void hostConnect(const QString &host, const int &port);
    void sendPacket(const FrostbiteRconPacket &packet, bool response = false);
    void sendCommand(const QString &cmd);
    bool isAuthenticated();
    PlayerList getPlayerList();

private:
    int packetReadState;
    char lastHeader[MIN_PACKET_SIZE];
    bool auth;
    QByteArray loginSalt;
    QString gameName;
    QVector<FrostbiteRconPacket> packetSendQueue;
    quint32 nextPacketSeq;
    PlayerList playerList;

    void handlePacket(const FrostbiteRconPacket &packet);

    enum {
        PacketReadingHeader = 0,
        PacketReadingData = 1
    };

private slots:
    void readyRead();
    void authenticateSlot();

};

#endif // FROSTBITECONNECTION_H
