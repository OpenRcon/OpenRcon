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
        parsePlayerAuthenticatedEvent(packet);
    } else if (request == "player.onDisconnect") {
        parsePlayerDisconnectEvent(packet);
    } else if (request == "player.onJoin") {
        parsePlayerJoinEvent(packet);
    } else if (request == "player.onLeave") {
        parsePlayerLeaveEvent(packet);
    } else if (request == "player.onSpawn") {
        parsePlayerSpawnEvent(packet);
    } else if (request == "player.onKill") {
        parsePlayerKillEvent(packet);
    } else if (request == "player.onChat") {
        parsePlayerChatEvent(packet);
    } else if (request == "server.onMaxPlayerCountChange") {
        parseServerMaxPlayerCountChangeEvent(packet);
    } else if (request == "player.onSquadChange") {
        parsePlayerSquadChangeEvent(packet);
    } else if (request == "player.onTeamChange") {
        parsePlayerTeamChangeEvent(packet);
    } else if (request == "punkBuster.onMessage") {
        parsePunkBusterMessageEvent(packet);
    } else if (request == "server.onLevelLoaded") {
        parseServerLevelLoadedEvent(packet);
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
    } else if (request == "serverInfo") {
        parseServerInfoCommand(packet);
    } else if (request == "logout") {
        parseLogoutCommand(packet);
    } else if (request == "quit") {
        parseQuitCommand(packet);
    } else if (request == "version") {
        parseVersionCommand(packet);
    } else if (request == "currentLevel") {
        parseCurrentLevelCommand(packet);
    } else if (request == "listPlayers") {
        parseListPlayersCommand(packet, lastSentPacket);
    } else if (request == "admin.eventsEnabled") {
        parseAdminEventsEnabledCommand(packet);
    } else if (request == "admin.help") {
        parseAdminHelpCommand(packet);
    } else if (request == "admin.kickPlayer") {
        parseAdminKickPlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        parseAdminKillPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        parseAdminListPlayersCommand(packet, lastSentPacket);
    } else if (request == "admin.movePlayer") {
        parseAdminMovePlayerCommand(packet);
    } else if (request == "admin.password") {
        parseAdminPasswordCommand(packet);
    } else if (request == "admin.say") {
        parseAdminSayCommand(packet);
    } else if (request == "admin.shutDown") {
        parseAdminShutDownCommand(packet);
    } else if (request == "admin.yell") {
        parseAdminYellCommand(packet);
    } else if (request == "banList.add") {
        parseBanListAddCommand(packet);
    } else if (request == "banList.clear") {
        parseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        parseBanListListCommand(packet);
    } else if (request == "banList.load") {
        parseBanListLoadCommand(packet);
    } else if (request == "banList.remove") {
        parseBanListRemoveCommand(packet);
    } else if (request == "banList.save") {
        parseBanListSaveCommand(packet);
    } else if (request == "fairFight.activate") {
        parseFairFightActivateCommand(packet);
    } else if (request == "fairFight.deactivate") {
        parseFairFightDeactivateCommand(packet);
    } else if (request == "fairFight.isActive") {
        parseFairFightIsActiveCommand(packet);
    } else if (request == "mapList.add") {
        parseMapListAddCommand(packet);
    } else if (request == "mapList.availableMaps") {
        parseMapListAvailableMapsCommand(packet);
    } else if (request == "mapList.clear") {
        parseMapListClearCommand(packet);
    } else if (request == "mapList.endRound") {
        parseMapListEndRoundCommand(packet);
    } else if (request == "mapList.getMapIndices") {
        parseMapListGetMapIndicesCommand(packet);
    } else if (request == "mapList.getRounds") {
        parseMapListGetRoundsCommand(packet);
    } else if (request == "mapList.list") {
        parseMapListListCommand(packet);
    } else if (request == "mapList.load") {
        parseMapListLoadCommand(packet);
    } else if (request == "mapList.remove") {
        parseMapListRemoveCommand(packet);
    } else if (request == "mapList.restartRound") {
        parseMapListRestartRoundCommand(packet);
    } else if (request == "mapList.runNextRound") {
        parseMapListRunNextRoundCommand(packet);
    } else if (request == "mapList.save") {
        parseMapListSaveCommand(packet);
    } else if (request == "mapList.setNextMapIndex") {
        parseMapListSetNextMapIndexCommand(packet);
    } else if (request == "player.idleDuration") {
        parsePlayerIdleDurationCommand(packet);
    } else if (request == "player.isAlive") {
        parsePlayerIsAliveCommand(packet);
    } else if (request == "player.ping") {
        parsePlayerPingCommand(packet);
    } else if (request == "punkBuster.activate") {
        parsePunkBusterActivateCommand(packet);
    } else if (request == "punkBuster.isActive") {
        parsePunkBusterIsActiveCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        parsePunkBusterPbSvCommand(packet);
    } else if (request == "reservedSlotsList.add") {
        parseReservedSlotsListAddCommand(packet);
    } else if (request == "reservedSlotsList.aggressiveJoin") {
        parseReservedSlotsListAggressiveJoinCommand(packet);
    } else if (request == "reservedSlotsList.clear") {
        parseReservedSlotsListClearCommand(packet);
    } else if (request == "reservedSlotsList.list") {
        parseReservedSlotsListListCommand(packet);
    } else if (request == "reservedSlotsList.load") {
        parseReservedSlotsListLoadCommand(packet);
    } else if (request == "reservedSlotsList.remove") {
        parseReservedSlotsListRemoveCommand(packet);
    } else if (request == "reservedSlotsList.save") {
        parseReservedSlotsListSaveCommand(packet);
    } else if (request == "spectatorList.add") {
        parseSpectatorListAddCommand(packet);
    } else if (request == "spectatorList.clear") {
        parseSpectatorListClearCommand(packet);
    } else if (request == "spectatorList.list") {
        parseSpectatorListListCommand(packet);
    } else if (request == "spectatorList.remove") {
        parseSpectatorListRemoveCommand(packet);
    } else if (request == "spectatorList.save") {
        parseSpectatorListSaveCommand(packet);
    } else if (request == "squad.leader") {
        parseSquadLeaderCommand(packet);
    } else if (request == "squad.listActive") {
        parseSquadListActiveCommand(packet);
    } else if (request == "squad.listPlayers") {
        parseSquadListPlayersCommand(packet);
    } else if (request == "squad.private") {
        parseSquadPrivateCommand(packet);
    } else if (request == "vars.3dSpotting") {
        parseVars3dSpottingCommand(packet);
    } else if (request == "vars.3pCam") {
        parseVars3pCamCommand(packet);
    } else if (request == "vars.alwaysAllowSpectators") {
        parseVarsAlwaysAllowSpectatorsCommand(packet);
    } else if (request == "vars.autoBalance") {
        parseVarsAutoBalanceCommand(packet);
    } else if (request == "vars.bulletDamage") {
        parseVarsBulletDamageCommand(packet);
    } else if (request == "vars.commander") {
        parseVarsCommanderCommand(packet);
    } else if (request == "vars.forceReloadWholeMags") {
        parseVarsForceReloadWholeMagsCommand(packet);
    } else if (request == "vars.friendlyFire") {
        parseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.gameModeCounter") {
        parseVarsGameModeCounterCommand(packet);
    } else if (request == "vars.gamePassword") {
        parseVarsGamePasswordCommand(packet);
    } else if (request == "vars.hitIndicatorsEnabled") {
        parseVarsHitIndicatorsEnabledCommand(packet);
    } else if (request == "vars.hud") {
        parseVarsHudCommand(packet);
    } else if (request == "vars.idleBanRounds") {
        parseVarsIdleBanRoundsCommand(packet);
    } else if (request == "vars.idleTimeout") {
        parseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.killCam") {
        parseVarsKillCamCommand(packet);
    } else if (request == "vars.maxPlayers") {
        parseVarsMaxPlayersCommand(packet);
    } else if (request == "vars.maxSpectators") {
        parseVarsMaxSpectatorsCommand(packet);
    } else if (request == "vars.miniMap") {
        parseVarsMiniMapCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        parseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.mpExperience") {
        parseVarsMpExperienceCommand(packet);
    } else if (request == "vars.nameTag") {
        parseVarsNameTagCommand(packet);
    } else if (request == "vars.onlySquadLeaderSpawn") {
        parseVarsOnlySquadLeaderSpawnCommand(packet);
    } else if (request == "vars.playerRespawnTime") {
        parseVarsPlayerRespawnTimeCommand(packet);
    } else if (request == "vars.preset") {
        parseVarsPresetCommand(packet);
    } else if (request == "vars.regenerateHealth") {
        parseVarsRegenerateHealthCommand(packet);
    } else if (request == "vars.roundLockdownCountdown") {
        parseVarsRoundLockdownCountdownCommand(packet, lastSentPacket);
    } else if (request == "vars.roundRestartPlayerCount") {
        parseVarsRoundRestartPlayerCountCommand(packet, lastSentPacket);
    } else if (request == "vars.roundStartPlayerCount") {
        parseVarsRoundStartPlayerCountCommand(packet, lastSentPacket);
    } else if (request == "vars.roundTimeLimit") {
        parseVarsRoundTimeLimitCommand(packet);
    } else if (request == "vars.roundWarmupTimeout") {
        parseVarsRoundWarmupTimeoutCommand(packet);
    } else if (request == "vars.serverDescription") {
        parseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.serverMessage") {
        parseVarsServerMessageCommand(packet);
    } else if (request == "vars.serverName") {
        parseVarsServerNameCommand(packet);
    } else if (request == "vars.serverType") {
        parseVarsServerTypeCommand(packet);
    } else if (request == "vars.soldierHealth") {
        parseVarsSoldierHealthCommand(packet);
    } else if (request == "vars.teamFactionOverride") {
        parseVarsTeamFactionOverrideCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        parseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillKickForBan") {
        parseVarsTeamKillKickForBanCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        parseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        parseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        parseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.ticketBleedRate") {
        parseVarsTicketBleedRateCommand(packet);
    } else if (request == "vars.unlockMode") {
        parseVarsUnlockModeCommand(packet);
    } else if (request == "vars.vehicleSpawnAllowed") {
        parseVarsVehicleSpawnAllowedCommand(packet);
    } else if (request == "vars.vehicleSpawnDelay") {
        parseVarsVehicleSpawnDelayCommand(packet);
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
void BF4Connection::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void BF4Connection::parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onPlayerDisconnectEvent());
}

void BF4Connection::parsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void BF4Connection::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BF4Connection::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();

    emit (onPlayerSpawnEvent(player, teamId));
}

void BF4Connection::parsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BF4Connection::parsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BF4Connection::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BF4Connection::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BF4Connection::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BF4Connection::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet); // TODO: Implement this.
}

void BF4Connection::parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void BF4Connection::parseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void BF4Connection::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BF4Connection::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

// Commands
void BF4Connection::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(true));
    } else {
        emit (onLoginPlainTextCommand(false));
    }
}

void BF4Connection::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
        } else {
            emit (onLoginHashedCommand(false));
        }
    }
}

void BF4Connection::parseServerInfoCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::parseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF4Connection::parseCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString level = packet.getWord(1).getContent();

        emit (onCurrentLevelCommand(level));
    }
}

void BF4Connection::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onListPlayersCommand(playerList, playerSubset));
}

void BF4Connection::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onAdminEventsEnabledCommand(enabled));
    }
}

void BF4Connection::parseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList commandList;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            commandList.append(packet.getWord(i).getContent());
        }

        emit (onAdminHelpCommand(commandList));
    }
}

void BF4Connection::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onAdminListPlayersCommand(playerList, playerSubset));
}

void BF4Connection::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onAdminPasswordCommand(password));
    }
}

void BF4Connection::parseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseAdminShutDownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseBanListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::parseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseFairFightActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

void BF4Connection::parseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString value = packet.getWord(1).getContent();
        QStringList list;

        for (unsigned int i = 2; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onMapListAvailableMapsCommand(value, list));
    }
}

void BF4Connection::parseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentMapIndex = toInt(packet.getWord(1).getContent());
        int nextMapIndex = toInt(packet.getWord(2).getContent());

        emit (onMapListGetMapIndicesCommand(currentMapIndex, nextMapIndex));
    }
}

void BF4Connection::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentRound = toInt(packet.getWord(1).getContent());
        int totalRounds = toInt(packet.getWord(2).getContent());

        emit (onMapListGetRoundsCommand(currentRound, totalRounds));
    }
}

void BF4Connection::parseMapListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::parseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        float idleDuration = toFloat(packet.getWord(1).getContent());

        emit (onPlayerIdleDurationCommand(idleDuration));
    }
}

void BF4Connection::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool alive = toBool(packet.getWord(1).getContent());

        emit (onPlayerIsAliveCommand(alive));
    }
}

void BF4Connection::parsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString player = packet.getWord(1).getContent();
        int ping = toInt(packet.getWord(2).getContent());

        emit (onPlayerPingCommand(player, ping));
    }
}

void BF4Connection::parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool isActive = toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(isActive));
    }
}

void BF4Connection::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

void BF4Connection::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSpectatorListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSpectatorListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSpectatorListListCommand(const FrostbiteRconPacket &packet)
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

void BF4Connection::parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString player = packet.getWord(1).getContent();

        emit (onSquadLeaderCommand(player));
    }
}

void BF4Connection::parseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4Connection::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());
        QStringList playerList;

        for (int i = 2; i < playerCount; i++) {
            playerList.append(packet.getWord(i).getContent());
        }

        emit (onSquadListPlayersCommand(playerList));
    }
}

void BF4Connection::parseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isPrivate = toBool(packet.getWord(1).getContent());

        emit (onSquadPrivateCommand(isPrivate));
    }
}

void BF4Connection::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVars3dSpottingCommand(enabled));
    }
}

void BF4Connection::parseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVars3pCamCommand(enabled));
    }
}

void BF4Connection::parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsAlwaysAllowSpectatorsCommand(enabled));
    }
}

void BF4Connection::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsAutoBalanceCommand(enabled));
    }
}

void BF4Connection::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsBulletDamageCommand(enabled));
    }
}

void BF4Connection::parseVarsCommanderCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsCommanderCommand(enabled));
    }
}

void BF4Connection::parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsForceReloadWholeMagsCommand(enabled));
    }
}

void BF4Connection::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
    }
}

void BF4Connection::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int scale = toInt(packet.getWord(1).getContent());

        emit (onVarsGameModeCounterCommand(scale));
    }
}

void BF4Connection::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onVarsGamePasswordCommand(password));
    }
}

void BF4Connection::parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsHitIndicatorsEnabledCommand(enabled));
    }
}

void BF4Connection::parseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsHudCommand(enabled));
    }
}

void BF4Connection::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int rounds = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleBanRoundsCommand(rounds));
    }
}

void BF4Connection::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(seconds));
    }
}

void BF4Connection::parseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
    }
}

void BF4Connection::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void BF4Connection::parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int spectatorCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4Connection::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapCommand(enabled));
    }
}

void BF4Connection::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapSpottingCommand(enabled));
    }
}

void BF4Connection::parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString experience = packet.getWord(1).getContent();

        emit (onVarsMpExperienceCommand(experience));
    }
}

void BF4Connection::parseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsNameTagCommand(enabled));
    }
}

void BF4Connection::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsOnlySquadLeaderSpawnCommand(enabled));
    }
}

void BF4Connection::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int respawnTime = toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerRespawnTimeCommand(respawnTime));
    }
}

void BF4Connection::parseVarsPresetCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        QString serverPreset = packet.getWord(1).getContent();
        bool lockPresetSetting = toBool(packet.getWord(2).getContent());

        emit (onVarsPresetCommand(serverPreset, lockPresetSetting));
    }
}

void BF4Connection::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsRegenerateHealthCommand(enabled));
    }
}

void BF4Connection::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int seconds = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundLockdownCountdownCommand(seconds));
    }
}

void BF4Connection::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int players = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundRestartPlayerCountCommand(players));
    }
}

void BF4Connection::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int players = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundStartPlayerCountCommand(players));
    }
}

void BF4Connection::parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percentage = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundTimeLimitCommand(percentage));
    }
}

void BF4Connection::parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int time = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundWarmupTimeoutCommand(time));
    }
}

void BF4Connection::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(description));
    }
}

void BF4Connection::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString message = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(message));
    }
}

void BF4Connection::parseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(name));
    }
}

void BF4Connection::parseVarsServerTypeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsServerTypeCommand(type));
    }
}

void BF4Connection::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int health = toInt(packet.getWord(1).getContent());

        emit (onVarsSoldierHealthCommand(health));
    }
}

void BF4Connection::parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int team1 = toInt(packet.getWord(1).getContent());
        int team2 = toInt(packet.getWord(2).getContent());
        int team3 = toInt(packet.getWord(3).getContent());
        int team4 = toInt(packet.getWord(4).getContent());

        emit (onVarsTeamFactionOverrideCommand(team1, team2, team3, team4));
    }
}

void BF4Connection::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillCountForKickCommand(count));
    }
}

void BF4Connection::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillKickForBanCommand(count));
    }
}

void BF4Connection::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void BF4Connection::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueForKickCommand(count));
    }
}

void BF4Connection::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueIncreaseCommand(count));
    }
}

void BF4Connection::parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = toInt(packet.getWord(1).getContent());

        emit (onVarsTicketBleedRateCommand(percent));
    }
}

void BF4Connection::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsUnlockModeCommand(type));
    }
}

void BF4Connection::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = toBool(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnAllowedCommand(enabled));
    }
}

void BF4Connection::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int delay = toInt(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnDelayCommand(delay));
    }
}

QList<PlayerInfo> BF4Connection::parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
