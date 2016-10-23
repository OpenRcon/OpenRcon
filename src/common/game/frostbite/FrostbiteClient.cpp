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

#include "FrostbiteConnection.h"
#include "FrostbiteCommandHandler.h"
#include "ServerEntry.h"

#include "BF4Client.h"

FrostbiteClient::FrostbiteClient(ServerEntry *serverEntry, QObject *parent) :
    Client(serverEntry, parent),
    connection(new FrostbiteConnection(this))
{
    qDebug() << "FrostbiteClient created.";
}

void FrostbiteClient::connectToHost(Frostbite2CommandHandler *commandHandler)
{
    connection->hostConnect(serverEntry);

    // Connection
    connect(connection,     &Connection::onConnected, this, &FrostbiteClient::onConnected);

    // Commands
    connect(commandHandler, static_cast<void (Frostbite2CommandHandler::*)(const QByteArray&)>(&Frostbite2CommandHandler::onLoginHashedCommand),
            this,           static_cast<void (FrostbiteClient::*)(const QByteArray&)>(&FrostbiteClient::onLoginHashedCommand));
    connect(commandHandler, static_cast<void (Frostbite2CommandHandler::*)(bool)>(&Frostbite2CommandHandler::onLoginHashedCommand),
            this,           static_cast<void (FrostbiteClient::*)(bool)>(&FrostbiteClient::onLoginHashedCommand));
    connect(commandHandler, &Frostbite2CommandHandler::onVersionCommand,   this, &FrostbiteClient::onVersionCommand);
}

FrostbiteClient::~FrostbiteClient()
{

}

void FrostbiteClient::onConnected()
{
    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void FrostbiteClient::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->getPassword().isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->getPassword());
    }
}

void FrostbiteClient::onLoginHashedCommand(bool auth)
{
    qDebug() << "lolololololololololololololololololololol";

    setAuthenticated(auth);
}

void FrostbiteClient::onVersionCommand(const QString &type, int build)
{
    qDebug() << "lolololololololololololololololololololol";

    Q_UNUSED(build);

    qDebug() << "Server type is: " << type << " should be: " << GameTypeUtils::toString(serverEntry->getGameType());

    if (GameTypeUtils::fromString(type) != serverEntry->getGameType()) {
        connection->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

QString FrostbiteClient::getVersionFromBuild(int build)
{
    return versionMap.contains(build) ? versionMap.value(build) : QString::number(build);
}
