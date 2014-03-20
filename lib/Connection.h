/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

class Connection : public QObject
{
    Q_OBJECT

public:
    explicit Connection(QObject *parent = 0);
    virtual ~Connection();

    QTcpSocket *tcpSocket;

public slots:
    virtual void hostConnect(const QString &host, const int &port);
    virtual void hostDisconnect();

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void tcpSocketConnected();
    void tcpSocketDisconnected();

};

#endif // CONNECTION_H
