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

#include "FrostbiteConnection.h"
#include "BF4.h"
#include "BF4CommandHandler.h"
#include "BF4LevelDictionary.h"

#include "ServerEntry.h"

BF4::BF4(ServerEntry *serverEntry) :
    FrostbiteGame(serverEntry),
    con(new FrostbiteConnection(this)),
    commandHandler(new BF4CommandHandler(con)),
    authenticated(false)
{
    con->hostConnect(serverEntry->host, serverEntry->port);

    versionMap.insert(70517, "OB-R2");
    versionMap.insert(72879, "OB-R3");
    versionMap.insert(77582, "OB-R4");
    versionMap.insert(87884, "R4");
    versionMap.insert(88031, "R5");
    versionMap.insert(88058, "R6");
    versionMap.insert(88472, "R7");
    versionMap.insert(89702, "R8");
    versionMap.insert(90165, "R9");
    versionMap.insert(90519, "R10");
    versionMap.insert(91697, "R11");
    versionMap.insert(93111, "R12");
    versionMap.insert(94318, "R13");
    versionMap.insert(95851, "R14");
    versionMap.insert(96245, "R15");
    versionMap.insert(97870, "R16");
    versionMap.insert(99392, "R17");
    versionMap.insert(101684, "R18");
    versionMap.insert(102560, "R19");
    versionMap.insert(103064, "R20");
    versionMap.insert(106318, "R21");
    versionMap.insert(106533, "R22");
    versionMap.insert(107145, "R23");
    versionMap.insert(107436, "R24");
    versionMap.insert(108751, "R25");
    versionMap.insert(109758, "R26");
    versionMap.insert(111118, "R27");
    versionMap.insert(112943, "R28");
    versionMap.insert(114240, "R29");
    versionMap.insert(115397, "R30");
    versionMap.insert(117719, "R31");
    versionMap.insert(120511, "R32");
    versionMap.insert(125871, "R33");
    versionMap.insert(126936, "R34");

    // Connection
    connect(con, &Connection::onConnected, this, &BF4::onConnected);

    // Commands
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(const QByteArray&)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (BF4::*)(const QByteArray&)>(&BF4::onLoginHashedCommand));
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (BF4::*)(bool)>(&BF4::onLoginHashedCommand));
    connect(commandHandler, &BF4CommandHandler::onVersionCommand, this, &BF4::onVersionCommand);
}

BF4::~BF4()
{
    delete con;
}

void BF4::onConnected()
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void BF4::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->password);
    }
}

void BF4::onLoginHashedCommand(bool auth)
{
    authenticated = auth;
}

void BF4::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(build);

    if (type != "BF4") {
        con->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

bool BF4::isAuthenticated()
{
    return authenticated;
}
