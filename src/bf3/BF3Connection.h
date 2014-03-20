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

#ifndef BF3CONNECTION_H
#define BF3CONNECTION_H

#include "Connection.h"

#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QAbstractSocket>
#include <QDebug>
#include <QStringList>
#include <QCryptographicHash>

#define MIN_PACKET_SIZE 12

typedef QMap<QString, QString> PlayerItem;
typedef QVector<PlayerItem> PlayerList;
    
class BF3Connection : public Connection {
    Q_OBJECT

public:
    BF3Connection(QObject *parent = 0);
    ~BF3Connection();

public slots:
    void hostConnect(const QString &host, const int &port);
    void sendCommand(const QString &cmd);
    void authenticate();
    
    bool authenticated();
    
    const PlayerItem &getPlayerList();


private:
    // sbrohy: TODO: Left the 'private' keyword here because I'm new to Qt and not sure whether it affects the 'signals' keyword below.

    QString digestSeed; // MD5 digest seed
    QString digestSeedPassword;	// Digest seed and password in hexadecimal

    bool m_auth;

    PlayerItem playerList;

private slots:
    void tcpSocketReadyRead();
    void tcpSocketStateChanged(QAbstractSocket::SocketState state);
    void getDigestSeed(const QString &data); // Get digest seed

signals:
    void logMessage(const QString &type, const QString &msg);

};

#endif // BF3CONNECTION_H
