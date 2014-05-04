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

#include "BFBC2CommandHandler.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{ 

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

void BFBC2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
	// Parse and call events.
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
	
    // Parse and call requests.
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
void BFBC2CommandHandler::responsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit(onPlayerJoinEvent(player));
}

void BFBC2CommandHandler::responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit(onPlayerAuthenticatedEvent(player, guid));
}

void BFBC2CommandHandler::responsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit(onPlayerLeaveEvent(player, info));
}

void BFBC2CommandHandler::responsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit(onPlayerSpawnEvent(player, kit, weaponList));
}

void BFBC2CommandHandler::responsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = FrostbiteUtils::toBool(packet.getWord(4).getContent());

    emit(onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BFBC2CommandHandler::responsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit(onPlayerChatEvent(player, message, target));
}

void BFBC2CommandHandler::responsePlayerKickedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit(onPlayerKickedEvent(player, reason));
}

void BFBC2CommandHandler::responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit(onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString::fromLatin1(packet.getWord(2).getContent()).toInt();
    int squadId = QString::fromLatin1(packet.getWord(3).getContent()).toInt();

    emit(onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit(onPunkBusterMessageEvent(message));
}

void BFBC2CommandHandler::responsePunkBusterVersionEvent(const FrostbiteRconPacket &packet)
{
    QString version = packet.getWord(1).getContent();

    emit(onPunkBusterVersionEvent(version));
}

void BFBC2CommandHandler::responseServerLoadingLevelEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = QString(packet.getWord(2).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(3).getContent()).toInt();

    emit(onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2CommandHandler::responseServerLevelStartedEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit(onServerLevelStartedEvent());
}

void BFBC2CommandHandler::responseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit(onServerRoundOverEvent(winningTeamId));
}

void BFBC2CommandHandler::responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit(onServerRoundOverPlayersEvent(playerInfo));
}

void BFBC2CommandHandler::responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit(onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */
void BFBC2CommandHandler::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLoginPlainTextCommand(tr("You have successfully logged in.")));
    }
}

/* Misc */
void BFBC2CommandHandler::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit(onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit(onLoginHashedCommand());
        }
    }
}

void BFBC2CommandHandler::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLogoutCommand(tr("You are now logged out.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onQuitCommand(tr("Disconnected.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::responseVersionCommand(const FrostbiteRconPacket &packet)
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

        emit(onVersionCommand(type, buildId, version));

        emit(onLogMessage(0,tr("<b>%1</b> server version: <b>%2</b>.").arg(type, version)));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::responseListPlayersCommand(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK") {
        emit(onListPlayersCommand());
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::responseEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseHelpCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList helpList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            helpList.append(packet.getWord(i).getContent());
        }

        emit(onHelpCommand(helpList));
    }
}

void BFBC2CommandHandler::responseAdminRunScriptCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

/* Query */
void BFBC2CommandHandler::responseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList serverInfo;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            serverInfo.append(packet.getWord(i).getContent());
        }

        emit(onServerInfoCommand(serverInfo));
    }
}

void BFBC2CommandHandler::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminRestartMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit(onMapListNextLevelIndexCommand(index));
    }
}

void BFBC2CommandHandler::responseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet)
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

        emit(onAdminListPlayersCommand(playerList));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit(onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2CommandHandler::responseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2CommandHandler::responseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2CommandHandler::responseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2CommandHandler::responseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseTextChatModerationListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseBanListListCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            banList.append(packet.getWord(i).getContent());
        }

        emit(onBanListListCommand(banList));
    }
}

void BFBC2CommandHandler::responseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseReservedSlotsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseReservedSlotsListCommand(const FrostbiteRconPacket &packet)
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

void BFBC2CommandHandler::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList mapList;

            for (quint32 i = 1; i < packet.getWordCount(); i = i + 2) {
                mapList << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }

            //emit(onMapListListRoundsCommand(mapList));
        } else {
            QStringList mapList;

            for (quint32 i = 1; i < packet.getWordCount(); i++) {
                mapList.append(packet.getWord(i).getContent());
            }

            emit(onMapListListCommand(mapList));
        }
    }

}

void BFBC2CommandHandler::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMapListAppendCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseMaplistInsertCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit(onVarsServerNameCommand(serverName));
    }
}

void BFBC2CommandHandler::responseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsPunkBusterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsHardCoreCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsRankLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit(onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2CommandHandler::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit(onVarsServerDescriptionCommand(serverDescription));
    }
}

void BFBC2CommandHandler::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = QString(packet.getWord(1).getContent()).toInt();

        emit(onVarsIdleTimeoutCommand(timeout));
    }
}

void BFBC2CommandHandler::responseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseLevelVarsSetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseLevelVarsGetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseLevelVarsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::responseLevelVarsListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
