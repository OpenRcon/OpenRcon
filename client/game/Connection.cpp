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

#include <QHostAddress>
#include <QMessageBox>

#include "Connection.h"

#include "Game.h"
#include "ServerEntry.h"

Connection::Connection(QAbstractSocket *socket, QObject *parent) : QObject(parent), socket(socket)
{
    connect(socket, &QAbstractSocket::connected,                                                                   this, &Connection::connected);
    connect(socket, &QAbstractSocket::disconnected,                                                                this, &Connection::disconnected);
    connect(socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &Connection::displayError);
}

Connection::~Connection()
{

}

void Connection::hostConnect(const QString &host, int port)
{
    if (!socket->isOpen()) {
        socket->connectToHost(host, port);
    } else {
        qDebug() << tr("Already connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    }
}

void Connection::hostDisconnect()
{
    if (socket->isOpen()) {
        socket->disconnectFromHost();
    } else {
        qDebug() << tr("Could not disconnect, because there was no open sockets to close.");
    }
}

void Connection::hostReconnect()
{
    // Store current connected host ip and port.
    QString host = socket->peerAddress().toString();
    int port = socket->peerPort();

    // Disconnect from host and reconnect.
    socket->disconnectFromHost();
    socket->connectToHost(host, port);
}

void Connection::connected()
{
    qDebug() << tr("Connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort());

    emit(onConnected());
}

void Connection::disconnected()
{
    qDebug() << tr("Disconnected from %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort());

    emit(onDisconnected());
}

void Connection::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(nullptr, tr("Error"), tr("The remote host closed the connection."));
        qDebug() << tr("Remote host closed the connection: %1.").arg(socket->errorString());
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(nullptr, tr("Error"), tr("The host address was not found."));
        qDebug() << tr("Host not found: %1.").arg(socket->errorString());
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(nullptr, tr("Error"), tr("The connection was refused by the peer (or timed out)."));
        qDebug() << tr("Connection refused: %1.").arg(socket->errorString());
        break;
    default:
        QMessageBox::information(nullptr, tr("Error"), tr("The following error occurred: %1.").arg(socket->errorString()));
        qDebug() << tr("Unknown error: %1.").arg(socket->errorString());
    }
}

/* These events is triggered everytime the client sends or receives data. */
void Connection::responseDataSentEvent(const QString &request)
{
    emit (onDataSentEvent(request));
}

void Connection::responseDataReceivedEvent(const QString &response)
{
    emit (onDataReceivedEvent(response));
}
