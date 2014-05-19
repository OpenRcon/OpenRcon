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

    commandList.append("login.plainText ");
    commandList.append("login.hashed");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("listPlayers");
    commandList.append("eventsEnabled");
    commandList.append("help");
    commandList.append("admin.runscript");
    commandList.append("punkBuster.pb_sv_command");
    commandList.append("serverInfo");
    commandList.append("admin.yell");
    commandList.append("admin.say");
    commandList.append("admin.runNextRound");
    commandList.append("admin.restartRound");
    commandList.append("admin.endRound");
    commandList.append("admin.runNextLevel");
    commandList.append("admin.restartMap");
    commandList.append("admin.currentLevel");
    commandList.append("mapList.nextLevelIndex");
    commandList.append("admin.supportedMaps");
    commandList.append("admin.setPlaylist");
    commandList.append("admin.getPlaylist");
    commandList.append("admin.getPlaylists");
    commandList.append("admin.kickPlayer");
    commandList.append("admin.listPlayers");
    commandList.append("admin.movePlayer");
    commandList.append("admin.killPlayer");
    commandList.append("vars.textChatModerationMode");
    commandList.append("vars.textChatSpamTriggerCount");
    commandList.append("vars.textChatSpamDetectionTime");
    commandList.append("vars.textChatSpamCoolDownTime");
    commandList.append("textChatModerationList.load");
    commandList.append("textChatModerationList.save");
    commandList.append("textChatModerationList.add ");
    commandList.append("textChatModerationList.remove");
    commandList.append("textChatModerationList.clear");
    commandList.append("textChatModerationList.list");
    commandList.append("banList.load");
    commandList.append("banList.save");
    commandList.append("banList.add");
    commandList.append("banList.remove");
    commandList.append("banList.clear");
    commandList.append("banList.list");
    commandList.append("reservedSlots.load");
    commandList.append("reservedSlots.save");
    commandList.append("reservedSlots.addPlayer");
    commandList.append("reservedSlots.removePlayer");
    commandList.append("reservedSlots.clear");
    commandList.append("reservedSlots.list");
    commandList.append("mapList.load");
    commandList.append("mapList.save");
    commandList.append("mapList.list");
    commandList.append("mapList.clear");
    commandList.append("mapList.remove");
    commandList.append("mapList.append");
    commandList.append("mapList.insert");
    commandList.append("vars.serverName");
    commandList.append("vars.adminPassword");
    commandList.append("vars.gamePassword");
    commandList.append("vars.punkBuster");
    commandList.append("vars.hardCore");
    commandList.append("vars.ranked");
    commandList.append("vars.rankLimit");
    commandList.append("vars.teamBalance");
    commandList.append("vars.friendlyFire");
    commandList.append("vars.currentPlayerLimit");
    commandList.append("vars.maxPlayerLimit");
    commandList.append("vars.playerLimit");
    commandList.append("vars.bannerUrl");
    commandList.append("vars.serverDescription");
    commandList.append("vars.killCam");
    commandList.append("vars.miniMap");
    commandList.append("vars.crossHair");
    commandList.append("vars.3dSpotting");
    commandList.append("vars.miniMapSpotting");
    commandList.append("vars.thirdPersonVehicleCameras");
    commandList.append("vars.teamKillCountForKick");
    commandList.append("vars.teamKillValueForKick");
    commandList.append("vars.teamKillValueIncrease");
    commandList.append("vars.teamKillValueDecreasePerSecond");
    commandList.append("vars.idleTimeout");
    commandList.append("vars.profanityFilter");
    commandList.append("levelVars.set");
    commandList.append("levelVars.get");
    commandList.append("levelVars.evaluate");
    commandList.append("levelVars.clear");
    commandList.append("levelVars.list");

    // Connection
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(commandHandler, SIGNAL(onLoginHashedCommand(QByteArray)), this, SLOT(onLoginHashedCommand(QByteArray)));
    connect(commandHandler, SIGNAL(onLoginHashedCommand(bool)), this, SLOT(onLoginHashedCommand(bool)));
    connect(commandHandler, SIGNAL(onVersionCommand(QString, int)), this, SLOT(onVersionCommand(QString, int)));
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
