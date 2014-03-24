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

#include "BFBC2Connection.h"

BFBC2Connection::BFBC2Connection(QObject *parent) : FrostbiteConnection(commandHandler, parent), commandHandler(new BFBC2CommandHandler(this))
{
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}

BFBC2Connection::~BFBC2Connection()
{
    delete commandHandler;
}

void BFBC2Connection::stateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::ConnectedState:
        commandHandler->onLogMessage(0, "Connected.");
        commandHandler->onStartConnection();
        break;
    case QAbstractSocket::UnconnectedState:
        commandHandler->onLogMessage(0, "Disconnected.");
        break;
    default:
        break;
    }
}
