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

#include "BFBC2Connection.h"

BFBC2Connection::BFBC2Connection(QObject *parent) : FrostbiteConnection(parent)
{

}

BFBC2Connection::~BFBC2Connection()
{

}

void BFBC2Connection::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse events.
    if (request == "player.onJoin") {
        parsePlayerJoinEvent(packet);
    } else if (request == "player.onAuthenticated") {
        parsePlayerAuthenticatedEvent(packet);
    } else if (request == "player.onLeave") {
        parsePlayerLeaveEvent(packet);
    } else if (request == "player.onSpawn") {
        parsePlayerSpawnEvent(packet);
    } else if (request == "player.onKill") {
        parsePlayerKillEvent(packet);
    } else if (request == "player.onChat") {
        parsePlayerChatEvent(packet);
    } else if (request == "player.onKicked") {
        parsePlayerKickedEvent(packet);
    } else if (request == "player.onSquadChange") {
        parsePlayerSquadChangeEvent(packet);
    } else if (request == "player.onTeamChange") {
        parsePlayerTeamChangeEvent(packet);
    } else if (request == "punkBuster.onMessage") {
        parsePunkBusterMessageEvent(packet);
    } else if (request == "punkBuster.onVersion") {
        parsePunkBusterVersionEvent(packet);
    } else if (request == "server.onLoadingLevel") {
        parseServerLoadingLevelEvent(packet);
    } else if (request == "server.onLevelStarted") {
        parseServerLevelStartedEvent(packet);
    } else if (request == "server.onRoundOver") {
        parseServerRoundOverEvent(packet);
    } else if (request == "server.onRoundOverPlayers") {
        parseServerRoundOverPlayersEvent(packet);
    } else if (request == "server.onRoundOverTeamScores") {
        parseServerRoundOverTeamScoresEvent(packet);
    }

    // Parse commands.
    if (request == "login.plainText") {
        parseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        parseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "logout") {
        parseLogoutCommand(packet);
    } else if (request == "quit") {
        parseQuitCommand(packet);
    } else if (request == "version") {
        parseVersionCommand(packet);
    } else if (request == "listPlayers") {
        parseListPlayersCommand(packet);
    } else if (request == "eventsEnabled") {
        parseEventsEnabledCommand(packet);
    } else if (request == "help") {
        parseHelpCommand(packet);
    } else if (request == "admin.runscript") {
        parseAdminRunScriptCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        parsePunkBusterPbSvCommand(packet);
    } else if (request == "serverInfo") {
        parseServerInfoCommand(packet);
    } else if (request == "admin.yell") {
        parseAdminYellCommand(packet);
    } else if (request == "admin.say") {
        parseAdminSayCommand(packet);
    } else if (request == "admin.runNextRound") {
        parseAdminRunNextRoundCommand(packet);
    } else if (request == "admin.restartRound") {
        parseAdminRestartRoundCommand(packet);
    } else if (request == "admin.endRound") {
        parseAdminEndRoundCommand(packet);
    } else if (request == "admin.runNextLevel") {
        parseAdminRunNextLevelCommand(packet);
    } else if (request == "admin.restartMap") {
        parseAdminRestartMapCommand(packet);
    } else if (request == "admin.currentLevel") {
        parseAdminCurrentLevelCommand(packet);
    } else if (request == "mapList.nextLevelIndex") {
        parseMapListNextLevelIndexCommand(packet);
    } else if (request == "admin.supportedMaps") {
        parseAdminSupportedMapsCommand(packet);
    } else if (request == "admin.setPlaylist") {
        parseAdminSetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylist") {
        parseAdminGetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylists") {
        parseAdminGetPlaylistsCommand(packet);
    } else if (request == "admin.kickPlayer") {
        parseAdminKickPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        parseAdminListPlayersCommand(packet);
    } else if (request == "admin.movePlayer") {
        parseAdminMovePlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        parseAdminKillPlayerCommand(packet);
    } else if (request == "vars.textChatModerationMode") {
        parseVarsTextChatModerationModeCommand(packet);
    } else if (request == "vars.textChatSpamTriggerCount") {
        parseVarsTextChatSpamTriggerCountCommand(packet);
    } else if (request == "vars.textChatSpamDetectionTime") {
        parseVarsTextChatSpamDetectionTimeCommand(packet);
    } else if (request == "vars.textChatSpamCoolDownTime") {
        parseVarsTextChatSpamCoolDownTimeCommand(packet);
    } else if (request == "textChatModerationList.load") {
        parseTextChatModerationListLoadCommand(packet);
    } else if (request == "textChatModerationList.save") {
        parseTextChatModerationListSaveCommand(packet);
    } else if (request == "textChatModerationList.add") {
        parseTextChatModerationListAddCommand(packet);
    } else if (request == "textChatModerationList.remove") {
        parseTextChatModerationListRemoveCommand(packet);
    } else if (request == "textChatModerationList.clear") {
        parseTextChatModerationListClearCommand(packet);
    } else if (request == "textChatModerationList.list") {
        parseTextChatModerationListListCommand(packet);
    } else if (request == "banList.load") {
        parseBanListLoadCommand(packet);
    } else if (request == "banList.save") {
        parseBanListSaveCommand(packet);
    } else if (request == "banList.add") {
        parseBanListAddCommand(packet);
    } else if (request == "banList.remove") {
        parseBanListRemoveCommand(packet);
    } else if (request == "banList.clear") {
        parseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        parseBanListListCommand(packet);
    } else if (request == "reservedSlots.load") {
        parseReservedSlotsLoadCommand(packet);
    } else if (request == "reservedSlots.save") {
        parseReservedSlotsSaveCommand(packet);
    } else if (request == "reservedSlots.addPlayer") {
        parseReservedSlotsAddPlayerCommand(packet);
    } else if (request == "reservedSlots.removePlayer") {
        parseReservedSlotsRemovePlayerCommand(packet);
    } else if (request == "reservedSlots.clear") {
        parseReservedSlotsClearCommand(packet);
    } else if (request == "reservedSlots.list") {
        parseReservedSlotsListCommand(packet);
    } else if (request == "mapList.load") {
        parseMapListLoadCommand(packet);
    } else if (request == "mapList.save") {
        parseMapListSaveCommand(packet);
    } else if (request == "mapList.list") {
        parseMapListListCommand(packet, lastSentPacket);
    } else if (request == "mapList.clear") {
        parseMapListClearCommand(packet);
    } else if (request == "mapList.remove") {
        parseMapListRemoveCommand(packet);
    } else if (request == "mapList.append") {
        parseMapListAppendCommand(packet);
    } else if (request == "maplist mapList.insert") {
        parseMaplistInsertCommand(packet);
    } else if (request == "vars.serverName") {
        parseVarsServerNameCommand(packet);
    } else if (request == "vars.adminPassword") {
        parseVarsAdminPasswordCommand(packet);
    } else if (request == "vars.gamePassword") {
        parseVarsGamePasswordCommand(packet);
    } else if (request == "vars.punkBuster") {
        parseVarsPunkBusterCommand(packet);
    } else if (request == "vars.hardCore") {
        parseVarsHardCoreCommand(packet);
    } else if (request == "vars.ranked") {
        parseVarsRankedCommand(packet);
    } else if (request == "vars.rankLimit") {
        parseVarsRankLimitCommand(packet);
    } else if (request == "vars.teamBalance") {
        parseVarsTeamBalanceCommand(packet);
    } else if (request == "vars.friendlyFire") {
        parseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.currentPlayerLimit") {
        parseVarsCurrentPlayerLimitCommand(packet);
    } else if (request == "vars.maxPlayerLimit") {
        parseVarsMaxPlayerLimitCommand(packet);
    } else if (request == "vars.playerLimit") {
        parseVarsPlayerLimitCommand(packet);
    } else if (request == "vars.bannerUrl") {
        parseVarsBannerUrlCommand(packet);
    } else if (request == "vars.serverDescription") {
        parseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.killCam") {
        parseVarsKillCamCommand(packet);
    } else if (request == "vars.miniMap") {
        parseVarsMiniMapCommand(packet);
    } else if (request == "vars.crossHair") {
        parseVarsCrossHairCommand(packet);
    } else if (request == "vars.3dSpotting") {
        parseVars3dSpottingCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        parseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.thirdPersonVehicleCameras") {
        parseVarsThirdPersonVehicleCamerasCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        parseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        parseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        parseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        parseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.idleTimeout") {
        parseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.profanityFilter") {
        parseVarsProfanityFilterCommand(packet);
    } else if (request == "LevelVars.set") {
        parseLevelVarsSetCommand(packet);
    } else if (request == "LevelVars.get") {
        parseLevelVarsGetCommand(packet);
    } else if (request == "LevelVars.evaluate") {
        parseLevelVarsEvaluateCommand(packet);
    } else if (request == "LevelVars.clear") {
        parseLevelVarsClearCommand(packet);
    } else if (request == "LevelVars.list") {
        parseLevelVarsListCommand(packet);
    }
}

/* Events */
void BFBC2Connection::parsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerJoinEvent(player));
}

void BFBC2Connection::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerAuthenticatedEvent(player, guid));
}

void BFBC2Connection::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BFBC2Connection::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit (onPlayerSpawnEvent(player, kit, weaponList));
}

void BFBC2Connection::parsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = FrostbiteUtils::toBool(packet.getWord(4).getContent());

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BFBC2Connection::parsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BFBC2Connection::parsePlayerKickedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit (onPlayerKickedEvent(player, reason));
}

void BFBC2Connection::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BFBC2Connection::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BFBC2Connection::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BFBC2Connection::parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet)
{
    QString version = packet.getWord(1).getContent();

    emit (onPunkBusterVersionEvent(version));
}

void BFBC2Connection::parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = toInt(packet.getWord(2).getContent());
    int roundsTotal = toInt(packet.getWord(3).getContent());

    emit (onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2Connection::parseServerLevelStartedEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onServerLevelStartedEvent());
}

void BFBC2Connection::parseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = toInt(packet.getWord(1).getContent());

    emit (onServerRoundOverEvent(winningTeamId));
}

void BFBC2Connection::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BFBC2Connection::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */
void BFBC2Connection::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(tr("You have successfully logged in.")));
    }
}

/* Misc */
void BFBC2Connection::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit (onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit (onLoginHashedCommand());
        }
    }
}

void BFBC2Connection::parseLogoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand(tr("You are now logged out.")));
    }
}

void BFBC2Connection::parseQuitCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand(tr("Disconnected.")));
    }
}

void BFBC2Connection::parseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BFBC2Connection::parseListPlayersCommand(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onListPlayersCommand());
    }
}

void BFBC2Connection::parseEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseHelpCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList helpList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            helpList.append(packet.getWord(i).getContent());
        }

        emit (onHelpCommand(helpList));
    }
}

void BFBC2Connection::parseAdminRunScriptCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

/* Query */
void BFBC2Connection::parseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList serverInfo;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            serverInfo.append(packet.getWord(i).getContent());
        }

        emit (onServerInfoCommand(serverInfo));
    }
}

void BFBC2Connection::parseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminRestartMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit (onMapListNextLevelIndexCommand(index));
    }
}

void BFBC2Connection::parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        PlayerList playerList;
        unsigned int parameterCount = QString(packet.getWord(1).getContent()).toUInt();
        unsigned int playerCount = QString(packet.getWord(2 + parameterCount).getContent()).toUInt();

        for (unsigned int i = 0; i < playerCount; i++) {
            PlayerListItem player;

            for (unsigned int j = 0; j < parameterCount; j++) {
                player.insert(packet.getWord(2 + j).getContent(), packet.getWord(2 + parameterCount + 1 + i * parameterCount + j).getContent());
            }

            playerList.append(player);
        }

        emit (onAdminListPlayersCommand(playerList));
    }
}

void BFBC2Connection::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit (onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2Connection::parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2Connection::parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2Connection::parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2Connection::parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseBanListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            banList.append(packet.getWord(i).getContent());
        }

        emit (onBanListListCommand(banList));
    }
}

void BFBC2Connection::parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseReservedSlotsListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList list;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListCommand(list));
    }
}

void BFBC2Connection::parseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i = i + 2) {
                mapList << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }

            //emit(onMapListListRoundsCommand(mapList));
        } else {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i++) {
                mapList.append(packet.getWord(i).getContent());
            }

            emit (onMapListListCommand(mapList));
        }
    }

}

void BFBC2Connection::parseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMapListAppendCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseMaplistInsertCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

void BFBC2Connection::parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsHardCoreCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsRankLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2Connection::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

void BFBC2Connection::parseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

void BFBC2Connection::parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseLevelVarsSetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseLevelVarsGetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseLevelVarsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::parseLevelVarsListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
