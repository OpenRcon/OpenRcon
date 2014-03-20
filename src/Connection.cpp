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

    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(tcpSocketConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(tcpSocketDisconnected()));
}

Connection::~Connection()
{
    delete tcpSocket;
}

void Connection::hostConnect(const QString &host, const int &port)
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket->connectToHost(host, port);
        qDebug() << QString("Connection started: %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
    } else {
        if (tcpSocket) {
            qDebug() << QString("Already connected to %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
        } else {
            qDebug() << "ERROR: Connection::hostConnect() tcpSocket = 0";
        }
    }
}

void Connection::hostDisconnect()
{
    if (tcpSocket) {
        if (tcpSocket->isOpen()) {
            tcpSocket->disconnectFromHost();
        } else {
            qDebug() << "Could not disconnect, because there was no open socket.";
        }
    } else {
        qDebug() << "ERROR: Connection::hostConnect() tcpSocket = 0";
    }
}

void Connection::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(0, tr("Error"), tr("The remote host closed the connection."));
        qDebug() << QString("socketError = RemoteHostClosedError (%1)").arg(tcpSocket->errorString());
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::warning(0, tr("Error"), tr("The host address was not found."));
        qDebug() << QString("socketError = HostNotFoundError (%1)").arg(tcpSocket->errorString());
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::warning(0, tr("Error"), tr("The connection was refused by the peer (or timed out)."));
        qDebug() << QString("socketError = ConnectionRefusedError (%1)").arg(tcpSocket->errorString());
        break;
    default:
        QMessageBox::information(0, tr("Error"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
        qDebug() << QString("socketError = Unknown (%1)").arg(tcpSocket->errorString());
    }
}

void Connection::tcpSocketConnected()
{
    qDebug() << QString("Connected to %1:%2").arg(tcpSocket->peerAddress().toString(), int(tcpSocket->peerPort()));
}

void Connection::tcpSocketDisconnected()
{
    qDebug() << QString("Disconnected from host %1:%2").arg(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
}
