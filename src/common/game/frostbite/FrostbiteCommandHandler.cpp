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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCryptographicHash>

#include "FrostbiteCommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "PlayerSubset.h"
#include "TeamScores.h"
#include "Frostbite2ServerInfo.h"
#include "BF3ServerInfo.h"
#include "BF4ServerInfo.h"
#include "BF3CommandHandler.h"
#include "BF4CommandHandler.h"
#include "BanListEntry.h"
#include "MapListEntry.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(QObject *parent) :
    CommandHandler(parent)
{

}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

void FrostbiteCommandHandler::setConnection(FrostbiteConnection *connection)
{
    this->connection = connection;
}

bool FrostbiteCommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (FrostbiteCommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */
        { "player.onAuthenticated",                 &FrostbiteCommandHandler::parsePlayerAuthenticatedEvent },
        { "player.onJoin",                          &FrostbiteCommandHandler::parsePlayerJoinEvent },
        { "player.onLeave",                         &FrostbiteCommandHandler::parsePlayerLeaveEvent },
        { "player.onSpawn",                         &FrostbiteCommandHandler::parsePlayerSpawnEvent },
        { "player.onKill",                          &FrostbiteCommandHandler::parsePlayerKillEvent },
        { "player.onChat",                          &FrostbiteCommandHandler::parsePlayerChatEvent },
        { "player.onSquadChange",                   &FrostbiteCommandHandler::parsePlayerSquadChangeEvent },
        { "player.onTeamChange",                    &FrostbiteCommandHandler::parsePlayerTeamChangeEvent },
        { "punkBuster.onMessage",                   &FrostbiteCommandHandler::parsePunkBusterMessageEvent },
        { "server.onRoundOver",                     &FrostbiteCommandHandler::parseServerRoundOverEvent },
        { "server.onRoundOverPlayers",              &FrostbiteCommandHandler::parseServerRoundOverPlayersEvent },
        { "server.onRoundOverTeamScores",           &FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent },

        /* Commands */
        // Misc
        { "login.plainText",                        &FrostbiteCommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",                           &FrostbiteCommandHandler::parseLoginHashedCommand },
        { "serverInfo",                             &FrostbiteCommandHandler::parseServerInfoCommand },
        { "logout",                                 &FrostbiteCommandHandler::parseLogoutCommand },
        { "quit",                                   &FrostbiteCommandHandler::parseQuitCommand },
        { "version",                                &FrostbiteCommandHandler::parseVersionCommand },
        { "listPlayers",                            nullptr /*&FrostbiteCommandHandler::parseListPlayersCommand*/}, // TODO: Move this from BF3CommandHandler and BF4CommandHandler.

        // Admin
        { "admin.kickPlayer",                       nullptr /*&FrostbiteCommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                       nullptr /*&FrostbiteCommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.listPlayers",                      nullptr /*&FrostbiteCommandHandler::parseAdminListPlayersCommand*/ },
        { "admin.movePlayer",                       nullptr /*&FrostbiteCommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.say",                              nullptr /*&FrostbiteCommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                             nullptr /*&FrostbiteCommandHandler::parseAdminYellCommand*/ },

        // Banning
        { "banList.add",                            nullptr /*&FrostbiteCommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                          nullptr /*&FrostbiteCommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                           &FrostbiteCommandHandler::parseBanListListCommand },
        { "banList.load",                           nullptr /*&FrostbiteCommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                         nullptr /*&FrostbiteCommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                           nullptr /*&FrostbiteCommandHandler::parseBanListSaveCommand*/ },

        // Maplist
        { "mapList.clear",                          nullptr /*&FrostbiteCommandHandler::parseMapListClearCommand*/ },
        { "mapList.list",                           &FrostbiteCommandHandler::parseMapListListCommand },
        { "mapList.load",                           nullptr /*&FrostbiteCommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                         nullptr /*&FrostbiteCommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.save",                           nullptr /*&FrostbiteCommandHandler::parseMapListSaveCommand*/ },

        // Punkbuster
        { "punkBuster.pb_sv_command",               nullptr /*&FrostbiteCommandHandler::parsePunkBusterPbSvCommand*/ },

        // Reserved Slots

        // Variables
        { "vars.3dSpotting",                        &FrostbiteCommandHandler::parseVars3dSpottingCommand },
        { "vars.friendlyFire",                      &FrostbiteCommandHandler::parseVarsFriendlyFireCommand },
        { "vars.gamePassword",                      &FrostbiteCommandHandler::parseVarsGamePasswordCommand },
        { "vars.idleTimeout",                       &FrostbiteCommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.killCam",                           &FrostbiteCommandHandler::parseVarsKillCamCommand },
        { "vars.miniMap",                           &FrostbiteCommandHandler::parseVarsMiniMapCommand },
        { "vars.miniMapSpotting",                   &FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand },
        { "vars.serverDescription",                 &FrostbiteCommandHandler::parseVarsServerDescriptionCommand },
        { "vars.serverName",                        &FrostbiteCommandHandler::parseVarsServerNameCommand },
        { "vars.teamKillCountForKick",              &FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand },
        { "vars.teamKillValueDecreasePerSecond",    &FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },
        { "vars.teamKillValueForKick",              &FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand },
        { "vars.teamKillValueIncrease",             &FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand },
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return false;
}

/* Send commands */
// Misc
void FrostbiteCommandHandler::sendLoginPlainTextCommand(const QString &password)
{
    connection->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void FrostbiteCommandHandler::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        connection->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            connection->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void FrostbiteCommandHandler::sendServerInfoCommand()
{
    connection->sendCommand("serverInfo");
}

void FrostbiteCommandHandler::sendLogoutCommand()
{
    connection->sendCommand("logout");
}

void FrostbiteCommandHandler::sendQuitCommand()
{
    connection->sendCommand("quit");
}

void FrostbiteCommandHandler::sendVersionCommand()
{
    connection->sendCommand("version");
}

// Admin
void FrostbiteCommandHandler::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    connection->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void FrostbiteCommandHandler::sendAdminKillPlayerCommand(const QString &player)
{
    connection->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void FrostbiteCommandHandler::sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill)
{
    connection->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void FrostbiteCommandHandler::sendAdminSayCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (message.length() < 128) {
        if (parameter < 0) {
            connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(message, PlayerSubset::toString(playerSubset).toLower()));
        } else {
            connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(message, PlayerSubset::toString(playerSubset).toLower()).arg(parameter));
        }
    }
}

void FrostbiteCommandHandler::sendAdminYellCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    sendAdminYellCommand(message, 10, playerSubset, parameter);
}

void FrostbiteCommandHandler::sendAdminYellCommand(const QString &message, int duration, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (message.length() < 256) {
        if (parameter < 0) {
            connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset).toLower()));
        } else {
            connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset).toLower()).arg(parameter));
        }
    }
}

// Banning
void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    connection->sendCommand(QString("\"banList.add\" \"%1\" \"%2\" \"perm\" \"%4\"").arg(idType, id, reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutString = useRounds ? "rounds" : "seconds";
    timeoutString += " " + QString::number(timeout);

    connection->sendCommand(QString("\"banList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(idType, id, timeoutString, reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListClearCommand()
{
    connection->sendCommand("banList.clear");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListListCommand(int index)
{
    if (index < 0) {
        connection->sendCommand("banList.list");
    } else {
        connection->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void FrostbiteCommandHandler::sendBanListLoadCommand()
{
    connection->sendCommand("banList.load");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    connection->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListSaveCommand()
{
    connection->sendCommand("banList.save");
}

// Maplist
void FrostbiteCommandHandler::sendMapListClearCommand()
{
    connection->sendCommand("mapList.clear");
    sendMapListListCommand();
}

void FrostbiteCommandHandler::sendMapListListCommand(int index)
{
    if (index < 0) {
        connection->sendCommand("mapList.list");
    } else {
        connection->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void FrostbiteCommandHandler::sendMapListLoadCommand()
{
    connection->sendCommand("mapList.load");
    sendMapListListCommand();
}

void FrostbiteCommandHandler::sendMapListRemoveCommand(int index)
{
    connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
    sendMapListListCommand();
}

void FrostbiteCommandHandler::sendMapListSaveCommand()
{
    connection->sendCommand("mapList.save");
}

// Punkbuster
void FrostbiteCommandHandler::sendPunkBusterPbSvCommand(const QString &command)
{
    if (!command.isEmpty()) {
        connection->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
    }
}

// Reserved Slots

// Variables
void FrostbiteCommandHandler::sendVars3dSpottingCommand()
{
    connection->sendCommand("vars.3dSpotting");
}

void FrostbiteCommandHandler::sendVars3dSpottingCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void FrostbiteCommandHandler::sendVarsFriendlyFireCommand()
{
    connection->sendCommand("vars.friendlyFire");
}

void FrostbiteCommandHandler::sendVarsFriendlyFireCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void FrostbiteCommandHandler::sendVarsGamePasswordCommand(const QString &password)
{
    if (password == 0) {
        connection->sendCommand("vars.gamePassword");
    } else {
        connection->sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
}

void FrostbiteCommandHandler::sendVarsIdleTimeoutCommand(int seconds)
{
    if (seconds == -1) {
        connection->sendCommand("vars.idleTimeout");
    } else {
        connection->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void FrostbiteCommandHandler::sendVarsKillCamCommand()
{
    connection->sendCommand("vars.killCam");
}

void FrostbiteCommandHandler::sendVarsKillCamCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void FrostbiteCommandHandler::sendVarsMiniMapCommand()
{
    connection->sendCommand("vars.miniMap");
}

void FrostbiteCommandHandler::sendVarsMiniMapCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void FrostbiteCommandHandler::sendVarsMiniMapSpottingCommand()
{
    connection->sendCommand("vars.miniMapSpotting");
}

void FrostbiteCommandHandler::sendVarsMiniMapSpottingCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void FrostbiteCommandHandler::sendVarsServerDescriptionCommand(const QString &description)
{
    if (description == 0) {
        connection->sendCommand("vars.serverDescription");
    } else {
        connection->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void FrostbiteCommandHandler::sendVarsServerNameCommand(const QString &name)
{
    if (name == 0) {
        connection->sendCommand("vars.serverName");
    } else {
        connection->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void FrostbiteCommandHandler::sendVarsTeamKillCountForKickCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillCountForKick");
    } else {
        connection->sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void FrostbiteCommandHandler::sendVarsTeamKillValueDecreasePerSecondCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void FrostbiteCommandHandler::sendVarsTeamKillValueForKickCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueForKick");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void FrostbiteCommandHandler::sendVarsTeamKillValueIncreaseCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueIncrease");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

/* Parse events */
void FrostbiteCommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit(onPlayerAuthenticatedEvent(player));
}

void FrostbiteCommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit(onPlayerJoinEvent(player, guid));
}

void FrostbiteCommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit(onPlayerLeaveEvent(player, info));
}

void FrostbiteCommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

    emit(onPlayerSpawnEvent(player, teamId));
}

void FrostbiteCommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit(onPlayerKillEvent(killer, victim, weapon, headshot));
}

void FrostbiteCommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit(onPlayerChatEvent(player, message, target));
}

void FrostbiteCommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit(onPlayerSquadChangeEvent(player, teamId, squadId));
}

void FrostbiteCommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit(onPlayerTeamChangeEvent(player, teamId, squadId));
}

void FrostbiteCommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit(onPunkBusterMessageEvent(message));
}

void FrostbiteCommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit(onServerRoundOverEvent(winningTeamId));
}

void FrostbiteCommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit(onServerRoundOverPlayersEvent(playerInfo));
}

void FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit(onServerRoundOverTeamScoresEvent(teamScores));
}

/* Parse commands */
// Misc
void FrostbiteCommandHandler::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLoginPlainTextCommand(true));
    } else {
        emit(onLoginPlainTextCommand(false));
    }
}

void FrostbiteCommandHandler::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit(onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit(onLoginHashedCommand(true));
        } else { // if (response == "InvalidPasswordHash")
            emit(onLoginHashedCommand(false));
        }
    }
}

void FrostbiteCommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();
        int playerCount = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int maxPlayerCount = FrostbiteUtils::toInt(packet.getWord(3).getContent());
        QString gamemode = packet.getWord(4).getContent();
        QString currentMap = packet.getWord(5).getContent();
        int roundsPlayed = FrostbiteUtils::toInt(packet.getWord(6).getContent());
        int roundsTotal = FrostbiteUtils::toInt(packet.getWord(7).getContent());

        // Parsing team scores.
        int entries = FrostbiteUtils::toInt(packet.getWord(8).getContent());
        int entriesIndex = 9 + entries;
        QList<int> scoreList;

        for (int i = 9; i <= entriesIndex; i++) {
            scoreList.append(FrostbiteUtils::toInt(packet.getWord(i).getContent()));
        }

        int targetScore = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 1).getContent());
        TeamScores scores(scoreList, targetScore);

        bool ranked = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 2).getContent());
        bool punkBuster = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 3).getContent());
        bool hasGamePassword = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 4).getContent());
        int serverUpTime = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 5).getContent());
        int roundTime = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 6).getContent());
        QString gameIpAndPort = packet.getWord(entriesIndex + 7).getContent();
        QString punkBusterVersion = packet.getWord(entriesIndex + 8).getContent();
        bool joinQueueEnabled = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 9).getContent());
        QString region = packet.getWord(entriesIndex + 10).getContent();
        QString closestPingSite = packet.getWord(entriesIndex + 11).getContent();
        QString country = packet.getWord(entriesIndex + 12).getContent();

        Frostbite2ServerInfo serverInfo(serverName,
                                        playerCount,
                                        maxPlayerCount,
                                        gamemode,
                                        currentMap,
                                        roundsPlayed,
                                        roundsTotal,
                                        scores,
                                        ranked,
                                        punkBuster,
                                        hasGamePassword,
                                        serverUpTime,
                                        roundTime,
                                        gameIpAndPort,
                                        punkBusterVersion,
                                        joinQueueEnabled,
                                        region,
                                        closestPingSite,
                                        country);

        emit(onServerInfoCommand(serverInfo));

        // BF3 Only.
        if (dynamic_cast<BF3CommandHandler*>(this)) {
            bool matchMakingEnabled = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 13).getContent());

            BF3ServerInfo serverInfo(serverName,
                                     playerCount,
                                     maxPlayerCount,
                                     gamemode,
                                     currentMap,
                                     roundsPlayed,
                                     roundsTotal,
                                     scores,
                                     ranked,
                                     punkBuster,
                                     hasGamePassword,
                                     serverUpTime,
                                     roundTime,
                                     gameIpAndPort,
                                     punkBusterVersion,
                                     joinQueueEnabled,
                                     region,
                                     closestPingSite,
                                     country,
                                     matchMakingEnabled);

            emit(onServerInfoCommand(serverInfo));

        // BF4 Only.
        } else if (dynamic_cast<BF4CommandHandler*>(this)) {
            int blazePlayerCount = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 13).getContent());
            QString blazeGameState = packet.getWord(entriesIndex + 14).getContent();

            BF4ServerInfo serverInfo(serverName,
                                     playerCount,
                                     maxPlayerCount,
                                     gamemode,
                                     currentMap,
                                     roundsPlayed,
                                     roundsTotal,
                                     scores,
                                     ranked,
                                     punkBuster,
                                     hasGamePassword,
                                     serverUpTime,
                                     roundTime,
                                     gameIpAndPort,
                                     punkBusterVersion,
                                     joinQueueEnabled,
                                     region,
                                     closestPingSite,
                                     country,
                                     blazePlayerCount,
                                     blazeGameState);

            emit(onServerInfoCommand(serverInfo));
        }
    }
}

void FrostbiteCommandHandler::parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLogoutCommand());
    }
}

void FrostbiteCommandHandler::parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onQuitCommand());
    }
}

void FrostbiteCommandHandler::parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit(onVersionCommand(type, build));
    }
}

// Admin

// Banning
void FrostbiteCommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QList<BanListEntry> banList;

        for (int i = 1; i < packet.getWordCount(); i += 6) {
            QString banIdType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = FrostbiteUtils::toInt(packet.getWord(i + 3).getContent());
            int rounds = FrostbiteUtils::toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(banIdType, id, banType, seconds, rounds, reason));
        }

        emit(onBanListListCommand(banList));
    }
}

// Maplist
void FrostbiteCommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QList<MapListEntry> mapList;
        int maps = QString(packet.getWord(1).getContent()).toInt();
        int parameters = QString(packet.getWord(2).getContent()).toInt();

        for (int i = 0; i < maps; i++) {
            QString level;
            QString gameMode;
            int rounds = 0;

            for (int j = 0; j < parameters; j++) {
                QString data = packet.getWord(3 + (i * parameters) + j).getContent();

                switch (j) {
                    case 0:
                        level = data;
                        break;
                    case 1:
                        gameMode = data;
                        break;
                    case 2:
                        rounds = data.toInt();
                        break;
                }
            }

            mapList.append(MapListEntry(level, gameMode, rounds));
        }

        emit(onMapListListCommand(mapList));
    }
}

// Punkbuster

// Reserved Slots

// Variables
void FrostbiteCommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit(onVars3dSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit(onVarsFriendlyFireCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit(onVarsGamePasswordCommand(password));
    }
}

void FrostbiteCommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit(onVarsIdleTimeoutCommand(seconds));
    }
}

void FrostbiteCommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit(onVarsKillCamCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit(onVarsMiniMapCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit(onVarsMiniMapSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit(onVarsServerDescriptionCommand(description));
    }
}

void FrostbiteCommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit(onVarsServerNameCommand(name));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit(onVarsTeamKillCountForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit(onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit(onVarsTeamKillValueForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit(onVarsTeamKillValueIncreaseCommand(count));
    }
}
