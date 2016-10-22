/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include "FrostbiteGame.h"

#include "FrostbiteCommandHandler.h"
#include "ServerEntry.h"

FrostbiteGame::FrostbiteGame(ServerEntry *serverEntry) : GameWidget(serverEntry), connection(new FrostbiteConnection(this)), commandHandler(new FrostbiteCommandHandler(connection))
{
    connection->hostConnect(serverEntry);

    // Connection
    connect(connection,       &Connection::onConnected,                         this, &FrostbiteGame::onConnected);

    // Commands
    connect(commandHandler,   static_cast<void (FrostbiteCommandHandler::*)(const QByteArray&)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,             static_cast<void (FrostbiteGame::*)(const QByteArray&)>(&FrostbiteGame::onLoginHashedCommand));
    connect(commandHandler,   static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,             static_cast<void (FrostbiteGame::*)(bool)>(&FrostbiteGame::onLoginHashedCommand));
    connect(commandHandler,   &FrostbiteCommandHandler::onVersionCommand,   this, &FrostbiteGame::onVersionCommand);
}

FrostbiteGame::~FrostbiteGame()
{

}

void FrostbiteGame::onConnected()
{
    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void FrostbiteGame::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->getPassword());
    }
}

void FrostbiteGame::onLoginHashedCommand(bool auth)
{
    this->authenticated = auth;

    commandHandler->sendVersionCommand();
}

void FrostbiteGame::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(build);

    qDebug() << "Server type is: " << type << " should be: " << GameTypeUtils::toString(serverEntry->getGameType());

    if (GameTypeUtils::fromString(type) != serverEntry->getGameType()) {
        connection->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}
bool FrostbiteGame::isAuthenticated()
{
    return authenticated;
}

void FrostbiteGame::setAuthenticated(bool authenticated)
{
    this->authenticated = authenticated;
}

QString FrostbiteGame::getVersionFromBuild(int build)
{
    return versionMap.contains(build) ? versionMap.value(build) : QString::number(build);
}
