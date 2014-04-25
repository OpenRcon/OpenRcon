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

BF4CommandHandler::BF4CommandHandler(QObject *parent) : BFBaseCommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

void BF4CommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse and call events.
    if (command == "player.onAuthenticated") {
        responsePlayerAuthenticatedEvent(packet);
    } else if (command == "player.onDisconnect") {
        responsePlayerDisconnectEvent(packet);
    } else if (command == "player.onJoin") {
        responsePlayerJoinEvent(packet);
    } else if (command == "player.onLeave") {
        responsePlayerLeaveEvent(packet);
    } else if (command == "player.onSpawn") {
        responsePlayerSpawnEvent(packet);
    } else if (command == "player.onKill") {
        responsePlayerKillEvent(packet);
    } else if (command == "player.onChat") {
        responsePlayerChatEvent(packet);
    } else if (command == "server.onMaxPlayerCountChange") {
        responseServerMaxPlayerCountChangeEvent(packet);
    } else if (command == "player.onSquadChange") {
        responsePlayerSquadChangeEvent(packet);
    } else if (command == "player.onTeamChange") {
        responsePlayerTeamChangeEvent(packet);
    } else if (command == "punkBuster.onMessage") {
        responsePunkBusterMessageEvent(packet);
    } else if (command == "server.onLevelLoaded") {
        responseServerLevelLoadedEvent(packet);
    } else if (command == "server.onRoundOver") {
        responseServerRoundOverEvent(packet);
    } else if (command == "server.onRoundOverPlayers") {
        responseServerRoundOverPlayersEvent(packet);
    } else if (command == "server.onRoundOverTeamScores") {
        responseServerRoundOverTeamScoresEvent(packet);
    }

    // Parse and call commands.
    if (command == "login.plainText") {
        responseLoginPlainTextCommand(packet);
    } else if (command == "login.hashed") {
        responseLoginHashedCommand(packet, lastSentPacket);
    } else if (command == "serverInfo") {
        responseServerInfoCommand(packet);
    } else if (command == "logout") {
        responseLogoutCommand(packet);
    } else if (command == "quit") {
        responseQuitCommand(packet);
    } else if (command ==  "version") {
        responseVersionCommand(packet);
    } else if (command ==  "currentLevel") {
        responseCurrentLevelCommand(packet);
    } else if (command ==  "listPlayers") {
        responseListPlayersCommand(packet);
    } else if (command == "admin.eventsEnabled") {
        responseAdminEventsEnabledCommand(packet);
    } else if (command == "admin.help") {
        responseAdminHelpCommand(packet);
    } else if (command == "admin.kickPlayer") {
        responseAdminKickPlayerCommand(packet);
    } else if (command == "admin.killPlayer") {
        responseAdminKillPlayerCommand(packet);
    } else if (command == "admin.listPlayers") {
        responseAdminListPlayersCommand(packet);
    } else if (command == "admin.movePlayer") {
        responseAdminMovePlayerCommand(packet);
    } else if (command == "admin.password") {
        responseAdminPasswordCommand(packet);
    } else if (command == "admin.say") {
        responseAdminSayCommand(packet);
    } else if (command == "admin.shutDown") {
        responseAdminShutDownCommand(packet);
    } else if (command == "admin.yell") {
        responseAdminYellCommand(packet);
    } else if (command == "banList.add") {
        responseBanListAddCommand(packet);
    } else if (command == "banList.clear") {
        responseBanListClearCommand(packet);
    } else if (command == "banList.list") {
        responseBanListListCommand(packet);
    } else if (command == "banList.load") {
        responseBanListLoadCommand(packet);
    } else if (command == "banList.remove") {
        responseBanListRemoveCommand(packet);
    } else if (command == "banList.save") {
        responseBanListSaveCommand(packet);
    } else if (command == "fairFight.activate") {
        responseFairFightActivateCommand(packet);
    } else if (command == "fairFight.deactivate") {
        responseFairFightDeactivateCommand(packet);
    } else if (command == "fairFight.isActive") {
        responseFairFightIsActiveCommand(packet);
    } else if (command == "mapList.add") {
        responseMapListAddCommand(packet);
    } else if (command == "mapList.availableMaps") {
        responseMapListAvailableMapsCommand(packet);
    } else if (command == "mapList.clear") {
        responseMapListClearCommand(packet);
    } else if (command == "mapList.endRound") {
        responseMapListEndRoundCommand(packet);
    } else if (command == "mapList.getMapIndices") {
        responseMapListGetMapIndicesCommand(packet);
    } else if (command == "mapList.getRounds") {
        responseMapListGetRoundsCommand(packet);
    } else if (command == "maplist.list") { // case sensetive?
        responseMapListListCommand(packet);
    } else if (command == "mapList.load") {
        responseMapListLoadCommand(packet);
    } else if (command == "mapList.remove") {
        responseMapListRemoveCommand(packet);
    } else if (command == "mapList.restartRound") {
        responseMapListRestartRoundCommand(packet);
    } else if (command == "mapList.runNextRound") {
        responseMapListRunNextRoundCommand(packet);
    } else if (command == "mapList.save") {
        responseMapListSaveCommand(packet);
    } else if (command == "mapList.setNextMapIndex") {
        responseMapListSetNextMapIndexCommand(packet);
    } else if (command == "player.idleDuration") {
        responsePlayerIdleDurationCommand(packet);
    } else if (command == "player.isAlive") {
        responsePlayerIsAliveCommand(packet);
    } else if (command == "player.ping") {
        responsePlayerPingCommand(packet);
    } else if (command == "punkBuster.activate") {
        responsePunkBusterActivateCommand(packet);
    } else if (command == "punkBuster.isActive") {
        responsePunkBusterIsActiveCommand(packet);
    } else if (command == "punkBuster.pb_sv_command") {
        responsePunkBusterPbSvCommandCommand(packet);
    } else if (command == "reservedSlotsList.add") {
        responseReservedSlotsListAddCommand(packet);
    } else if (command == "reservedSlotsList.aggressiveJoin") {
        responseReservedSlotsListAggressiveJoinCommand(packet);
    } else if (command == "reservedSlotsList.clear") {
        responseReservedSlotsListClearCommand(packet);
    } else if (command == "reservedSlotsList.list") {
        responseReservedSlotsListListCommand(packet);
    } else if (command == "reservedSlotsList.load") {
        responseReservedSlotsListLoadCommand(packet);
    } else if (command == "reservedSlotsList.remove") {
        responseReservedSlotsListRemoveCommand(packet);
    } else if (command == "reservedSlotsList.save") {
        responseReservedSlotsListSaveCommand(packet);
    } else if (command == "spectatorList.add") {
        responseSpectatorListAddCommand(packet);
    } else if (command == "spectatorList.clear") {
        responseSpectatorListClearCommand(packet);
    } else if (command == "spectatorList.list") {
        responseSpectatorListListCommand(packet);
    } else if (command == "spectatorList.remove") {
        responseSpectatorListRemoveCommand(packet);
    } else if (command == "spectatorList.save") {
        responseSpectatorListSaveCommand(packet);
    } else if (command == "squad.leader") {
        responseSquadLeaderCommand(packet);
    } else if (command == "squad.listActive") {
        responseSquadListActiveCommand(packet);
    } else if (command == "squad.listPlayers") {
        responseSquadListPlayersCommand(packet);
    } else if (command == "squad.private") {
        responseSquadPrivateCommand(packet);
    } else if (command == "vars.3dSpotting") {
        responseVars3dSpottingCommand(packet);
    } else if (command == "vars.3pCam") {
        responseVars3pCamCommand(packet);
    } else if (command == "vars.alwaysAllowSpectators") {
        responseVarsAlwaysAllowSpectatorsCommand(packet);
    } else if (command == "vars.autoBalance") {
        responseVarsAutoBalanceCommand(packet);
    } else if (command == "vars.bulletDamage") {
        responseVarsBulletDamageCommand(packet);
    } else if (command == "vars.commander") {
        responseVarsCommanderCommand(packet);
    } else if (command == "vars.crossHair") {
        responseVarsCrossHairCommand(packet);
    } else if (command == "vars.forceReloadWholeMags") {
        responseVarsForceReloadWholeMagsCommand(packet);
    } else if (command == "vars.friendlyFire") {
        responseVarsFriendlyFireCommand(packet);
    } else if (command == "vars.gameModeCounter") {
        responseVarsGameModeCounterCommand(packet);
    } else if (command == "vars.gamePassword") {
        responseVarsGamePasswordCommand(packet);
    } else if (command == "vars.hitIndicatorsEnabled") {
        responseVarsHitIndicatorsEnabledCommand(packet);
    } else if (command == "vars.hud") {
        responseVarsHudCommand(packet);
    } else if (command == "vars.idleBanRounds") {
        responseVarsIdleBanRoundsCommand(packet);
    } else if (command == "vars.idleTimeout") {
        responseVarsIdleTimeoutCommand(packet);
    } else if (command == "vars.killCam") {
        responseVarsKillCamCommand(packet);
    } else if (command == "vars.maxPlayers") {
        responseVarsMaxPlayersCommand(packet);
    } else if (command == "vars.maxSpectators") {
        responseVarsMaxSpectatorsCommand(packet);
    } else if (command == "vars.miniMap") {
        responseVarsMiniMapCommand(packet);
    } else if (command == "vars.miniMapSpotting") {
        responseVarsMiniMapSpottingCommand(packet);
    } else if (command == "vars.mpExperience") {
        responseVarsMpExperienceCommand(packet);
    } else if (command == "vars.nameTag") {
        responseVarsNameTagCommand(packet);
    } else if (command == "vars.onlySquadLeaderSpawn") {
        responseVarsOnlySquadLeaderSpawnCommand(packet);
    } else if (command == "vars.playerRespawnTime") {
        responseVarsPlayerRespawnTimeCommand(packet);
    } else if (command == "vars.preset") {
        responseVarsPresetCommand(packet);
    } else if (command == "vars.regenerateHealth") {
        responseVarsRegenerateHealthCommand(packet);
    } else if (command == "vars.roundLockdownCountdown") {
        responseVarsRoundLockdownCountdownCommand(packet);
    } else if (command == "vars.roundRestartPlayerCount") {
        responseVarsRoundRestartPlayerCountCommand(packet);
    } else if (command == "vars.roundStartPlayerCount") {
        responseVarsRoundStartPlayerCountCommand(packet);
    } else if (command == "vars.roundTimeLimit") {
        responseVarsRoundTimeLimitCommand(packet);
    } else if (command == "vars.roundWarmupTimeout") {
        responseVarsRoundWarmupTimeoutCommand(packet);
    } else if (command == "vars.serverDescription") {
        responseVarsServerDescriptionCommand(packet);
    } else if (command == "vars.serverMessage") {
        responseVarsServerMessageCommand(packet);
    } else if (command == "vars.serverName") {
        responseVarsServerNameCommand(packet);
    } else if (command == "vars.serverType") {
        responseVarsServerTypeCommand(packet);
    } else if (command == "vars.soldierHealth") {
        responseVarsSoldierHealthCommand(packet);
    } else if (command == "vars.team1FactionOverride") {
        responseVarsTeam1FactionOverrideCommand(packet);
    } else if (command == "vars.team2FactionOverride") {
        responseVarsTeam2FactionOverrideCommand(packet);
    } else if (command == "vars.team3FactionOverride") {
        responseVarsTeam3FactionOverrideCommand(packet);
    } else if (command == "vars.team4FactionOverride") {
        responseVarsTeam4FactionOverrideCommand(packet);
    } else if (command == "vars.teamKillCountForKick") {
        responseVarsTeamKillCountForKickCommand(packet);
    } else if (command == "vars.teamKillKickForBan") {
        responseVarsTeamKillKickForBanCommand(packet);
    } else if (command == "vars.teamKillValueDecreasePerSecond") {
        responseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (command == "vars.teamKillValueForKick") {
        responseVarsTeamKillValueForKickCommand(packet);
    } else if (command == "vars.teamKillValueIncrease") {
        responseVarsTeamKillValueIncreaseCommand(packet);
    } else if (command == "vars.ticketBleedRate") {
        responseVarsTicketBleedRateCommand(packet);
    } else if (command == "vars.unlockMode") {
        responseVarsUnlockModeCommand(packet);
    } else if (command == "vars.vehicleSpawnAllowed") {
        responseVarsVehicleSpawnAllowedCommand(packet);
    } else if (command == "vars.vehicleSpawnDelay") {
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

    if (response == "OK" && packet.getWordCount() > 0) {
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

        emit (onServerInfoCommand(ServerInfo(serverName, playerCount, maxPlayerCount, gamemode, currentMap, roundsPlayed, roundsTotal, scores, onlineState, ranked, punkBuster, hasGamePassword, serverUpTime, roundTime, gameIpAndPort,  punkBusterVersion, joinQueueEnabled, region, closestPingSite, country,  matchMakingEnabled, blazePlayerCount, blazeGameState)));
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
        QString version = QString::number(build);

        QMap<int, QString> versionMap;
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

        if (versionMap.contains(build)) {
            version = versionMap.value(build);
        }

        emit (onVersionCommand(type, build, version));
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

void BF4CommandHandler::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    // OK 10 name guid teamId squadId kills deaths score rank ping type 1 halvorshalvors EA_76544D0431556D2ECC32046A5FDB5B49 1 1 0 0 0 7 44 0
    if (response == "OK" && packet.getWordCount() > 0) {
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

        emit (onAdminListPlayersCommand(playerList));
    } else if (response == "InvalidArguments") {
        emit (onUnknownCommand());
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
