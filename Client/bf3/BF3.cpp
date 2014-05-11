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

#include "BF3.h"

BF3::BF3(ServerEntry *serverEntry) :
    FrostbiteGame(serverEntry),
    con(new BF3Connection(this)),
    commandHandler(con->commandHandler()),
    authenticated(false)
{
    con = new BF3Connection(this);
    con->hostConnect(serverEntry->host, serverEntry->port);

    levelDictionary = new BF3LevelDictionary(this);

    versionMap.insert(872601, "OB-E");
    versionMap.insert(873274, "OB-F");
    versionMap.insert(879322, "R3");
    versionMap.insert(879793, "R4");
    versionMap.insert(881071, "R5");
    versionMap.insert(882210, "R6");
    versionMap.insert(883137, "R7");
    versionMap.insert(883971, "R8");
    versionMap.insert(886605, "R9");
    versionMap.insert(888890, "R10");
    versionMap.insert(892188, "R11");
    versionMap.insert(893642, "R12");
    versionMap.insert(894307, "R13");
    versionMap.insert(894565, "R14");
    versionMap.insert(895012, "R15");
    versionMap.insert(895921, "R16");
    versionMap.insert(896646, "R17");
    versionMap.insert(903227, "R19");
    versionMap.insert(926998, "R20");
    versionMap.insert(933688, "R21");
    versionMap.insert(940924, "R22");
    versionMap.insert(948577, "R23");
    versionMap.insert(951336, "R24");
    versionMap.insert(951364, "R25");
    versionMap.insert(964189, "R26");
    versionMap.insert(972386, "R27");
    versionMap.insert(981883, "R28");
    versionMap.insert(1000930, "R29");
    versionMap.insert(1009356, "R30");
    versionMap.insert(1014305, "R31");
    versionMap.insert(1028652, "R32");
    versionMap.insert(1043704, "R32 1/2");
    versionMap.insert(1055290, "R33");
    versionMap.insert(1066226, "R34");
    versionMap.insert(1075133, "R34log");
    versionMap.insert(1097264, "R35");
    versionMap.insert(1125745, "R36");
    versionMap.insert(1139617, "R37");
    versionMap.insert(1149977, "R38");

    // Connection
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(commandHandler, SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));
    connect(commandHandler, SIGNAL(onLoginHashedCommand(bool)), this, SLOT(onLoginHashedCommand(bool)));
    connect(commandHandler, SIGNAL(onVersionCommand(const QString&, int)), this, SLOT(onVersionCommand(const QString&, int)));
}

BF3::~BF3()
{
    //delete con;
    //delete levelDictionary;
}

void BF3::onConnected()
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void BF3::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->password);
    }
}

void BF3::onLoginHashedCommand(bool auth)
{
    authenticated = auth;
}

void BF3::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(build);

    if (type != "BF3") {
        con->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

bool BF3::isAuthenticated()
{
    return authenticated;
}
