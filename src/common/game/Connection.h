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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QAbstractSocket>

class QString;

class ServerEntry;

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection(QObject *parent = nullptr);
    virtual ~Connection();

    virtual void hostConnect(ServerEntry *serverEntry) = 0;
    virtual void hostDisconnect();
    bool isConnected();

protected:
    void responseDataSent(const QString &request);
    void responseDataReceived(const QString &response);

    QAbstractSocket *socket;

private slots:
    void connected();
    void disconnected();
    void displayError(QAbstractSocket::SocketError socketError);

signals:
    void onConnected(QAbstractSocket *socket);
    void onDisconnected( QAbstractSocket *socket);
    void onDataSent(const QString &request);
    void onDataReceived(const QString &response);

};

#endif // CONNECTION_H
