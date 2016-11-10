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
#include "BanIdType.h"
#include "BanType.h"
#include "BF3ServerInfo.h"
#include "BF4ServerInfo.h"
#include "BF3CommandHandler.h"
#include "BF4CommandHandler.h"
#include "BF4PlayerEntry.h"
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
        { "listPlayers",                            &FrostbiteCommandHandler::parseListPlayersCommand },

        // Admin
        { "admin.kickPlayer",                       nullptr /*&FrostbiteCommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                       nullptr /*&FrostbiteCommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.listPlayers",                      &FrostbiteCommandHandler::parseAdminListPlayersCommand },
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
    QString command;

    if (salt.isNull() && password.isEmpty()) {
        command = "login.hashed";
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            command = QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData());
        }
    }

    connection->sendCommand(command);
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

void FrostbiteCommandHandler::sendListPlayersCommand(const PlayerSubsetEnum &playerSubset)
{
    connection->sendCommand(QString("\"listPlayers\" \"%1\"").arg(PlayerSubset::toString(playerSubset).toLower()));
}

// Admin
void FrostbiteCommandHandler::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    QString command;

    if (reason.isEmpty()) {
        command = QString("\"admin.kickPlayer\" \"%1\"").arg(player);
    } else {
        command = QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendAdminKillPlayerCommand(const QString &player)
{
    connection->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void FrostbiteCommandHandler::sendAdminListPlayersCommand(const PlayerSubsetEnum &playerSubset)
{
    connection->sendCommand(QString("\"admin.listPlayers\" \"%1\"").arg(PlayerSubset::toString(playerSubset).toLower()));
}

void FrostbiteCommandHandler::sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill)
{
    connection->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void FrostbiteCommandHandler::sendAdminSayCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (message.length() < 128) {
        QString command;

        if (parameter < 0) {
            command = QString("\"admin.say\" \"%1\" \"%2\"").arg(message, PlayerSubset::toString(playerSubset).toLower());
        } else {
            command = QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(message, PlayerSubset::toString(playerSubset).toLower()).arg(parameter);
        }

        connection->sendCommand(command);
    }
}

void FrostbiteCommandHandler::sendAdminYellCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    sendAdminYellCommand(message, 10, playerSubset, parameter);
}

void FrostbiteCommandHandler::sendAdminYellCommand(const QString &message, int duration, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (message.length() < 256) {
        QString command;

        if (parameter < 0) {
            command = QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset).toLower());
        } else {
            command = QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset).toLower()).arg(parameter);
        }

        connection->sendCommand(command);
    }
}

// Banning
void FrostbiteCommandHandler::sendBanListAddCommand(const BanIdTypeEnum &banIdType, const QString &banId, const BanTypeEnum &banType, const QString &reason, int timeout)
{
    QString command;
    QString banTypeString;

    switch (banType) {
    case BanTypeEnum::Rounds:
    case BanTypeEnum::Seconds:
        banTypeString = QString("\"%1\" \"%2\"").arg(BanType::toString(banType).toLower(), QString::number(timeout));
        break;
    default:
        banTypeString = BanType::toString(banType).toLower();
        break;
    }

    if (reason.isEmpty()) {
        command = QString("\"banList.add\" \"%1\" \"%2\" %3").arg(BanIdType::toString(banIdType).toLower(), banId, banTypeString);
    } else {
        command = QString("\"banList.add\" \"%1\" \"%2\" %3 \"%4\"").arg(BanIdType::toString(banIdType).toLower(), banId, banTypeString, reason);
    }

    connection->sendCommand(command);
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListClearCommand()
{
    connection->sendCommand("banList.clear");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListListCommand(int index)
{
    QString command;

    if (index < 0) {
        command = "banList.list";
    } else {
        command = QString("\"banList.list\" \"%1\"").arg(index);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendBanListLoadCommand()
{
    connection->sendCommand("banList.load");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListRemoveCommand(const BanIdTypeEnum &banIdType, const QString &banId)
{
    connection->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(BanIdType::toString(banIdType).toLower(), banId));
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
    QString command;

    if (index < 0) {
        command = "mapList.list";
    } else {
        command = QString("\"mapList.list\" \"%1\"").arg(index);
    }

    connection->sendCommand(command);
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
    QString command;

    if (password.isEmpty()) {
        command = "vars.gamePassword";
    } else {
        command = QString("\"vars.gamePassword\" \"%1\"").arg(password);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsIdleTimeoutCommand(int seconds)
{
    QString command;

    if (seconds < 0) {
        command = "vars.idleTimeout";
    } else {
        command = QString("\"vars.idleTimeout\" \"%1\"").arg(seconds);
    }

    connection->sendCommand(command);
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
    QString command;

    if (description.isEmpty()) {
        command = "vars.serverDescription";
    } else {
        command = QString("\"vars.serverDescription\" \"%1\"").arg(description);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsServerNameCommand(const QString &name)
{
    QString command;

    if (name.isEmpty()) {
        command = "vars.serverName";
    } else {
        command = QString("\"vars.serverName\" \"%1\"").arg(name);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsTeamKillCountForKickCommand(int count)
{
    QString command;

    if (count < 0) {
        command = "vars.teamKillCountForKick";
    } else {
        command = QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsTeamKillValueDecreasePerSecondCommand(int count)
{
    QString command;

    if (count < 0) {
        command = "vars.teamKillValueDecreasePerSecond";
    } else {
        command = QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsTeamKillValueForKickCommand(int count)
{
    QString command;

    if (count < 0) {
        command = "vars.teamKillValueForKick";
    } else {
        command = QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count);
    }

    connection->sendCommand(command);
}

void FrostbiteCommandHandler::sendVarsTeamKillValueIncreaseCommand(int count)
{
    QString command;

    if (count < 0) {
        command = "vars.teamKillValueIncrease";
    } else {
        command = QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count);
    }

    connection->sendCommand(command);
}

/* Parse events */
void FrostbiteCommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();

        emit (onPlayerAuthenticatedEvent(player));
    }
}

void FrostbiteCommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        QString guid = packet.getWord(2).getContent();

        emit (onPlayerJoinEvent(player, guid));
    }
}

void FrostbiteCommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        QString info = packet.getWord(2).getContent();

        emit (onPlayerLeaveEvent(player, info));
    }
}

void FrostbiteCommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onPlayerSpawnEvent(player, teamId));
    }
}

void FrostbiteCommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString killer = packet.getWord(1).getContent();
        QString victim = packet.getWord(2).getContent();
        QString weapon = packet.getWord(3).getContent();
        bool headshot = packet.getWord(4).getContent();

        emit (onPlayerKillEvent(killer, victim, weapon, headshot));
    }
}

void FrostbiteCommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        QString message = packet.getWord(2).getContent();
        QString target = packet.getWord(3).getContent();

        emit (onPlayerChatEvent(player, message, target));
    }
}

void FrostbiteCommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

        emit (onPlayerSquadChangeEvent(player, teamId, squadId));
    }
}

void FrostbiteCommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString player = packet.getWord(1).getContent();
        int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

        emit (onPlayerTeamChangeEvent(player, teamId, squadId));
    }
}

void FrostbiteCommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString message = packet.getWord(1).getContent();

        emit (onPunkBusterMessageEvent(message));
    }
}

void FrostbiteCommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        int winningTeamId = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onServerRoundOverEvent(winningTeamId));
    }
}

void FrostbiteCommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0)  {
        QString playerInfo = packet.getWord(1).getContent();

        emit (onServerRoundOverPlayersEvent(playerInfo));
    }
}

void FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() > 0) {
        QString teamScores = packet.getWord(1).getContent();

        emit (onServerRoundOverTeamScoresEvent(teamScores));
    }
}

/* Parse commands */
// Misc
void FrostbiteCommandHandler::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(true));
    } else {
        emit (onLoginPlainTextCommand(false));
    }
}

void FrostbiteCommandHandler::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit (onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit (onLoginHashedCommand(true));
        } else { // if (response == "InvalidPasswordHash")
            emit (onLoginHashedCommand(false));
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

        emit (onServerInfoCommand(serverInfo));

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

            emit (onServerInfoCommand(serverInfo));

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

            emit (onServerInfoCommand(serverInfo));
        }
    }
}

void FrostbiteCommandHandler::parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand());
    }
}

void FrostbiteCommandHandler::parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand());
    }
}

void FrostbiteCommandHandler::parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void FrostbiteCommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    parsePlayerList(packet, lastSentPacket);
}

// Admin
void FrostbiteCommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    parsePlayerList(packet, lastSentPacket);
}

// Banning
void FrostbiteCommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QList<BanListEntry> banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            BanIdTypeEnum banIdType = BanIdType::fromString(packet.getWord(i).getContent());
            QString id = packet.getWord(i + 1).getContent();
            BanTypeEnum banType = BanType::fromString(packet.getWord(i + 2).getContent());
            int seconds = FrostbiteUtils::toInt(packet.getWord(i + 3).getContent());
            int rounds = FrostbiteUtils::toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(banIdType, id, banType, seconds, rounds, reason));
        }

        emit (onBanListListCommand(banList));
    }
}

// Maplist
void FrostbiteCommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
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

        emit (onMapListListCommand(mapList));
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

        emit (onVars3dSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onVarsGamePasswordCommand(password));
    }
}

void FrostbiteCommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(seconds));
    }
}

void FrostbiteCommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(description));
    }
}

void FrostbiteCommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(name));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillCountForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueIncreaseCommand(count));
    }
}

void FrostbiteCommandHandler::parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();
    QList<FrostbitePlayerEntry> playerList;
    QList<Frostbite2PlayerEntry> frostbite2PlayerList;
    QList<BF4PlayerEntry> bf4PlayerList;

    Frostbite2CommandHandler *frostbite2CommandHandler = dynamic_cast<Frostbite2CommandHandler*>(this);
    BF4CommandHandler *bf4CommandHandler = dynamic_cast<BF4CommandHandler*>(this);

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int parameters = QString(packet.getWord(1).getContent()).toInt();
        int players = QString(packet.getWord(2 + parameters).getContent()).toInt();

        for (int i = 0; i < players; i++) {
            QStringList list;

            for (int j = 0; j < parameters; j++) {
                list.append(packet.getWord(2 + parameters + 1 + i * parameters + j).getContent());
            }

            QString name = list.at(0);
            QString guid = list.at(1);
            int teamId = FrostbiteUtils::toInt(list.at(2));
            int squadId = FrostbiteUtils::toInt(list.at(3));
            int kills = FrostbiteUtils::toInt(list.at(4));
            int deaths = FrostbiteUtils::toInt(list.at(5));
            int score = FrostbiteUtils::toInt(list.at(6));


            // Frostbite2 Only.
            if (frostbite2CommandHandler) {
                int rank = FrostbiteUtils::toInt(list.at(7));

                frostbite2PlayerList.append(Frostbite2PlayerEntry(name, guid, teamId, squadId, kills, deaths, score, rank));

                // BF4 Only.
                if (bf4CommandHandler) {
                    int ping = FrostbiteUtils::toInt(list.at(8));
                    int type = FrostbiteUtils::toInt(list.at(9));

                    bf4PlayerList.append(BF4PlayerEntry(name, guid, teamId, squadId, kills, deaths, score, rank, ping, type));
                }
            }

            playerList.append(FrostbitePlayerEntry(name, guid, teamId, squadId, kills, deaths, score));
        }

        // Frostbite2 Only.
        if (frostbite2CommandHandler) {
            emit (onListPlayersCommand(frostbite2PlayerList));

            // BF4 Only.
            if (bf4CommandHandler) {
                emit (onListPlayersCommand(bf4PlayerList));
            }
        }

        emit (onListPlayersCommand(playerList));
    }
}
