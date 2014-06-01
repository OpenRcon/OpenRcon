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
#include "BFBC2.h"
#include "BFBC2CommandHandler.h"
#include "BFBC2LevelDictionary.h"

#include "ServerEntry.h"

BFBC2::BFBC2(ServerEntry *serverEntry) :
    FrostbiteGame(serverEntry),
    con(new FrostbiteConnection(this)),
    commandHandler(new BFBC2CommandHandler(con)),
    authenticated(false)
{
    con->hostConnect(serverEntry->host, serverEntry->port);

    versionMap.insert(571287, "R21");
    versionMap.insert(581637, "R22");
    versionMap.insert(584642, "R23");
    versionMap.insert(593485, "R24");
    versionMap.insert(602833, "R25");
    versionMap.insert(609063, "R26");
    versionMap.insert(617877, "R27");
    versionMap.insert(621775, "R28");
    versionMap.insert(638140, "R30");
    versionMap.insert(720174, "R32");
    versionMap.insert(851434, "R34");

    // Connection
    connect(con, &Connection::onConnected, this, &BFBC2::onConnected);

    // Commands
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(const QByteArray&)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (BFBC2::*)(const QByteArray&)>(&BFBC2::onLoginHashedCommand));
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this,           static_cast<void (BFBC2::*)(bool)>(&BFBC2::onLoginHashedCommand));
    connect(commandHandler, &FrostbiteCommandHandler::onVersionCommand, this, &BFBC2::onVersionCommand);
}

BFBC2::~BFBC2()
{
    delete con;
}

void BFBC2::onConnected()
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand();
    }
}

void BFBC2::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        commandHandler->sendLoginHashedCommand(salt, serverEntry->password);
    }
}

void BFBC2::onLoginHashedCommand(bool auth)
{
    authenticated = auth;
}

void BFBC2::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(build);

    if (type != "BFBC2") {
        con->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

bool BFBC2::isAuthenticated()
{
    return authenticated;
}

void BFBC2::slotCommandMapListListRounds(QStringList ml)
{
    mapListU = ml;
}

void BFBC2::sendSayMessage(const QString &msg, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg).arg(group));
    } else {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(msg));
    }
}

void BFBC2::sendYellMessage(const QString &message, int duration, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(group));
    } else {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
    }
}

void BFBC2::killPlayer(const QString &player)
{
    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BFBC2::kickPlayer(const QString &player, const QString &reason)
{
    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player).arg(reason));
}

void BFBC2::banPlayer(const QString &type, const QString &id, const QString &timeout, const QString &reason)
{
    // banList.add <id-type, id, timeout, reason> Add player/IP/GUID to ban list for a certain amount of time
    con->sendCommand(QString("\"banList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(type, id, timeout, reason));
}

void BFBC2::unbanPlayer(const QString &type, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(type, id));
}

void BFBC2::movePlayer(const QString &player, const QString &teamId, const QString &squadId, const QString &fk)
{
    if (!player.isEmpty()) {
        con->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player, teamId, squadId, fk));
    }
}

QString BFBC2::getMapName(const QString &engineName, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelEntry level = BFBC2LevelDictionary::getLevel(engineName); // TODO: Mind the gamemode?

        return level.name;
    }

    return QString();
}

QPixmap BFBC2::getMapImage(const QString &engineName, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelEntry level = BFBC2LevelDictionary::getLevel(engineName); // TODO: Mind the gamemode?

        return level.image();
    }

    return QPixmap();
}
