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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Connection.h"

Connection::Connection(QObject *parent)
{
    Q_UNUSED(parent);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Connection::~Connection()
{
    delete tcpSocket;
}

void Connection::hostConnect(const QString &host, const int &port)
{
    if (!tcpSocket->isOpen()) {
        tcpSocket->connectToHost(host, port);
    } else {
        qDebug() << tr("Already connected to %1:%2.").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
    }
}

void Connection::hostDisconnect()
{
    if (tcpSocket->isOpen()) {
        tcpSocket->disconnectFromHost();
    } else {
        qDebug() << tr("Could not disconnect, because there was no open sockets to close.");
    }
}

void Connection::connected()
{
    qDebug() << tr("Connected to %1:%2.").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());

    emit(onConnected());
}

void Connection::disconnected()
{
    qDebug() << tr("Disconnected from %1:%2.").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());

    emit(onDisconnected());
}

void Connection::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(0, tr("Error"), tr("The remote host closed the connection."));
        qDebug() << tr("Remote host closed the connection: %1.").arg(tcpSocket->errorString());
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(0, tr("Error"), tr("The host address was not found."));
        qDebug() << tr("Host not found: %1.").arg(tcpSocket->errorString());
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(0, tr("Error"), tr("The connection was refused by the peer (or timed out)."));
        qDebug() << tr("Connection refused: %1.").arg(tcpSocket->errorString());
        break;
    default:
        QMessageBox::information(0, tr("Error"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
        qDebug() << tr("Unknown error: %1.").arg(tcpSocket->errorString());
    }
}
