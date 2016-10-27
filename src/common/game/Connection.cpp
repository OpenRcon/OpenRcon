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

#include <QAbstractSocket>
#include <QString>
#include <QHostAddress>
#include <QTcpSocket>

#include "Connection.h"
#include "ServerEntry.h"

Connection::Connection(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this))
{
    qDebug() << "Connection created.";

    connect(socket, &QAbstractSocket::connected,                                                                   this, &Connection::connected);
    connect(socket, &QAbstractSocket::disconnected,                                                                this, &Connection::disconnected);
    connect(socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &Connection::displayError);
}

Connection::~Connection()
{

}

void Connection::hostConnect(ServerEntry *serverEntry)
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        socket->connectToHost(serverEntry->getHost(), serverEntry->getPort());
    } else {
        qDebug() << tr("Already connected to %1:%2.").arg(serverEntry->getHost()).arg(serverEntry->getPort());
    }
}

void Connection::hostDisconnect()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    } else {
        qDebug() << tr("Could not disconnect, there is no open socket to disconnect.");
    }
}

bool Connection::isConnected()
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void Connection::connected()
{
    emit(onConnected(socket));

    qDebug() << tr("Connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort());
}

void Connection::disconnected()
{
    emit(onDisconnected(socket));

    qDebug() << tr("Disconnected from %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort());
}

void Connection::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        //QMessageBox::warning(nullptr, tr("Error"), tr("The remote host closed the connection."));
        qDebug() << tr("Remote host closed the connection: %1.").arg(socket->errorString());
        break;
    case QAbstractSocket::HostNotFoundError:
        //QMessageBox::warning(nullptr, tr("Error"), tr("The host address was not found."));
        qDebug() << tr("Host not found: %1.").arg(socket->errorString());
        break;
    case QAbstractSocket::ConnectionRefusedError:
        //QMessageBox::warning(nullptr, tr("Error"), tr("The connection was refused by the peer (or timed out)."));
        qDebug() << tr("Connection refused: %1.").arg(socket->errorString());
        break;
    default:
        //QMessageBox::information(nullptr, tr("Error"), tr("The following error occurred: %1.").arg(socket->errorString()));
        qDebug() << tr("Unknown error: %1.").arg(socket->errorString());
    }
}

/* These events is triggered everytime the client sends or receives data. */
void Connection::responseDataSent(const QString &request)
{
    if (!request.isEmpty()) {
         emit (onDataSent(request));
    }
}

void Connection::responseDataReceived(const QString &response)
{
    if (!response.isEmpty()) {
        emit (onDataReceived(response));
    }
}
