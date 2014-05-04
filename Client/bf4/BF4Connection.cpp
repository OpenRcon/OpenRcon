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

#include "BF4Connection.h"

BF4Connection::BF4Connection(QObject *parent) : FrostbiteConnection(parent)
{

}

BF4Connection::~BF4Connection()
{

}

void BF4Connection::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse events.
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

    // Parse commands.
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
    } else if (request == "version") {
        responseVersionCommand(packet);
    } else if (request == "currentLevel") {
        responseCurrentLevelCommand(packet);
    } else if (request == "listPlayers") {
        responseListPlayersCommand(packet, lastSentPacket);
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
    } else if (request == "mapList.list") {
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
        responsePunkBusterPbSvCommand(packet);
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

/* Send */

// Misc
void BF4Connection::sendLoginPlainTextCommand(const QString &password)
{
    sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void BF4Connection::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BF4Connection::sendServerInfoCommand()
{
    sendCommand("serverInfo");
}

void BF4Connection::sendLogoutCommand()
{
    sendCommand("logout");
}

void BF4Connection::sendQuitCommand()
{
    sendCommand("quit");
}

void BF4Connection::sendVersionCommand()
{
    sendCommand("version");
}

void BF4Connection::sendCurrentLevelCommand()
{
    sendCommand("currentLevel");
}

void BF4Connection::sendListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        sendCommand("\"listPlayers\" \"all\"");
    }
}

// Admin
void BF4Connection::sendAdminEventsEnabledCommand(const bool &enabled)
{
    sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendAdminHelpCommand()
{
    sendCommand("admin.help");
}

void BF4Connection::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void BF4Connection::sendAdminKillPlayerCommand(const QString &player)
{
    sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BF4Connection::sendAdminListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BF4Connection::sendAdminMovePlayerCommand(const QString &player, const int &teamId, const int &squadId, const bool &forceKill)
{
    sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId, squadId).arg(toString(forceKill)));
}

void BF4Connection::sendAdminPasswordCommand()
{
    sendCommand("admin.password");
}

void BF4Connection::sendAdminPasswordCommand(const QString &password)
{
    sendCommand(QString("\"admin.password\" \"%1\"").arg(password));
}

void BF4Connection::sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(message));
    }
}

void BF4Connection::sendAdminShutdownCommand()
{
    sendCommand("admin.shutDown");
}

void BF4Connection::sendAdminShutdownCommand(const bool &graceful)
{
    sendCommand(QString("\"admin.shutDown\" \"%1\"").arg(toString(graceful)));
}

void BF4Connection::sendAdminShutdownCommand(const bool &graceful, const int &seconds)
{
    sendCommand(QString("\"admin.shutDown\" \"%1\" \"%2\"").arg(toString(graceful)).arg(seconds));
}

void BF4Connection::sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset)
{
    sendAdminYellCommand(message, 10, playerSubset);
}

void BF4Connection::sendAdminYellCommand(const QString &message, const int &duration, const PlayerSubset &playerSubset)
{
    if (message.length() <= 256) {
        if (playerSubset == PlayerSubset::All) {
            sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
        }
    }
}

// Banning
void BF4Connection::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void BF4Connection::sendBanListAddCommand(const QString &idType, const QString &id, const int &timeout, const bool &useRounds, const QString &reason)
{
    QString timeoutType = useRounds ? "rounds" : "seconds";

    sendCommand(QString("banList.add %1 %2 %3 %4 %5").arg(idType, id, timeoutType).arg(toString(timeout), reason));
    sendBanListListCommand();
}

void BF4Connection::sendBanListClearCommand()
{
    sendCommand("banList.clear");
}

void BF4Connection::sendBanListListCommand(const int &index)
{
    if (index == 0) {
        sendCommand("banList.list");
    } else {
        sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void BF4Connection::sendBanListLoadCommand()
{
    sendCommand("banList.load");
}

void BF4Connection::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void BF4Connection::sendBanListSaveCommand()
{
    sendCommand("banList.save");
}

// FairFight
void BF4Connection::sendFairFightActivateCommand()
{
    sendCommand("fairFight.activate");
}

void BF4Connection::sendFairFightDeactivateCommand()
{
    sendCommand("fairfight.deactivate");
}

void BF4Connection::sendFairFightIsActiveCommand()
{
    sendCommand("fairFight.isActive");
}

// Maplist
void BF4Connection::sendMapListAdd(const QString &level, const QString &gameMode, const int &rounds, const int &offSet)
{
    sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListList();
}

void BF4Connection::sendMapListAvailableMaps(const QString &filter)
{
    sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void BF4Connection::sendMapListClear()
{
    sendCommand("mapList.clear");
}

void BF4Connection::sendMapListEndRound(const int &teamId)
{
    sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void BF4Connection::sendMapListGetMapIndices()
{
    sendCommand("mapList.getMapIndices");
}

void BF4Connection::sendMapListGetRounds()
{
    sendCommand("mapList.getRounds");
}

void BF4Connection::sendMapListList(const int &index)
{
    if (index == 0) {
        sendCommand("mapList.list");
    } else {
        sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void BF4Connection::sendMapListLoad()
{
    sendCommand("mapList.load");
}

void BF4Connection::sendMapListRemove(const int &index)
{
    sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
}

void BF4Connection::sendMapListRestartRound()
{
    sendCommand("mapList.restartRound");
}

void BF4Connection::sendMapListRunNextRound()
{
    sendCommand("mapList.runNextRound");
}

void BF4Connection::sendMapListSave()
{
    sendCommand("mapList.save");
}

void BF4Connection::sendMapListSetNextMapIndex(const int &index)
{
    sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

void BF4Connection::sendPlayerIdleDuration(const QString &player)
{
    sendCommand(QString("\"player.idleDuration\" \"%1\"").arg(player));
}

void BF4Connection::sendPlayerIsAlive(const QString &player)
{
    sendCommand(QString("\"player.isAlive\" \"%1\"").arg(player));
}

void BF4Connection::sendPlayerPing(const QString &player)
{
    sendCommand(QString("\"player.ping\" \"%1\"").arg(player));
}

// PunkBuster
void BF4Connection::sendPunkBusterActivate()
{
    sendCommand("punkBuster.activate");
}

void BF4Connection::sendPunkBusterIsActive()
{
    sendCommand("punkBuster.isActive");
}

void BF4Connection::sendPunkBusterPbSvCommand(const QString &command)
{
    sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}

// Reserved Slots
void BF4Connection::sendReservedSlotsListAdd(const QString &player)
{
    sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4Connection::sendReservedSlotsListAggressiveJoin()
{
    sendCommand("reservedSlotsList.aggressiveJoin");
}

void BF4Connection::sendReservedSlotsListAggressiveJoin(const bool &enabled)
{
    sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendReservedSlotsListClear()
{
    sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListList();
}

void BF4Connection::sendReservedSlotsListList()
{
    sendCommand("reservedSlotsList.list");
}

void BF4Connection::sendReservedSlotsListLoad()
{
    sendCommand("reservedSlotsList.load");
    sendReservedSlotsListList();
}

void BF4Connection::sendReservedSlotsListRemove(const QString &player)
{
    sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4Connection::sendReservedSlotsListSave()
{
    sendCommand("reservedSlotsList.save");
    sendReservedSlotsListList();
}

// Spectator list
void BF4Connection::sendSpectatorListAdd(const QString &player)
{
    sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4Connection::sendSpectatorListClear()
{
    sendCommand("spectatorList.clear");
    sendSpectatorListList();
}

void BF4Connection::sendSpectatorListList(const int &index)
{
    if (index == 0) {
        sendCommand("spectatorList.list");
    } else {
        sendCommand(QString("\"spectatorList.list\" \"%1\"").arg(index));
    }
}

void BF4Connection::sendSpectatorListRemove(const QString &player)
{
    sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4Connection::sendSpectatorListSave()
{
    sendCommand("spectatorList.save");
    sendSpectatorListList();
}

// Squad
void BF4Connection::sendSquadLeader(const int &teamId, const int &squadId, const QString &player)
{
    sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void BF4Connection::sendSquadListActive(const int &teamId)
{
    sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void BF4Connection::sendSquadListPlayers(const int &teamId, const int &squadId)
{
    sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void BF4Connection::sendSquadPrivate(const int &teamId, const int &squadId, const bool &isPrivate)
{
    sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(toString(isPrivate)));
}

// Variables
void BF4Connection::sendVars3dSpotting()
{
    sendCommand("vars.3dSpotting");
}

void BF4Connection::sendVars3dSpotting(const bool &enabled)
{
    sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVars3pCam()
{
    sendCommand("vars.3pCam");
}

void BF4Connection::sendVars3pCam(const bool &enabled)
{
    sendCommand(QString("\"vars.3pCam\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsAlwaysAllowSpectators()
{
    sendCommand("vars.alwaysAllowSpectators");
}

void BF4Connection::sendVarsAlwaysAllowSpectators(const bool &enabled)
{
    sendCommand(QString("\"vars.alwaysAllowSpectators\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsAutoBalance()
{
    sendCommand("vars.autoBalance");
}

void BF4Connection::sendVarsAutoBalance(const bool &enabled)
{
    sendCommand(QString("\"vars.autoBalance\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsBulletDamage(const int &damage)
{
    if (damage == -1) {
        sendCommand("vars.bulletDamage");
    } else {
        sendCommand(QString("\"vars.bulletDamage\" \"%1\"").arg(damage));
    }
}

void BF4Connection::sendVarsCommander()
{
    sendCommand("vars.commander");
}

void BF4Connection::sendVarsCommander(const bool &enabled)
{
    sendCommand(QString("\"vars.commander\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsForceReloadWholeMags()
{
    sendCommand("vars.forceReloadWholeMags");
}

void BF4Connection::sendVarsForceReloadWholeMags(const bool &enabled)
{
    sendCommand(QString("\"vars.forceReloadWholeMags\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsFriendlyFire()
{
    sendCommand("vars.friendlyFire");
}

void BF4Connection::sendVarsFriendlyFire(const bool &enabled)
{
    sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsGameModeCounter(const int &scale)
{
    if (scale == -1) {
        sendCommand("vars.gameModeCounter");
    } else {
        sendCommand(QString("\"vars.gameModeCounter\" \"%1\"").arg(scale));
    }
}

void BF4Connection::sendVarsGamePassword(const QString &password)
{
    if (password == 0) {
        sendCommand("vars.gamePassword");
    } else {
        sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
}

void BF4Connection::sendVarsHitIndicatorsEnabled()
{
    sendCommand("vars.hitIndicatorsEnabled");
}

void BF4Connection::sendVarsHitIndicatorsEnabled(const bool &enabled)
{
    sendCommand(QString("\"vars.hitIndicatorsEnabled\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsHud()
{
    sendCommand("vars.hud");
}

void BF4Connection::sendVarsHud(const bool &enabled)
{
    sendCommand(QString("\"vars.hud\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsIdleBanRounds(const int &rounds)
{
    if (rounds == -1) {
        sendCommand("vars.idleBanRounds");
    } else {
        sendCommand(QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds));
    }
}

void BF4Connection::sendVarsIdleTimeout(const int &seconds)
{
    if (seconds == -1) {
        sendCommand("vars.idleTimeout");
    } else {
        sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void BF4Connection::sendVarsKillCam()
{
    sendCommand("vars.killCam");
}

void BF4Connection::sendVarsKillCam(const bool &enabled)
{
    sendCommand(QString("\"vars.killCam\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsMaxPlayers(const int &players)
{
    if (players == -1) {
        sendCommand("vars.maxPlayers");
    } else {
        sendCommand(QString("\"vars.maxPlayers\" \"%1\"").arg(players));
    }
}

void BF4Connection::sendVarsMaxSpectators(const int &spectators)
{
    if (spectators == -1) {
        sendCommand("vars.maxSpectators");
    } else {
        sendCommand(QString("\"vars.maxSpectators\" \"%1\"").arg(spectators));
    }
}

void BF4Connection::sendVarsMiniMap()
{
    sendCommand("vars.");
}

void BF4Connection::sendVarsMiniMap(const bool &enabled)
{
    sendCommand(QString("\"vars.\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsMiniMapSpotting()
{
    sendCommand("vars.miniMap");
}

void BF4Connection::sendVarsMiniMapSpotting(const bool &enabled)
{
    sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsMpExperience(const QString &experience)
{
    if (experience == 0) {
        sendCommand("vars.mpExperience");
    } else {
        sendCommand(QString("\"vars.mpExperience\" \"%1\"").arg(experience));
    }
}

void BF4Connection::sendVarsNameTag()
{
    sendCommand("vars.nameTag");
}

void BF4Connection::sendVarsNameTag(const bool &enabled)
{
    sendCommand(QString("\"vars.nameTag\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsOnlySquadLeaderSpawn()
{
    sendCommand("vars.onlySquadLeaderSpawn");
}

void BF4Connection::sendVarsOnlySquadLeaderSpawn(const bool &enabled)
{
    sendCommand(QString("\"vars.onlySquadLeaderSpawn\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsPlayerRespawnTime(const int &respawnTime)
{
    if (respawnTime == -1) {
        sendCommand("vars.playerRespawnTime");
    } else {
        sendCommand(QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime));
    }
}

void BF4Connection::sendVarsPreset(const QString &serverPreset, const bool &lockPresetSetting)
{
    if (serverPreset == 0 && lockPresetSetting == 0) {
        sendCommand("vars.preset");
    } else {
        sendCommand(QString("\"vars.preset\" \"%1\" \"%2\"").arg(serverPreset, toString(lockPresetSetting)));
    }
}

void BF4Connection::sendVarsRegenerateHealth()
{
    sendCommand("vars.regenerateHealth");
}

void BF4Connection::sendVarsRegenerateHealth(const bool &enabled)
{
    sendCommand(QString("\"vars.regenerateHealth\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsRoundLockdownCountdown(const int &seconds)
{
    if (seconds == -1) {
        sendCommand("vars.roundLockdownCountdown");
    } else {
        sendCommand(QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds));
    }
}

void BF4Connection::sendVarsRoundRestartPlayerCount(const int &players)
{
    if (players == -1) {
        sendCommand("vars.roundRestartPlayerCount");
    } else {
        sendCommand(QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4Connection::sendVarsRoundStartPlayerCount(const int &players)
{
    if (players == -1) {
        sendCommand("vars.roundStartPlayerCount");
    } else {
        sendCommand(QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4Connection::sendVarsRoundTimeLimit(const int &percent)
{
    if (percent == -1) {
        sendCommand("vars.roundTimeLimit");
    } else {
        sendCommand(QString("\"vars.roundTimeLimit\" \"%1\"").arg(percent));
    }
}

void BF4Connection::sendVarsRoundWarmupTimeout(const int &timeout)
{
    if (timeout == -1) {
        sendCommand("vars.roundWarmupTimeout");
    } else {
        sendCommand(QString("\"vars.roundWarmupTimeout\" \"%1\"").arg(timeout));
    }
}

void BF4Connection::sendVarsServerDescription(const QString &description)
{
    if (description == 0) {
        sendCommand("vars.serverDescription");
    } else {
        sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void BF4Connection::sendVarsServerMessage(const QString &message)
{
    if (message == 0) {
        sendCommand("vars.serverMessage");
    } else {
        sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(message));
    }
}

void BF4Connection::sendVarsServerName(const QString &name)
{
    if (name == 0) {
        sendCommand("vars.serverName");
    } else {
        sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void BF4Connection::sendVarsServerType(const QString &type)
{
    if (type == 0) {
        sendCommand("vars.serverType");
    } else {
        sendCommand(QString("\"vars.serverType\" \"%1\"").arg(type));
    }
}

void BF4Connection::sendVarsSoldierHealth(const int &percent)
{
    if (percent == -1) {
        sendCommand("vars.soldierHealth");
    } else {
        sendCommand(QString("\"vars.soldierHealth\" \"%1\"").arg(percent));
    }
}

void BF4Connection::sendVarsTeamFactionOverride(const int &teamId, const int &factionId)
{
    if (teamId == -1 && factionId == -1) {
        sendCommand("vars.teamFactionOverride");
    } else {
        sendCommand(QString("\"vars.teamFactionOverride\" \"%1\" \"%1\"").arg(teamId, factionId));
    }
}

void BF4Connection::sendVarsTeamKillCountForKick(const int &count)
{
    if (count == -1) {
        sendCommand("vars.teamKillCountForKick");
    } else {
        sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void BF4Connection::sendVarsTeamKillKickForBan(const int &count)
{
    if (count == -1) {
        sendCommand("vars.teamKillKickForBan");
    } else {
        sendCommand(QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count));
    }
}

void BF4Connection::sendVarsTeamKillValueDecreasePerSecond(const int &count)
{
    if (count == -1) {
        sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void BF4Connection::sendVarsTeamKillValueForKick(const int &count)
{
    if (count == -1) {
        sendCommand("vars.teamKillValueForKick");
    } else {
        sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void BF4Connection::sendVarsTeamKillValueIncrease(const int &count)
{
    if (count == -1) {
        sendCommand("vars.teamKillValueIncrease");
    } else {
        sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

void BF4Connection::sendVarsTicketBleedRate(const int &percent)
{
    if (percent == -1) {
        sendCommand("vars.ticketBleedRate");
    } else {
        sendCommand(QString("\"vars.ticketBleedRate\" \"%1\"").arg(percent));
    }
}

void BF4Connection::sendVarsUnlockMode(const QString &type)
{
    if (type == 0) {
        sendCommand("vars.unlockMode");
    } else {
        sendCommand(QString("\"vars.unlockMode\" \"%1\"").arg(type));
    }
}

void BF4Connection::sendVarsVehicleSpawnAllowed()
{
    sendCommand("vars.vehicleSpawnAllowed");
}

void BF4Connection::sendVarsVehicleSpawnAllowed(const bool &enabled)
{
    sendCommand(QString("\"vars.vehicleSpawnAllowed\" \"%1\"").arg(toString(enabled)));
}

void BF4Connection::sendVarsVehicleSpawnDelay(const int &percent)
{
    if (percent == -1) {
        sendCommand("vars.vehicleSpawnDelay");
    } else {
        sendCommand(QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent));
    }
}

/* Parse */

// Events
void BF4Connection::responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void BF4Connection::responsePlayerDisconnectEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onPlayerDisconnectEvent());
}

void BF4Connection::responsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void BF4Connection::responsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BF4Connection::responsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();

    emit (onPlayerSpawnEvent(player, teamId));
}

void BF4Connection::responsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BF4Connection::responsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BF4Connection::responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BF4Connection::responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BF4Connection::responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BF4Connection::responseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseServerLevelLoadedEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void BF4Connection::responseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void BF4Connection::responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BF4Connection::responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

// Commands
void BF4Connection::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

void BF4Connection::responseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

//    OK OpenRcon 0 8 CarrierAssaultLarge0 XP2_001 0 2 2 65000 65000 0  true true false 382974 382964 82.145.47.195:25200 v1.883 | A1390 C2.333 true EU ams GB 0 IN_GAME

//    OK <serverName: string>
//    <current playercount: integer>
//    <effective max playercount: integer>
//    <current gamemode: string>
//    <current map: string>
//    <roundsPlayed: integer>
//    <roundsTotal: string>
//    <scores: team scores>
//    <onlineState: online state>
//    <ranked: boolean>
//    <punkBuster: boolean>
//    <hasGamePassword: boolean>
//    <serverUpTime: seconds>
//    <roundTime: seconds>
//    <gameIpAndPort: IpPortPair>
//    <punkBusterVersion: string>
//    <joinQueueEnabled: boolean>
//    <region: string>
//    <closestPingSite: string>
//    <country: string>
//    <matchMakingEnabled: boolean>
//    <blazePlayerCount: integer>
//    <blazeGameState: string>

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();
        int playerCount = toInt(packet.getWord(2).getContent());
        int maxPlayerCount = toInt(packet.getWord(3).getContent());
        QString gamemode = packet.getWord(4).getContent();
        QString currentMap = packet.getWord(5).getContent();
        int roundsPlayed = toInt(packet.getWord(6).getContent());
        int roundsTotal = toInt(packet.getWord(7).getContent());

        // Parsing team scores.
        int entries = toInt(packet.getWord(8).getContent());
        QList<int> scoreList;
        int targetScore;

        for (int i = 9; i < entries; i++) {
            scoreList.append(toInt(packet.getWord(i).getContent()));

            if (i == entries) {
                targetScore = toInt(packet.getWord(i + 1).getContent());
            }
        }

        TeamScores scores(scoreList,
                          targetScore);

        // Parsing online state.
        QString onlineStateString = packet.getWord(12).getContent();
        OnlineState onlineState;

        if (onlineStateString == "NotConnected") {
            onlineState = OnlineState::NotConnected;
        } else if (onlineStateString == "ConnectedToBackend") {
            onlineState = OnlineState::ConnectedToBackend;
        } else if (onlineStateString == "AcceptingPlayers") {
            onlineState = OnlineState::AcceptingPlayers;
        }

        bool ranked = toBool(packet.getWord(13).getContent());
        bool punkBuster = toBool(packet.getWord(14).getContent());
        bool hasGamePassword = toBool(packet.getWord(15).getContent());
        int serverUpTime = toInt(packet.getWord(16).getContent());
        int roundTime = toInt(packet.getWord(17).getContent());
        QString gameIpAndPort = packet.getWord(18).getContent();
        QString punkBusterVersion = packet.getWord(19).getContent();
        bool joinQueueEnabled = toBool(packet.getWord(20).getContent());
        QString region = packet.getWord(21).getContent();
        QString closestPingSite = packet.getWord(22).getContent();
        QString country = packet.getWord(23).getContent();

        bool matchMakingEnabled = toBool(packet.getWord(21).getContent());
        int blazePlayerCount = toInt(packet.getWord(22).getContent());
        QString blazeGameState = packet.getWord(23).getContent();

        BF4ServerInfo serverInfo(
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

void BF4Connection::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF4Connection::responseCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = getPlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onListPlayersCommand(playerList, playerSubset));
}

void BF4Connection::responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = getPlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onAdminListPlayersCommand(playerList, playerSubset));
}

void BF4Connection::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminShutDownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseBanListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseFairFightActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseFairFightDeactivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseFairFightIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

void BF4Connection::responseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
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

void BF4Connection::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(isActive));
    }
}

void BF4Connection::responsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

void BF4Connection::responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSpectatorListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSpectatorListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSpectatorListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::responseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSpectatorListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsAlwaysAllowSpectatorsCommand(enabled));
    }
}

void BF4Connection::responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsCommanderCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsCommanderCommand(enabled));
    }
}

void BF4Connection::responseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
    }
}

void BF4Connection::responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

void BF4Connection::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
    }
}

void BF4Connection::responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void BF4Connection::responseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int spectatorCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4Connection::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsMpExperienceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsPresetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

void BF4Connection::responseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverMessage = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(serverMessage));
    }
}

void BF4Connection::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

void BF4Connection::responseVarsServerTypeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsServerTypeCommand(type));
    }
}

void BF4Connection::responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeam1FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeam2FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeam3FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeam4FactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

QList<PlayerInfo> BF4Connection::getPlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();
    QList<PlayerInfo> playerList;

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
            int teamId = toInt(list.at(2));
            int squadId = toInt(list.at(3));
            int kills = toInt(list.at(4));
            int deaths = toInt(list.at(5));
            int score = toInt(list.at(6));
            int rank = toInt(list.at(7));
            int ping = toInt(list.at(8));

            playerList.append(PlayerInfo(name, guid, teamId, squadId, kills, deaths, score, rank, ping));
        }
    }

    return playerList;
}

PlayerSubset BF4Connection::getPlayerSubset(const QString &playerSubsetString)
{
    PlayerSubset playerSubset;

    if (playerSubsetString == "all") {
        playerSubset = PlayerSubset::All;
    } else if (playerSubsetString == "team") {
        playerSubset = PlayerSubset::Team;
    } else if (playerSubsetString == "squad") {
        playerSubset = PlayerSubset::Squad;
    } else if (playerSubsetString == "player") {
        playerSubset = PlayerSubset::Player;
    }

    return playerSubset;
}
