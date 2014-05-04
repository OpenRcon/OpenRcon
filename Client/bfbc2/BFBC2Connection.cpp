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
        responsePlayerJoinEvent(packet);
    } else if (request == "player.onAuthenticated") {
        responsePlayerAuthenticatedEvent(packet);
    } else if (request == "player.onLeave") {
        responsePlayerLeaveEvent(packet);
    } else if (request == "player.onSpawn") {
        responsePlayerSpawnEvent(packet);
    } else if (request == "player.onKill") {
        responsePlayerKillEvent(packet);
    } else if (request == "player.onChat") {
        responsePlayerChatEvent(packet);
    } else if (request == "player.onKicked") {
        responsePlayerKickedEvent(packet);
    } else if (request == "player.onSquadChange") {
        responsePlayerSquadChangeEvent(packet);
    } else if (request == "player.onTeamChange") {
        responsePlayerTeamChangeEvent(packet);
    } else if (request == "punkBuster.onMessage") {
        responsePunkBusterMessageEvent(packet);
    } else if (request == "punkBuster.onVersion") {
        responsePunkBusterVersionEvent(packet);
    } else if (request == "server.onLoadingLevel") {
        responseServerLoadingLevelEvent(packet);
    } else if (request == "server.onLevelStarted") {
        responseServerLevelStartedEvent(packet);
    } else if (request == "server.onRoundOver") {
        responseServerRoundOverEvent(packet);
    } else if (request == "server.onRoundOverPlayers") {
        responseServerRoundOverPlayersEvent(packet);
    } else if (request == "server.onRoundOverTeamScores") {
        responseServerRoundOverTeamScoresEvent(packet);
    }

    // Parse commands.
    if (request == "login.plainText") {
        responseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        responseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "logout") {
        responseLogoutCommand(packet);
    } else if (request == "quit") {
        responseQuitCommand(packet);
    } else if (request == "version") {
        responseVersionCommand(packet);
    } else if (request == "listPlayers") {
        responseListPlayersCommand(packet);
    } else if (request == "eventsEnabled") {
        responseEventsEnabledCommand(packet);
    } else if (request == "help") {
        responseHelpCommand(packet);
    } else if (request == "admin.runscript") {
        responseAdminRunScriptCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        responsePunkBusterPbSvCommand(packet);
    } else if (request == "serverInfo") {
        responseServerInfoCommand(packet);
    } else if (request == "admin.yell") {
        responseAdminYellCommand(packet);
    } else if (request == "admin.say") {
        responseAdminSayCommand(packet);
    } else if (request == "admin.runNextRound") {
        responseAdminRunNextRoundCommand(packet);
    } else if (request == "admin.restartRound") {
        responseAdminRestartRoundCommand(packet);
    } else if (request == "admin.endRound") {
        responseAdminEndRoundCommand(packet);
    } else if (request == "admin.runNextLevel") {
        responseAdminRunNextLevelCommand(packet);
    } else if (request == "admin.restartMap") {
        responseAdminRestartMapCommand(packet);
    } else if (request == "admin.currentLevel") {
        responseAdminCurrentLevelCommand(packet);
    } else if (request == "mapList.nextLevelIndex") {
        responseMapListNextLevelIndexCommand(packet);
    } else if (request == "admin.supportedMaps") {
        responseAdminSupportedMapsCommand(packet);
    } else if (request == "admin.setPlaylist") {
        responseAdminSetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylist") {
        responseAdminGetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylists") {
        responseAdminGetPlaylistsCommand(packet);
    } else if (request == "admin.kickPlayer") {
        responseAdminKickPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        responseAdminListPlayersCommand(packet);
    } else if (request == "admin.movePlayer") {
        responseAdminMovePlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        responseAdminKillPlayerCommand(packet);
    } else if (request == "vars.textChatModerationMode") {
        responseVarsTextChatModerationModeCommand(packet);
    } else if (request == "vars.textChatSpamTriggerCount") {
        responseVarsTextChatSpamTriggerCountCommand(packet);
    } else if (request == "vars.textChatSpamDetectionTime") {
        responseVarsTextChatSpamDetectionTimeCommand(packet);
    } else if (request == "vars.textChatSpamCoolDownTime") {
        responseVarsTextChatSpamCoolDownTimeCommand(packet);
    } else if (request == "textChatModerationList.load") {
        responseTextChatModerationListLoadCommand(packet);
    } else if (request == "textChatModerationList.save") {
        responseTextChatModerationListSaveCommand(packet);
    } else if (request == "textChatModerationList.add") {
        responseTextChatModerationListAddCommand(packet);
    } else if (request == "textChatModerationList.remove") {
        responseTextChatModerationListRemoveCommand(packet);
    } else if (request == "textChatModerationList.clear") {
        responseTextChatModerationListClearCommand(packet);
    } else if (request == "textChatModerationList.list") {
        responseTextChatModerationListListCommand(packet);
    } else if (request == "banList.load") {
        responseBanListLoadCommand(packet);
    } else if (request == "banList.save") {
        responseBanListSaveCommand(packet);
    } else if (request == "banList.add") {
        responseBanListAddCommand(packet);
    } else if (request == "banList.remove") {
        responseBanListRemoveCommand(packet);
    } else if (request == "banList.clear") {
        responseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        responseBanListListCommand(packet);
    } else if (request == "reservedSlots.load") {
        responseReservedSlotsLoadCommand(packet);
    } else if (request == "reservedSlots.save") {
        responseReservedSlotsSaveCommand(packet);
    } else if (request == "reservedSlots.addPlayer") {
        responseReservedSlotsAddPlayerCommand(packet);
    } else if (request == "reservedSlots.removePlayer") {
        responseReservedSlotsRemovePlayerCommand(packet);
    } else if (request == "reservedSlots.clear") {
        responseReservedSlotsClearCommand(packet);
    } else if (request == "reservedSlots.list") {
        responseReservedSlotsListCommand(packet);
    } else if (request == "mapList.load") {
        responseMapListLoadCommand(packet);
    } else if (request == "mapList.save") {
        responseMapListSaveCommand(packet);
    } else if (request == "mapList.list") {
        responseMapListListCommand(packet, lastSentPacket);
    } else if (request == "mapList.clear") {
        responseMapListClearCommand(packet);
    } else if (request == "mapList.remove") {
        responseMapListRemoveCommand(packet);
    } else if (request == "mapList.append") {
        responseMapListAppendCommand(packet);
    } else if (request == "maplist mapList.insert") {
        responseMaplistInsertCommand(packet);
    } else if (request == "vars.serverName") {
        responseVarsServerNameCommand(packet);
    } else if (request == "vars.adminPassword") {
        responseVarsAdminPasswordCommand(packet);
    } else if (request == "vars.gamePassword") {
        responseVarsGamePasswordCommand(packet);
    } else if (request == "vars.punkBuster") {
        responseVarsPunkBusterCommand(packet);
    } else if (request == "vars.hardCore") {
        responseVarsHardCoreCommand(packet);
    } else if (request == "vars.ranked") {
        responseVarsRankedCommand(packet);
    } else if (request == "vars.rankLimit") {
        responseVarsRankLimitCommand(packet);
    } else if (request == "vars.teamBalance") {
        responseVarsTeamBalanceCommand(packet);
    } else if (request == "vars.friendlyFire") {
        responseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.currentPlayerLimit") {
        responseVarsCurrentPlayerLimitCommand(packet);
    } else if (request == "vars.maxPlayerLimit") {
        responseVarsMaxPlayerLimitCommand(packet);
    } else if (request == "vars.playerLimit") {
        responseVarsPlayerLimitCommand(packet);
    } else if (request == "vars.bannerUrl") {
        responseVarsBannerUrlCommand(packet);
    } else if (request == "vars.serverDescription") {
        responseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.killCam") {
        responseVarsKillCamCommand(packet);
    } else if (request == "vars.miniMap") {
        responseVarsMiniMapCommand(packet);
    } else if (request == "vars.crossHair") {
        responseVarsCrossHairCommand(packet);
    } else if (request == "vars.3dSpotting") {
        responseVars3dSpottingCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        responseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.thirdPersonVehicleCameras") {
        responseVarsThirdPersonVehicleCamerasCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        responseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        responseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        responseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        responseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.idleTimeout") {
        responseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.profanityFilter") {
        responseVarsProfanityFilterCommand(packet);
    } else if (request == "LevelVars.set") {
        responseLevelVarsSetCommand(packet);
    } else if (request == "LevelVars.get") {
        responseLevelVarsGetCommand(packet);
    } else if (request == "LevelVars.evaluate") {
        responseLevelVarsEvaluateCommand(packet);
    } else if (request == "LevelVars.clear") {
        responseLevelVarsClearCommand(packet);
    } else if (request == "LevelVars.list") {
        responseLevelVarsListCommand(packet);
    } else {
        responseUnknownCommand();
    }
}

/* Events */
void BFBC2Connection::responsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerJoinEvent(player));
}

void BFBC2Connection::responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerAuthenticatedEvent(player, guid));
}

void BFBC2Connection::responsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BFBC2Connection::responsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit (onPlayerSpawnEvent(player, kit, weaponList));
}

void BFBC2Connection::responsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = toBool(packet.getWord(4).getContent());

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BFBC2Connection::responsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BFBC2Connection::responsePlayerKickedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit (onPlayerKickedEvent(player, reason));
}

void BFBC2Connection::responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BFBC2Connection::responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BFBC2Connection::responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BFBC2Connection::responsePunkBusterVersionEvent(const FrostbiteRconPacket &packet)
{
    QString version = packet.getWord(1).getContent();

    emit (onPunkBusterVersionEvent(version));
}

void BFBC2Connection::responseServerLoadingLevelEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = toInt(packet.getWord(2).getContent());
    int roundsTotal = toInt(packet.getWord(3).getContent());

    emit (onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2Connection::responseServerLevelStartedEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onServerLevelStartedEvent());
}

void BFBC2Connection::responseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = toInt(packet.getWord(1).getContent());

    emit (onServerRoundOverEvent(winningTeamId));
}

void BFBC2Connection::responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BFBC2Connection::responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */
void BFBC2Connection::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(tr("You have successfully logged in.")));
    }
}

/* Misc */
void BFBC2Connection::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

void BFBC2Connection::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand(tr("You are now logged out.")));
    } else if (response == "InvalidArguments"){
        emit (onUnknownCommand());
    }
}

void BFBC2Connection::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand(tr("Disconnected.")));
    } else if (response == "InvalidArguments"){
        emit (onUnknownCommand());
    }
}

void BFBC2Connection::responseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString type = packet.getWord(1).getContent();
        int buildId = QString(packet.getWord(2).getContent()).toInt();
        QString version;

        QMap<int, QString> versionMap;
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

        if (versionMap.contains(buildId)) {
            version = versionMap.value(buildId);
        }

        emit (onVersionCommand(type, buildId, version));

        emit (onLogMessage(0, tr("<b>%1</b> server version: <b>%2</b>.").arg(type, version)));
    } else if (response == "InvalidArguments") {
        emit (onUnknownCommand());
    }
}

void BFBC2Connection::responseListPlayersCommand(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onListPlayersCommand());
    } else if (response == "InvalidArguments") {
        emit (onUnknownCommand());
    }
}

void BFBC2Connection::responseEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseHelpCommand(const FrostbiteRconPacket &packet)
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

void BFBC2Connection::responseAdminRunScriptCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

/* Query */
void BFBC2Connection::responseServerInfoCommand(const FrostbiteRconPacket &packet)
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

void BFBC2Connection::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminRestartMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit (onMapListNextLevelIndexCommand(index));
    }
}

void BFBC2Connection::responseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet)
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
    } else if (response == "InvalidArguments") {
        emit (onUnknownCommand());
    }
}

void BFBC2Connection::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit (onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2Connection::responseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2Connection::responseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2Connection::responseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2Connection::responseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseTextChatModerationListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseBanListListCommand(const FrostbiteRconPacket &packet)
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

void BFBC2Connection::responseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseReservedSlotsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseReservedSlotsListCommand(const FrostbiteRconPacket &packet)
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

void BFBC2Connection::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
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

void BFBC2Connection::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMapListAppendCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseMaplistInsertCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

void BFBC2Connection::responseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsPunkBusterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsHardCoreCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsRankLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2Connection::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

void BFBC2Connection::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

void BFBC2Connection::responseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseLevelVarsSetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseLevelVarsGetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseLevelVarsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2Connection::responseLevelVarsListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
