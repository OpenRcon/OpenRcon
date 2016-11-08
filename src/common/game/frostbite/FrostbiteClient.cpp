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
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FrostbiteClient.h"
#include "ServerEntry.h"
#include "GameType.h"

FrostbiteClient::FrostbiteClient(ServerEntry *serverEntry, FrostbiteCommandHandler *commandHandler, QObject *parent) :
    Client(serverEntry, parent),
    connection(new FrostbiteConnection(commandHandler, this)),
    commandHandler(commandHandler)
{
    connectToHost();

    // Connection
    connect(connection,     &Connection::onConnected,                      this, &FrostbiteClient::onConnected);
    connect(connection,     &Connection::onDisconnected,                   this, &FrostbiteClient::onDisconnected);

    // Commands
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(const QByteArray&)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (FrostbiteClient::*)(const QByteArray&)>(&FrostbiteClient::onLoginHashedCommand));
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (FrostbiteClient::*)(bool)>(&FrostbiteClient::onLoginHashedCommand));
    connect(commandHandler, &FrostbiteCommandHandler::onVersionCommand,    this, &FrostbiteClient::onVersionCommand);
}

FrostbiteClient::~FrostbiteClient()
{
    disconnectFromHost();
}

void FrostbiteClient::connectToHost()
{
    connection->hostConnect(serverEntry);
}

void FrostbiteClient::disconnectFromHost()
{
    connection->hostDisconnect();
}

QString FrostbiteClient::getVersionFromBuild(int build) const
{
    return versionMap.contains(build) ? versionMap.value(build) : QString::number(build);
}

void FrostbiteClient::onConnected()
{
    commandHandler->sendVersionCommand();
    commandHandler->sendServerInfoCommand();

    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void FrostbiteClient::onDisconnected()
{
    setAuthenticated(false);
}

void FrostbiteClient::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->getPassword());
    }
}

void FrostbiteClient::onLoginHashedCommand(bool authenticated)
{
    setAuthenticated(authenticated);
}

void FrostbiteClient::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(build);

    if (GameType::fromString(type) != serverEntry->getGameType()) {
        disconnectFromHost();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}
