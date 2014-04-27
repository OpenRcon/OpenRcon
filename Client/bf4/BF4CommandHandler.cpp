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

#include "BF4CommandHandler.h"

BF4CommandHandler::BF4CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

void BF4CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse and call events.
    if (request == "player.onAuthenticated") {
        responsePlayerAuthenticatedEvent(packet);
    } else if (request == "player.onDisconnect") {
        responsePlayerDisconnectEvent(packet);
    } else if (request == "player.onJoin") {
        responsePlayerJoinEvent(packet);
    } else if (request == "player.onLeave") {
        responsePlayerLeaveEvent(packet);
    } else if (request == "player.onSpawn") {
        responsePlayerSpawnEvent(packet);
    } else if (request == "player.onKill") {
        responsePlayerKillEvent(packet);
    } else if (request == "player.onChat") {
        responsePlayerChatEvent(packet);
    } else if (request == "server.onMaxPlayerCountChange") {
        responseServerMaxPlayerCountChangeEvent(packet);
    } else if (request == "player.onSquadChange") {
        responsePlayerSquadChangeEvent(packet);
    } else if (request == "player.onTeamChange") {
        responsePlayerTeamChangeEvent(packet);
    } else if (request == "punkBuster.onMessage") {
        responsePunkBusterMessageEvent(packet);
    } else if (request == "server.onLevelLoaded") {
        responseServerLevelLoadedEvent(packet);
    } else if (request == "server.onRoundOver") {
        responseServerRoundOverEvent(packet);
    } else if (request == "server.onRoundOverPlayers") {
        responseServerRoundOverPlayersEvent(packet);
    } else if (request == "server.onRoundOverTeamScores") {
        responseServerRoundOverTeamScoresEvent(packet);
    }

    // Parse and call commands.
    if (request == "login.plainText") {
        responseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        responseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "serverInfo") {
        responseServerInfoCommand(packet);
    } else if (request == "logout") {
        responseLogoutCommand(packet);
    } else if (request == "quit") {
        responseQuitCommand(packet);
    } else if (request ==  "version") {
        responseVersionCommand(packet);
    } else if (request ==  "currentLevel") {
        responseCurrentLevelCommand(packet);
    } else if (request ==  "listPlayers") {
        responseListPlayersCommand(packet);
    } else if (request == "admin.eventsEnabled") {
        responseAdminEventsEnabledCommand(packet);
    } else if (request == "admin.help") {
        responseAdminHelpCommand(packet);
    } else if (request == "admin.kickPlayer") {
        responseAdminKickPlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        responseAdminKillPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        responseAdminListPlayersCommand(packet, lastSentPacket);
    } else if (request == "admin.movePlayer") {
        responseAdminMovePlayerCommand(packet);
    } else if (request == "admin.password") {
        responseAdminPasswordCommand(packet);
    } else if (request == "admin.say") {
        responseAdminSayCommand(packet);
    } else if (request == "admin.shutDown") {
        responseAdminShutDownCommand(packet);
    } else if (request == "admin.yell") {
        responseAdminYellCommand(packet);
    } else if (request == "banList.add") {
        responseBanListAddCommand(packet);
    } else if (request == "banList.clear") {
        responseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        responseBanListListCommand(packet);
    } else if (request == "banList.load") {
        responseBanListLoadCommand(packet);
    } else if (request == "banList.remove") {
        responseBanListRemoveCommand(packet);
    } else if (request == "banList.save") {
        responseBanListSaveCommand(packet);
    } else if (request == "fairFight.activate") {
        responseFairFightActivateCommand(packet);
    } else if (request == "fairFight.deactivate") {
        responseFairFightDeactivateCommand(packet);
    } else if (request == "fairFight.isActive") {
        responseFairFightIsActiveCommand(packet);
    } else if (request == "mapList.add") {
        responseMapListAddCommand(packet);
    } else if (request == "mapList.availableMaps") {
        responseMapListAvailableMapsCommand(packet);
    } else if (request == "mapList.clear") {
        responseMapListClearCommand(packet);
    } else if (request == "mapList.endRound") {
        responseMapListEndRoundCommand(packet);
    } else if (request == "mapList.getMapIndices") {
        responseMapListGetMapIndicesCommand(packet);
    } else if (request == "mapList.getRounds") {
        responseMapListGetRoundsCommand(packet);
    } else if (request == "maplist.list") { // case sensetive?
        responseMapListListCommand(packet);
    } else if (request == "mapList.load") {
        responseMapListLoadCommand(packet);
    } else if (request == "mapList.remove") {
        responseMapListRemoveCommand(packet);
    } else if (request == "mapList.restartRound") {
        responseMapListRestartRoundCommand(packet);
    } else if (request == "mapList.runNextRound") {
        responseMapListRunNextRoundCommand(packet);
    } else if (request == "mapList.save") {
        responseMapListSaveCommand(packet);
    } else if (request == "mapList.setNextMapIndex") {
        responseMapListSetNextMapIndexCommand(packet);
    } else if (request == "player.idleDuration") {
        responsePlayerIdleDurationCommand(packet);
    } else if (request == "player.isAlive") {
        responsePlayerIsAliveCommand(packet);
    } else if (request == "player.ping") {
        responsePlayerPingCommand(packet);
    } else if (request == "punkBuster.activate") {
        responsePunkBusterActivateCommand(packet);
    } else if (request == "punkBuster.isActive") {
        responsePunkBusterIsActiveCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        responsePunkBusterPbSvCommandCommand(packet);
    } else if (request == "reservedSlotsList.add") {
        responseReservedSlotsListAddCommand(packet);
    } else if (request == "reservedSlotsList.aggressiveJoin") {
        responseReservedSlotsListAggressiveJoinCommand(packet);
    } else if (request == "reservedSlotsList.clear") {
        responseReservedSlotsListClearCommand(packet);
    } else if (request == "reservedSlotsList.list") {
        responseReservedSlotsListListCommand(packet);
    } else if (request == "reservedSlotsList.load") {
        responseReservedSlotsListLoadCommand(packet);
    } else if (request == "reservedSlotsList.remove") {
        responseReservedSlotsListRemoveCommand(packet);
    } else if (request == "reservedSlotsList.save") {
        responseReservedSlotsListSaveCommand(packet);
    } else if (request == "spectatorList.add") {
        responseSpectatorListAddCommand(packet);
    } else if (request == "spectatorList.clear") {
        responseSpectatorListClearCommand(packet);
    } else if (request == "spectatorList.list") {
        responseSpectatorListListCommand(packet);
    } else if (request == "spectatorList.remove") {
        responseSpectatorListRemoveCommand(packet);
    } else if (request == "spectatorList.save") {
        responseSpectatorListSaveCommand(packet);
    } else if (request == "squad.leader") {
        responseSquadLeaderCommand(packet);
    } else if (request == "squad.listActive") {
        responseSquadListActiveCommand(packet);
    } else if (request == "squad.listPlayers") {
        responseSquadListPlayersCommand(packet);
    } else if (request == "squad.private") {
        responseSquadPrivateCommand(packet);
    } else if (request == "vars.3dSpotting") {
        responseVars3dSpottingCommand(packet);
    } else if (request == "vars.3pCam") {
        responseVars3pCamCommand(packet);
    } else if (request == "vars.alwaysAllowSpectators") {
        responseVarsAlwaysAllowSpectatorsCommand(packet);
    } else if (request == "vars.autoBalance") {
        responseVarsAutoBalanceCommand(packet);
    } else if (request == "vars.bulletDamage") {
        responseVarsBulletDamageCommand(packet);
    } else if (request == "vars.commander") {
        responseVarsCommanderCommand(packet);
    } else if (request == "vars.crossHair") {
        responseVarsCrossHairCommand(packet);
    } else if (request == "vars.forceReloadWholeMags") {
        responseVarsForceReloadWholeMagsCommand(packet);
    } else if (request == "vars.friendlyFire") {
        responseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.gameModeCounter") {
        responseVarsGameModeCounterCommand(packet);
    } else if (request == "vars.gamePassword") {
        responseVarsGamePasswordCommand(packet);
    } else if (request == "vars.hitIndicatorsEnabled") {
        responseVarsHitIndicatorsEnabledCommand(packet);
    } else if (request == "vars.hud") {
        responseVarsHudCommand(packet);
    } else if (request == "vars.idleBanRounds") {
        responseVarsIdleBanRoundsCommand(packet);
    } else if (request == "vars.idleTimeout") {
        responseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.killCam") {
        responseVarsKillCamCommand(packet);
    } else if (request == "vars.maxPlayers") {
        responseVarsMaxPlayersCommand(packet);
    } else if (request == "vars.maxSpectators") {
        responseVarsMaxSpectatorsCommand(packet);
    } else if (request == "vars.miniMap") {
        responseVarsMiniMapCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        responseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.mpExperience") {
        responseVarsMpExperienceCommand(packet);
    } else if (request == "vars.nameTag") {
        responseVarsNameTagCommand(packet);
    } else if (request == "vars.onlySquadLeaderSpawn") {
        responseVarsOnlySquadLeaderSpawnCommand(packet);
    } else if (request == "vars.playerRespawnTime") {
        responseVarsPlayerRespawnTimeCommand(packet);
    } else if (request == "vars.preset") {
        responseVarsPresetCommand(packet);
    } else if (request == "vars.regenerateHealth") {
        responseVarsRegenerateHealthCommand(packet);
    } else if (request == "vars.roundLockdownCountdown") {
        responseVarsRoundLockdownCountdownCommand(packet);
    } else if (request == "vars.roundRestartPlayerCount") {
        responseVarsRoundRestartPlayerCountCommand(packet);
    } else if (request == "vars.roundStartPlayerCount") {
        responseVarsRoundStartPlayerCountCommand(packet);
    } else if (request == "vars.roundTimeLimit") {
        responseVarsRoundTimeLimitCommand(packet);
    } else if (request == "vars.roundWarmupTimeout") {
        responseVarsRoundWarmupTimeoutCommand(packet);
    } else if (request == "vars.serverDescription") {
        responseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.serverMessage") {
        responseVarsServerMessageCommand(packet);
    } else if (request == "vars.serverName") {
        responseVarsServerNameCommand(packet);
    } else if (request == "vars.serverType") {
        responseVarsServerTypeCommand(packet);
    } else if (request == "vars.soldierHealth") {
        responseVarsSoldierHealthCommand(packet);
    } else if (request == "vars.team1FactionOverride") {
        responseVarsTeam1FactionOverrideCommand(packet);
    } else if (request == "vars.team2FactionOverride") {
        responseVarsTeam2FactionOverrideCommand(packet);
    } else if (request == "vars.team3FactionOverride") {
        responseVarsTeam3FactionOverrideCommand(packet);
    } else if (request == "vars.team4FactionOverride") {
        responseVarsTeam4FactionOverrideCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        responseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillKickForBan") {
        responseVarsTeamKillKickForBanCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        responseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        responseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        responseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.ticketBleedRate") {
        responseVarsTicketBleedRateCommand(packet);
    } else if (request == "vars.unlockMode") {
        responseVarsUnlockModeCommand(packet);
    } else if (request == "vars.vehicleSpawnAllowed") {
        responseVarsVehicleSpawnAllowedCommand(packet);
    } else if (request == "vars.vehicleSpawnDelay") {
        responseVarsVehicleSpawnDelayCommand(packet);
    } else {
        responseUnknownCommand();
    }
}

/* Events */
void BF4CommandHandler::responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerAuthenticatedEvent(player, guid));
}

void BF4CommandHandler::responsePlayerDisconnectEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onPlayerDisconnectEvent());
}

void BF4CommandHandler::responsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerJoinEvent(player));
}

void BF4CommandHandler::responsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BF4CommandHandler::responsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();

    emit (onPlayerSpawnEvent(player, teamId));
}

void BF4CommandHandler::responsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BF4CommandHandler::responsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BF4CommandHandler::responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BF4CommandHandler::responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BF4CommandHandler::responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BF4CommandHandler::responseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseServerLevelLoadedEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void BF4CommandHandler::responseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void BF4CommandHandler::responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BF4CommandHandler::responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */
void BF4CommandHandler::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
        } else if (response == "InvalidPasswordHash") {
            emit (onLoginHashedCommand(false));
        }
    }
}

void BF4CommandHandler::responseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();
        int playerCount = QString(packet.getWord(2).getContent()).toInt();
        int maxPlayerCount = QString(packet.getWord(3).getContent()).toInt();
        QString gamemode = packet.getWord(4).getContent();
        QString currentMap = packet.getWord(5).getContent();
        int roundsPlayed = QString(packet.getWord(6).getContent()).toInt();
        int roundsTotal = QString(packet.getWord(7).getContent()).toInt();

        // TODO: Check indexes here.
        QString scores = packet.getWord(8).getContent();
        QString onlineState = packet.getWord(9).getContent();
        bool ranked = toBool(packet.getWord(10).getContent());
        bool punkBuster = toBool(packet.getWord(11).getContent());
        bool hasGamePassword = toBool(packet.getWord(12).getContent());
        int serverUpTime = QString(packet.getWord(13).getContent()).toInt();
        int roundTime = QString(packet.getWord(14).getContent()).toInt();
        QString gameIpAndPort = packet.getWord(15).getContent();
        QString punkBusterVersion = packet.getWord(16).getContent();
        bool joinQueueEnabled = toBool(packet.getWord(17).getContent());
        QString region = packet.getWord(18).getContent();
        QString closestPingSite = packet.getWord(19).getContent();
        QString country = packet.getWord(20).getContent();
        bool matchMakingEnabled = toBool(packet.getWord(21).getContent());
        int blazePlayerCount = QString(packet.getWord(22).getContent()).toInt();
        QString blazeGameState = packet.getWord(23).getContent();

        ServerInfo serverInfo(
                   serverName,
                   playerCount,
                   maxPlayerCount,
                   gamemode,
                   currentMap,
                   roundsPlayed,
                   roundsTotal,
                   scores,
                   onlineState,
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
                   matchMakingEnabled,
                   blazePlayerCount,
                   blazeGameState
        );

        emit (onServerInfoCommand(serverInfo));
    }
}

void BF4CommandHandler::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF4CommandHandler::responseCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QList<PlayerInfo> playerList;
        int parameters = QString(packet.getWord(1).getContent()).toInt();
        int players = QString(packet.getWord(2 + parameters).getContent()).toInt();

        for (int i = 0; i < players; i++) {
            QStringList list;

            for (int j = 0; j < parameters; j++) {
                list.append(packet.getWord(2 + parameters + 1 + i * parameters + j).getContent());
            }

            QString name = list.at(0);
            QString guid = list.at(1);
            int teamId = list.at(2).toInt();
            int squadId = list.at(3).toInt();
            int kills = list.at(4).toInt();
            int deaths = list.at(5).toInt();
            int score = list.at(6).toInt();
            int rank = list.at(7).toInt();
            int ping = list.at(8).toInt();

            playerList.append(PlayerInfo(name, guid, teamId, squadId, kills, deaths, score, rank, ping));
        }

        QString request = lastSentPacket.getWord(1).getContent();
        PlayerSubset playerSubset;

        if (request == "all") {
            playerSubset = All;
        } else if (request == "team") {
            playerSubset = Team;
        } else if (request == "squad") {
            playerSubset = Squad;
        } else if (request == "player") {
            playerSubset = Player;
        }

        emit (onAdminListPlayersCommand(playerList, playerSubset));
    }
}

void BF4CommandHandler::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminShutDownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseBanListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        BanList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            QString idType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = toInt(packet.getWord(i + 3).getContent());
            int rounds = toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(idType, id, banType, seconds, rounds, reason));
        }

        emit (onBanListListCommand(banList));
    }
}

void BF4CommandHandler::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseFairFightActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseFairFightDeactivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseFairFightIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

void BF4CommandHandler::responseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        MapList mapList;
        int maps = QString(packet.getWord(1).getContent()).toInt();
        int parameters = QString(packet.getWord(2).getContent()).toInt();

        for (int i = 0; i < maps; i++) {
            QString level;
            QString gameMode;
            int rounds;

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

void BF4CommandHandler::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(isActive));
    }
}

void BF4CommandHandler::responsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListListCommand(reservedSlotList));
    }
}

void BF4CommandHandler::responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSpectatorListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSpectatorListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSpectatorListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList spectatorList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            spectatorList.append(packet.getWord(i).getContent());
        }

        emit (onSpectatorListListCommand(spectatorList));
    }
}

void BF4CommandHandler::responseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSpectatorListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsCommanderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = QString(packet.getWord(1).getContent()).toInt();

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

void BF4CommandHandler::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void BF4CommandHandler::responseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int spectatorCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4CommandHandler::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsMpExperienceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsPresetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

void BF4CommandHandler::responseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverMessage = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(serverMessage));
    }
}

void BF4CommandHandler::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

void BF4CommandHandler::responseVarsServerTypeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsServerTypeCommand(type));
    }
}

void BF4CommandHandler::responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeam1FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeam2FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeam3FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeam4FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
