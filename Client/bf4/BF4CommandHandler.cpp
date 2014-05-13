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
#include "BF4CommandHandler.h"

BF4CommandHandler::BF4CommandHandler(FrostbiteConnection *parent) : Frostbite2CommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

bool BF4CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF4CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "player.onDisconnect",                 &BF4CommandHandler::parsePlayerDisconnectEvent },
        { "server.onMaxPlayerCountChange",       &BF4CommandHandler::parseServerMaxPlayerCountChangeEvent },
        { "server.onLevelLoaded",                &BF4CommandHandler::parseServerLevelLoadedEvent },

        /* Commands */
        // Misc
        { "serverInfo",                          &BF4CommandHandler::parseServerInfoCommand },
        { "currentLevel",                        &BF4CommandHandler::parseCurrentLevelCommand },
        { "listPlayers",                         &BF4CommandHandler::parseListPlayersCommand },

        // Admin
        { "admin.listPlayers",                   &BF4CommandHandler::parseAdminListPlayersCommand },
        { "admin.shutDown",                      nullptr /*&BF4CommandHandler::parseAdminShutDownCommand*/ },

        // BanList
        { "banList.add",                         nullptr /*&BF4CommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                       nullptr /*&BF4CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        &BF4CommandHandler::parseBanListListCommand },
        { "banList.load",                        nullptr /*&BF4CommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                      nullptr /*&BF4CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                        nullptr /*&BF4CommandHandler::parseBanListSaveCommand*/ },

        // FairFight
        { "fairFight.activate",                  nullptr /*&BF4CommandHandler::parseFairFightActivateCommand*/ },
        { "fairFight.deactivate",                nullptr /*&BF4CommandHandler::parseFairFightDeactivateCommand*/ },
        { "fairFight.isActive",                  &BF4CommandHandler::parseFairFightIsActiveCommand },

        // MapList
        { "mapList.add",                         nullptr /*&BF4CommandHandler::parseMapListAddCommand*/ },
        { "mapList.availableMaps",               &BF4CommandHandler::parseMapListAvailableMapsCommand },
        { "mapList.clear",                       nullptr /*&BF4CommandHandler::parseMapListClearCommand*/ },
        { "mapList.endRound",                    nullptr /*&BF4CommandHandler::parseMapListEndRoundCommand*/ },
        { "mapList.getMapIndices",               &BF4CommandHandler::parseMapListGetMapIndicesCommand },
        { "mapList.getRounds",                   &BF4CommandHandler::parseMapListGetRoundsCommand },
        { "mapList.list",                        &BF4CommandHandler::parseMapListListCommand },
        { "mapList.load",                        nullptr /*&BF4CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                      nullptr /*&BF4CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.restartRound",                nullptr /*&BF4CommandHandler::parseMapListRestartRoundCommand*/ },
        { "mapList.runNextRound",                nullptr /*&BF4CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.save",                        nullptr /*&BF4CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.setNextMapIndex",             nullptr /*&BF4CommandHandler::parseMapListSetNextMapIndexCommand*/ },

        // Reserved Slots
        { "reservedSlotsList.add",               nullptr /*&BF4CommandHandler::parseReservedSlotsListAddCommand*/ },
        { "reservedSlotsList.aggressiveJoin",    &BF4CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        { "reservedSlotsList.clear",             nullptr /*&BF4CommandHandler::parseReservedSlotsListClearCommand*/ },
        { "reservedSlotsList.list",              &BF4CommandHandler::parseReservedSlotsListListCommand },
        { "reservedSlotsList.load",              nullptr /*&BF4CommandHandler::parseReservedSlotsListLoadCommand*/ },
        { "reservedSlotsList.remove",            nullptr /*&BF4CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        { "reservedSlotsList.save",              nullptr /*&BF4CommandHandler::parseReservedSlotsListSaveCommand*/ },

        // Spectator List
        { "spectatorList.add",                   nullptr /*&BF4CommandHandler::parseSpectatorListAddCommand*/ },
        { "spectatorList.clear",                 nullptr /*&BF4CommandHandler::parseSpectatorListClearCommand*/ },
        { "spectatorList.list",                  &BF4CommandHandler::parseSpectatorListListCommand },
        { "spectatorList.remove",                nullptr /*&BF4CommandHandler::parseSpectatorListRemoveCommand*/ },
        { "spectatorList.save",                  nullptr /*&BF4CommandHandler::parseSpectatorListSaveCommand*/ },

        // Squad
        { "squad.leader",                        &BF4CommandHandler::parseSquadLeaderCommand },
        { "squad.listActive",                    nullptr /*&BF4CommandHandler::parseSquadListActiveCommand*/ },
        { "squad.listPlayers",                   &BF4CommandHandler::parseSquadListPlayersCommand },
        { "squad.private",                       &BF4CommandHandler::parseSquadPrivateCommand },

        // Vars
        { "vars.3dSpotting",                     &BF4CommandHandler::parseVars3dSpottingCommand },
        { "vars.3pCam",                          &BF4CommandHandler::parseVars3pCamCommand },
        { "vars.alwaysAllowSpectators",          &BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand },
        { "vars.autoBalance",                    &BF4CommandHandler::parseVarsAutoBalanceCommand },
        { "vars.bulletDamage",                   &BF4CommandHandler::parseVarsBulletDamageCommand },
        { "vars.commander",                      &BF4CommandHandler::parseVarsCommanderCommand },
        { "vars.forceReloadWholeMags",           &BF4CommandHandler::parseVarsForceReloadWholeMagsCommand },
        { "vars.friendlyFire",                   &BF4CommandHandler::parseVarsFriendlyFireCommand },
        { "vars.gameModeCounter",                &BF4CommandHandler::parseVarsGameModeCounterCommand },
        { "vars.gamePassword",                   &BF4CommandHandler::parseVarsGamePasswordCommand },
        { "vars.hitIndicatorsEnabled",           &BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand },
        { "vars.hud",                            &BF4CommandHandler::parseVarsHudCommand },
        { "vars.idleBanRounds",                  &BF4CommandHandler::parseVarsIdleBanRoundsCommand },
        { "vars.idleTimeout",                    &BF4CommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.killCam",                        &BF4CommandHandler::parseVarsKillCamCommand },
        { "vars.maxPlayers",                     &BF4CommandHandler::parseVarsMaxPlayersCommand },
        { "vars.maxSpectators",                  &BF4CommandHandler::parseVarsMaxSpectatorsCommand },
        { "vars.miniMap",                        &BF4CommandHandler::parseVarsMiniMapCommand },
        { "vars.miniMapSpotting",                &BF4CommandHandler::parseVarsMiniMapSpottingCommand },
        { "vars.mpExperience",                   &BF4CommandHandler::parseVarsMpExperienceCommand },
        { "vars.nameTag",                        &BF4CommandHandler::parseVarsNameTagCommand },
        { "vars.onlySquadLeaderSpawn",           &BF4CommandHandler::parseVarsOnlySquadLeaderSpawnCommand },
        { "vars.playerRespawnTime",              &BF4CommandHandler::parseVarsPlayerRespawnTimeCommand },
        { "vars.preset",                         &BF4CommandHandler::parseVarsPresetCommand },
        { "vars.regenerateHealth",               &BF4CommandHandler::parseVarsRegenerateHealthCommand },
        { "vars.roundLockdownCountdown",         &BF4CommandHandler::parseVarsRoundLockdownCountdownCommand },
        { "vars.roundRestartPlayerCount",        &BF4CommandHandler::parseVarsRoundRestartPlayerCountCommand },
        { "vars.roundStartPlayerCount",          &BF4CommandHandler::parseVarsRoundStartPlayerCountCommand },
        { "vars.roundTimeLimit",                 &BF4CommandHandler::parseVarsRoundTimeLimitCommand },
        { "vars.roundWarmupTimeout",             &BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand },
        { "vars.serverDescription",              &BF4CommandHandler::parseVarsServerDescriptionCommand },
        { "vars.serverMessage",                  &BF4CommandHandler::parseVarsServerMessageCommand },
        { "vars.serverName",                     &BF4CommandHandler::parseVarsServerNameCommand },
        { "vars.serverType",                     &BF4CommandHandler::parseVarsServerTypeCommand },
        { "vars.soldierHealth",                  &BF4CommandHandler::parseVarsSoldierHealthCommand },
        { "vars.teamFactionOverride",            &BF4CommandHandler::parseVarsTeamFactionOverrideCommand },
        { "vars.teamKillCountForKick",           &BF4CommandHandler::parseVarsTeamKillCountForKickCommand },
        { "vars.teamKillKickForBan",             &BF4CommandHandler::parseVarsTeamKillKickForBanCommand },
        { "vars.teamKillValueDecreasePerSecond", &BF4CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },
        { "vars.teamKillValueForKick",           &BF4CommandHandler::parseVarsTeamKillValueForKickCommand },
        { "vars.teamKillValueIncrease",          &BF4CommandHandler::parseVarsTeamKillValueIncreaseCommand },
        { "vars.ticketBleedRate",                &BF4CommandHandler::parseVarsTicketBleedRateCommand },
        { "vars.unlockMode",                     &BF4CommandHandler::parseVarsUnlockModeCommand },
        { "vars.vehicleSpawnAllowed",            &BF4CommandHandler::parseVarsVehicleSpawnAllowedCommand },
        { "vars.vehicleSpawnDelay",              &BF4CommandHandler::parseVarsVehicleSpawnDelayCommand }
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    } else {
        return Frostbite2CommandHandler::parse(request, packet, lastSentPacket);
    }
}

/* Send commands */
// Misc
void BF4CommandHandler::sendServerInfoCommand()
{
    con->sendCommand("serverInfo");
}

void BF4CommandHandler::sendCurrentLevelCommand()
{
    con->sendCommand("currentLevel");
}

void BF4CommandHandler::sendListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        con->sendCommand("\"listPlayers\" \"all\"");
    }
}

// Admin
void BF4CommandHandler::sendAdminListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BF4CommandHandler::sendAdminShutdownCommand()
{
    con->sendCommand("admin.shutDown");
}

void BF4CommandHandler::sendAdminShutdownCommand(bool graceful)
{
    con->sendCommand(QString("\"admin.shutDown\" \"%1\"").arg(FrostbiteUtils::toString(graceful)));
}

void BF4CommandHandler::sendAdminShutdownCommand(bool graceful, int seconds)
{
    con->sendCommand(QString("\"admin.shutDown\" \"%1\" \"%2\"").arg(FrostbiteUtils::toString(graceful)).arg(seconds));
}

// Banning
void BF4CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    con->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void BF4CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutType = useRounds ? "rounds" : "seconds";

    con->sendCommand(QString("banList.add %1 %2 %3 %4 %5").arg(idType, id, timeoutType).arg(FrostbiteUtils::toString(timeout), reason));
    sendBanListListCommand();
}

void BF4CommandHandler::sendBanListClearCommand()
{
    con->sendCommand("banList.clear");
}

void BF4CommandHandler::sendBanListListCommand(int index)
{
    if (index == 0) {
        con->sendCommand("banList.list");
    } else {
        con->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void BF4CommandHandler::sendBanListLoadCommand()
{
    con->sendCommand("banList.load");
}

void BF4CommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void BF4CommandHandler::sendBanListSaveCommand()
{
    con->sendCommand("banList.save");
}

// FairFight
void BF4CommandHandler::sendFairFightActivateCommand()
{
    con->sendCommand("fairFight.activate");
}

void BF4CommandHandler::sendFairFightDeactivateCommand()
{
    con->sendCommand("fairfight.deactivate");
}

void BF4CommandHandler::sendFairFightIsActiveCommand()
{
    con->sendCommand("fairFight.isActive");
}

// Maplist
void BF4CommandHandler::sendMapListAdd(const QString &level, const QString &gameMode, int rounds, int offSet)
{
    con->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListList();
}

void BF4CommandHandler::sendMapListAvailableMaps(const QString &filter)
{
    con->sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void BF4CommandHandler::sendMapListClear()
{
    con->sendCommand("mapList.clear");
}

void BF4CommandHandler::sendMapListEndRound(int teamId)
{
    con->sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void BF4CommandHandler::sendMapListGetMapIndices()
{
    con->sendCommand("mapList.getMapIndices");
}

void BF4CommandHandler::sendMapListGetRounds()
{
    con->sendCommand("mapList.getRounds");
}

void BF4CommandHandler::sendMapListList(int index)
{
    if (index == 0) {
        con->sendCommand("mapList.list");
    } else {
        con->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void BF4CommandHandler::sendMapListLoad()
{
    con->sendCommand("mapList.load");
}

void BF4CommandHandler::sendMapListRemove(int index)
{
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
}

void BF4CommandHandler::sendMapListRestartRound()
{
    con->sendCommand("mapList.restartRound");
}

void BF4CommandHandler::sendMapListRunNextRound()
{
    con->sendCommand("mapList.runNextRound");
}

void BF4CommandHandler::sendMapListSave()
{
    con->sendCommand("mapList.save");
}

void BF4CommandHandler::sendMapListSetNextMapIndex(int index)
{
    con->sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

// Reserved Slots
void BF4CommandHandler::sendReservedSlotsListAdd(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4CommandHandler::sendReservedSlotsListAggressiveJoin()
{
    con->sendCommand("reservedSlotsList.aggressiveJoin");
}

void BF4CommandHandler::sendReservedSlotsListAggressiveJoin(bool enabled)
{
    con->sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendReservedSlotsListClear()
{
    con->sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListList();
}

void BF4CommandHandler::sendReservedSlotsListList()
{
    con->sendCommand("reservedSlotsList.list");
}

void BF4CommandHandler::sendReservedSlotsListLoad()
{
    con->sendCommand("reservedSlotsList.load");
    sendReservedSlotsListList();
}

void BF4CommandHandler::sendReservedSlotsListRemove(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4CommandHandler::sendReservedSlotsListSave()
{
    con->sendCommand("reservedSlotsList.save");
    sendReservedSlotsListList();
}

// Spectator list
void BF4CommandHandler::sendSpectatorListAdd(const QString &player)
{
    con->sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4CommandHandler::sendSpectatorListClear()
{
    con->sendCommand("spectatorList.clear");
    sendSpectatorListList();
}

void BF4CommandHandler::sendSpectatorListList(int index)
{
    if (index == 0) {
        con->sendCommand("spectatorList.list");
    } else {
        con->sendCommand(QString("\"spectatorList.list\" \"%1\"").arg(index));
    }
}

void BF4CommandHandler::sendSpectatorListRemove(const QString &player)
{
    con->sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4CommandHandler::sendSpectatorListSave()
{
    con->sendCommand("spectatorList.save");
    sendSpectatorListList();
}

// Squad
void BF4CommandHandler::sendSquadLeader(int teamId, int squadId, const QString &player)
{
    con->sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void BF4CommandHandler::sendSquadListActive(int teamId)
{
    con->sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void BF4CommandHandler::sendSquadListPlayers(int teamId, int squadId)
{
    con->sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void BF4CommandHandler::sendSquadPrivate(int teamId, int squadId, bool isPrivate)
{
    con->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}

// Variables
void BF4CommandHandler::sendVars3dSpotting()
{
    con->sendCommand("vars.3dSpotting");
}

void BF4CommandHandler::sendVars3dSpotting(bool enabled)
{
    con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVars3pCam()
{
    con->sendCommand("vars.3pCam");
}

void BF4CommandHandler::sendVars3pCam(bool enabled)
{
    con->sendCommand(QString("\"vars.3pCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsAlwaysAllowSpectators()
{
    con->sendCommand("vars.alwaysAllowSpectators");
}

void BF4CommandHandler::sendVarsAlwaysAllowSpectators(bool enabled)
{
    con->sendCommand(QString("\"vars.alwaysAllowSpectators\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsAutoBalance()
{
    con->sendCommand("vars.autoBalance");
}

void BF4CommandHandler::sendVarsAutoBalance(bool enabled)
{
    con->sendCommand(QString("\"vars.autoBalance\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsBulletDamage(int damage)
{
    if (damage == -1) {
        con->sendCommand("vars.bulletDamage");
    } else {
        con->sendCommand(QString("\"vars.bulletDamage\" \"%1\"").arg(damage));
    }
}

void BF4CommandHandler::sendVarsCommander()
{
    con->sendCommand("vars.commander");
}

void BF4CommandHandler::sendVarsCommander(bool enabled)
{
    con->sendCommand(QString("\"vars.commander\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsForceReloadWholeMags()
{
    con->sendCommand("vars.forceReloadWholeMags");
}

void BF4CommandHandler::sendVarsForceReloadWholeMags(bool enabled)
{
    con->sendCommand(QString("\"vars.forceReloadWholeMags\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsFriendlyFire()
{
    con->sendCommand("vars.friendlyFire");
}

void BF4CommandHandler::sendVarsFriendlyFire(bool enabled)
{
    con->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsGameModeCounter(int scale)
{
    if (scale == -1) {
        con->sendCommand("vars.gameModeCounter");
    } else {
        con->sendCommand(QString("\"vars.gameModeCounter\" \"%1\"").arg(scale));
    }
}

void BF4CommandHandler::sendVarsGamePassword(const QString &password)
{
    if (password == 0) {
        con->sendCommand("vars.gamePassword");
    } else {
        con->sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabled()
{
    con->sendCommand("vars.hitIndicatorsEnabled");
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabled(bool enabled)
{
    con->sendCommand(QString("\"vars.hitIndicatorsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsHud()
{
    con->sendCommand("vars.hud");
}

void BF4CommandHandler::sendVarsHud(bool enabled)
{
    con->sendCommand(QString("\"vars.hud\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsIdleBanRounds(int rounds)
{
    if (rounds == -1) {
        con->sendCommand("vars.idleBanRounds");
    } else {
        con->sendCommand(QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds));
    }
}

void BF4CommandHandler::sendVarsIdleTimeout(int seconds)
{
    if (seconds == -1) {
        con->sendCommand("vars.idleTimeout");
    } else {
        con->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void BF4CommandHandler::sendVarsKillCam()
{
    con->sendCommand("vars.killCam");
}

void BF4CommandHandler::sendVarsKillCam(bool enabled)
{
    con->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsMaxPlayers(int players)
{
    if (players == -1) {
        con->sendCommand("vars.maxPlayers");
    } else {
        con->sendCommand(QString("\"vars.maxPlayers\" \"%1\"").arg(players));
    }
}

void BF4CommandHandler::sendVarsMaxSpectators(int spectators)
{
    if (spectators == -1) {
        con->sendCommand("vars.maxSpectators");
    } else {
        con->sendCommand(QString("\"vars.maxSpectators\" \"%1\"").arg(spectators));
    }
}

void BF4CommandHandler::sendVarsMiniMap()
{
    con->sendCommand("vars.");
}

void BF4CommandHandler::sendVarsMiniMap(bool enabled)
{
    con->sendCommand(QString("\"vars.\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsMiniMapSpotting()
{
    con->sendCommand("vars.miniMap");
}

void BF4CommandHandler::sendVarsMiniMapSpotting(bool enabled)
{
    con->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsMpExperience(const QString &experience)
{
    if (experience == 0) {
        con->sendCommand("vars.mpExperience");
    } else {
        con->sendCommand(QString("\"vars.mpExperience\" \"%1\"").arg(experience));
    }
}

void BF4CommandHandler::sendVarsNameTag()
{
    con->sendCommand("vars.nameTag");
}

void BF4CommandHandler::sendVarsNameTag(bool enabled)
{
    con->sendCommand(QString("\"vars.nameTag\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsOnlySquadLeaderSpawn()
{
    con->sendCommand("vars.onlySquadLeaderSpawn");
}

void BF4CommandHandler::sendVarsOnlySquadLeaderSpawn(bool enabled)
{
    con->sendCommand(QString("\"vars.onlySquadLeaderSpawn\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsPlayerRespawnTime(int respawnTime)
{
    if (respawnTime == -1) {
        con->sendCommand("vars.playerRespawnTime");
    } else {
        con->sendCommand(QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime));
    }
}

void BF4CommandHandler::sendVarsPreset(const QString &serverPreset, bool lockPresetSetting)
{
    if (serverPreset == 0 && lockPresetSetting == 0) {
        con->sendCommand("vars.preset");
    } else {
        con->sendCommand(QString("\"vars.preset\" \"%1\" \"%2\"").arg(serverPreset, FrostbiteUtils::toString(lockPresetSetting)));
    }
}

void BF4CommandHandler::sendVarsRegenerateHealth()
{
    con->sendCommand("vars.regenerateHealth");
}

void BF4CommandHandler::sendVarsRegenerateHealth(bool enabled)
{
    con->sendCommand(QString("\"vars.regenerateHealth\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsRoundLockdownCountdown(int seconds)
{
    if (seconds == -1) {
        con->sendCommand("vars.roundLockdownCountdown");
    } else {
        con->sendCommand(QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds));
    }
}

void BF4CommandHandler::sendVarsRoundRestartPlayerCount(int players)
{
    if (players == -1) {
        con->sendCommand("vars.roundRestartPlayerCount");
    } else {
        con->sendCommand(QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4CommandHandler::sendVarsRoundStartPlayerCount(int players)
{
    if (players == -1) {
        con->sendCommand("vars.roundStartPlayerCount");
    } else {
        con->sendCommand(QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4CommandHandler::sendVarsRoundTimeLimit(int percent)
{
    if (percent == -1) {
        con->sendCommand("vars.roundTimeLimit");
    } else {
        con->sendCommand(QString("\"vars.roundTimeLimit\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsRoundWarmupTimeout(int timeout)
{
    if (timeout == -1) {
        con->sendCommand("vars.roundWarmupTimeout");
    } else {
        con->sendCommand(QString("\"vars.roundWarmupTimeout\" \"%1\"").arg(timeout));
    }
}

void BF4CommandHandler::sendVarsServerDescription(const QString &description)
{
    if (description == 0) {
        con->sendCommand("vars.serverDescription");
    } else {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void BF4CommandHandler::sendVarsServerMessage(const QString &message)
{
    if (message == 0) {
        con->sendCommand("vars.serverMessage");
    } else {
        con->sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(message));
    }
}

void BF4CommandHandler::sendVarsServerName(const QString &name)
{
    if (name == 0) {
        con->sendCommand("vars.serverName");
    } else {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void BF4CommandHandler::sendVarsServerType(const QString &type)
{
    if (type == 0) {
        con->sendCommand("vars.serverType");
    } else {
        con->sendCommand(QString("\"vars.serverType\" \"%1\"").arg(type));
    }
}

void BF4CommandHandler::sendVarsSoldierHealth(int percent)
{
    if (percent == -1) {
        con->sendCommand("vars.soldierHealth");
    } else {
        con->sendCommand(QString("\"vars.soldierHealth\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsTeamFactionOverride(int teamId, int factionId)
{
    if (teamId == -1 && factionId == -1) {
        con->sendCommand("vars.teamFactionOverride");
    } else {
        con->sendCommand(QString("\"vars.teamFactionOverride\" \"%1\" \"%1\"").arg(teamId, factionId));
    }
}

void BF4CommandHandler::sendVarsTeamKillCountForKick(int count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillCountForKick");
    } else {
        con->sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsTeamKillKickForBan(int count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillKickForBan");
    } else {
        con->sendCommand(QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsTeamKillValueDecreasePerSecond(int count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsTeamKillValueForKick(int count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueForKick");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsTeamKillValueIncrease(int count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueIncrease");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsTicketBleedRate(int percent)
{
    if (percent == -1) {
        con->sendCommand("vars.ticketBleedRate");
    } else {
        con->sendCommand(QString("\"vars.ticketBleedRate\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsUnlockMode(const QString &type)
{
    if (type == 0) {
        con->sendCommand("vars.unlockMode");
    } else {
        con->sendCommand(QString("\"vars.unlockMode\" \"%1\"").arg(type));
    }
}

void BF4CommandHandler::sendVarsVehicleSpawnAllowed()
{
    con->sendCommand("vars.vehicleSpawnAllowed");
}

void BF4CommandHandler::sendVarsVehicleSpawnAllowed(bool enabled)
{
    con->sendCommand(QString("\"vars.vehicleSpawnAllowed\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsVehicleSpawnDelay(int percent)
{
    if (percent == -1) {
        con->sendCommand("vars.vehicleSpawnDelay");
    } else {
        con->sendCommand(QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent));
    }
}

/* Parse events */
void BF4CommandHandler::parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerDisconnectEvent(player));
}

void BF4CommandHandler::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    // TODO: Implement this, not implemented yet as i don't have any docs for this and i could trigger the event.
}

void BF4CommandHandler::parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

/* Parse commands */
void BF4CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
        int entries = toInt(packet.getWord(8).getContent());
        QList<int> scoreList;
        int targetScore;

        for (int i = 9; i < entries; i++) {
            scoreList.append(toInt(packet.getWord(i).getContent()));

            if (i == entries) {
                targetScore = toInt(packet.getWord(i + 1).getContent());
            }
        }

        TeamScores scores(scoreList, targetScore);

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

        bool ranked = FrostbiteUtils::toBool(packet.getWord(13).getContent());
        bool punkBuster = FrostbiteUtils::toBool(packet.getWord(14).getContent());
        bool hasGamePassword = FrostbiteUtils::toBool(packet.getWord(15).getContent());
        int serverUpTime = FrostbiteUtils::toInt(packet.getWord(16).getContent());
        int roundTime = FrostbiteUtils::toInt(packet.getWord(17).getContent());
        QString gameIpAndPort = packet.getWord(18).getContent();
        QString punkBusterVersion = packet.getWord(19).getContent();
        bool joinQueueEnabled = FrostbiteUtils::toBool(packet.getWord(20).getContent());
        QString region = packet.getWord(21).getContent();
        QString closestPingSite = packet.getWord(22).getContent();
        QString country = packet.getWord(23).getContent();

        bool matchMakingEnabled = FrostbiteUtils::toBool(packet.getWord(21).getContent());
        int blazePlayerCount = FrostbiteUtils::toInt(packet.getWord(22).getContent());
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

void BF4CommandHandler::parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString level = packet.getWord(1).getContent();

        emit (onCurrentLevelCommand(level));
    }
}

void BF4CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onListPlayersCommand(playerList, playerSubset));
}

void BF4CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubset playerSubset = getPlayerSubset(lastSentPacket.getWord(1).getContent());

    emit (onAdminListPlayersCommand(playerList, playerSubset));
}

//void BF4CommandHandler::parseAdminShutDownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// BanList
/*void BF4CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

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

/*void BF4CommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// FairFight
/*void BF4CommandHandler::parseFairFightActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

// MapList
/*void BF4CommandHandler::parseMapListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

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

/*void BF4CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentMapIndex = toInt(packet.getWord(1).getContent());
        int nextMapIndex = toInt(packet.getWord(2).getContent());

        emit (onMapListGetMapIndicesCommand(currentMapIndex, nextMapIndex));
    }
}

void BF4CommandHandler::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentRound = toInt(packet.getWord(1).getContent());
        int totalRounds = toInt(packet.getWord(2).getContent());

        emit (onMapListGetRoundsCommand(currentRound, totalRounds));
    }
}

void BF4CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

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

/*void BF4CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Reserved Slots
/*void BF4CommandHandler::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

/*void BF4CommandHandler::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListListCommand(reservedSlotList));
    }
}

/*void BF4CommandHandler::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// SpectatorList
/*void BF4CommandHandler::parseSpectatorListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseSpectatorListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList spectatorList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            spectatorList.append(packet.getWord(i).getContent());
        }

        emit (onSpectatorListListCommand(spectatorList));
    }
}

/*void BF4CommandHandler::parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Squad
void BF4CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString player = packet.getWord(1).getContent();

        emit (onSquadLeaderCommand(player));
    }
}

/*void BF4CommandHandler::parseSquadListActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BF4CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

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

void BF4CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isPrivate = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onSquadPrivateCommand(isPrivate));
    }
}

// Vars
void BF4CommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3dSpottingCommand(enabled));
    }
}

void BF4CommandHandler::parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3pCamCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAlwaysAllowSpectatorsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAutoBalanceCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsBulletDamageCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsCommanderCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsForceReloadWholeMagsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int scale = toInt(packet.getWord(1).getContent());

        emit (onVarsGameModeCounterCommand(scale));
    }
}

void BF4CommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onVarsGamePasswordCommand(password));
    }
}

void BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHitIndicatorsEnabledCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHudCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int rounds = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleBanRoundsCommand(rounds));
    }
}

void BF4CommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(seconds));
    }
}

void BF4CommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void BF4CommandHandler::parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int spectatorCount = toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4CommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapSpottingCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString experience = packet.getWord(1).getContent();

        emit (onVarsMpExperienceCommand(experience));
    }
}

void BF4CommandHandler::parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsNameTagCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsOnlySquadLeaderSpawnCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int respawnTime = toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerRespawnTimeCommand(respawnTime));
    }
}

void BF4CommandHandler::parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        QString serverPreset = packet.getWord(1).getContent();
        bool lockPresetSetting = FrostbiteUtils::toBool(packet.getWord(2).getContent());

        emit (onVarsPresetCommand(serverPreset, lockPresetSetting));
    }
}

void BF4CommandHandler::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsRegenerateHealthCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int seconds = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundLockdownCountdownCommand(seconds));
    }
}

void BF4CommandHandler::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int players = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundRestartPlayerCountCommand(players));
    }
}

void BF4CommandHandler::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1 && lastPacketSent.getWordCount() > 1) {
        int players = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundStartPlayerCountCommand(players));
    }
}

void BF4CommandHandler::parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percentage = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundTimeLimitCommand(percentage));
    }
}

void BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int time = toInt(packet.getWord(1).getContent());

        emit (onVarsRoundWarmupTimeoutCommand(time));
    }
}

void BF4CommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(description));
    }
}

void BF4CommandHandler::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString message = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(message));
    }
}

void BF4CommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(name));
    }
}

void BF4CommandHandler::parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsServerTypeCommand(type));
    }
}

void BF4CommandHandler::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int health = toInt(packet.getWord(1).getContent());

        emit (onVarsSoldierHealthCommand(health));
    }
}

void BF4CommandHandler::parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int team1 = toInt(packet.getWord(1).getContent());
        int team2 = toInt(packet.getWord(2).getContent());
        int team3 = toInt(packet.getWord(3).getContent());
        int team4 = toInt(packet.getWord(4).getContent());

        emit (onVarsTeamFactionOverrideCommand(team1, team2, team3, team4));
    }
}

void BF4CommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillCountForKickCommand(count));
    }
}

void BF4CommandHandler::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillKickForBanCommand(count));
    }
}

void BF4CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void BF4CommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueForKickCommand(count));
    }
}

void BF4CommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueIncreaseCommand(count));
    }
}

void BF4CommandHandler::parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = toInt(packet.getWord(1).getContent());

        emit (onVarsTicketBleedRateCommand(percent));
    }
}

void BF4CommandHandler::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsUnlockModeCommand(type));
    }
}

void BF4CommandHandler::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnAllowedCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int delay = toInt(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnDelayCommand(delay));
    }
}

QList<PlayerInfo> BF4CommandHandler::parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
