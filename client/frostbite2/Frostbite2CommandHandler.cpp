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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "Frostbite2CommandHandler.h"
#include "FrostbiteUtils.h"

Frostbite2CommandHandler::Frostbite2CommandHandler(FrostbiteConnection *parent) : FrostbiteCommandHandler(parent)
{

}

Frostbite2CommandHandler::~Frostbite2CommandHandler()
{

}

bool Frostbite2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (Frostbite2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "player.onAuthenticated",              &Frostbite2CommandHandler::parsePlayerAuthenticatedEvent },
        { "player.onJoin",                       &Frostbite2CommandHandler::parsePlayerJoinEvent },
        { "player.onSpawn",                      &Frostbite2CommandHandler::parsePlayerSpawnEvent },
        { "player.onKill",                       &Frostbite2CommandHandler::parsePlayerKillEvent },
        { "server.onMaxPlayerCountChange",       &Frostbite2CommandHandler::parseServerMaxPlayerCountChangeEvent },
        { "server.onLevelLoaded",                &Frostbite2CommandHandler::parseServerLevelLoadedEvent },

        /* Commands */
        // Misc

        // Admin
        { "admin.eventsEnabled",                 &Frostbite2CommandHandler::parseAdminEventsEnabledCommand },
        { "admin.help",                          &Frostbite2CommandHandler::parseAdminHelpCommand },
        { "admin.kickPlayer",                    nullptr /*&Frostbite2CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                    nullptr /*&Frostbite2CommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.movePlayer",                    nullptr /*&Frostbite2CommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.password",                      &Frostbite2CommandHandler::parseAdminPasswordCommand },
        { "admin.say",                           nullptr /*&Frostbite2CommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                          nullptr /*&Frostbite2CommandHandler::parseAdminYellCommand*/ },

        // MapList
        { "mapList.add",                         nullptr /*&Frostbite2CommandHandler::parseMapListAddCommand*/ },
        { "mapList.availableMaps",               &Frostbite2CommandHandler::parseMapListAvailableMapsCommand },
        { "mapList.clear",                       nullptr /*&Frostbite2CommandHandler::parseMapListClearCommand*/ },
        { "mapList.endRound",                    nullptr /*&Frostbite2CommandHandler::parseMapListEndRoundCommand*/ },
        { "mapList.getMapIndices",               &Frostbite2CommandHandler::parseMapListGetMapIndicesCommand },
        { "mapList.getRounds",                   &Frostbite2CommandHandler::parseMapListGetRoundsCommand },
        { "mapList.list",                        &Frostbite2CommandHandler::parseMapListListCommand },
        { "mapList.load",                        nullptr /*&Frostbite2CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                      nullptr /*&Frostbite2CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.restartRound",                nullptr /*&Frostbite2CommandHandler::parseMapListRestartRoundCommand*/ },
        { "mapList.runNextRound",                nullptr /*&Frostbite2CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.save",                        nullptr /*&Frostbite2CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.setNextMapIndex",             nullptr /*&Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand*/ },

        // Player
        { "player.idleDuration",                 &Frostbite2CommandHandler::parsePlayerIdleDurationCommand },
        { "player.isAlive",                      &Frostbite2CommandHandler::parsePlayerIsAliveCommand },
        { "player.ping",                         &Frostbite2CommandHandler::parsePlayerPingCommand },

        // PunkBuster
        { "punkBuster.activate",                 nullptr /*&Frostbite2CommandHandler::parsePunkBusterActivateCommand*/ },
        { "punkBuster.isActive",                 &Frostbite2CommandHandler::parsePunkBusterIsActiveCommand },

        // Reserved Slots
        { "reservedSlotsList.add",               nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListAddCommand*/ },
        { "reservedSlotsList.aggressiveJoin",    &Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        { "reservedSlotsList.clear",             nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListClearCommand*/ },
        { "reservedSlotsList.list",              &Frostbite2CommandHandler::parseReservedSlotsListListCommand },
        { "reservedSlotsList.load",              nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListLoadCommand*/ },
        { "reservedSlotsList.remove",            nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        { "reservedSlotsList.save",              nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListSaveCommand*/ },

        // Squad
        { "squad.leader",                        &Frostbite2CommandHandler::parseSquadLeaderCommand },
        { "squad.listActive",                    nullptr /*&Frostbite2CommandHandler::parseSquadListActiveCommand*/ },
        { "squad.listPlayers",                   &Frostbite2CommandHandler::parseSquadListPlayersCommand },
        { "squad.private",                       &Frostbite2CommandHandler::parseSquadPrivateCommand },

        // Variables
        { "vars.3pCam",                          &Frostbite2CommandHandler::parseVars3pCamCommand },
        { "vars.autoBalance",                    &Frostbite2CommandHandler::parseVarsAutoBalanceCommand },
        { "vars.bulletDamage",                   &Frostbite2CommandHandler::parseVarsBulletDamageCommand },
        { "vars.gameModeCounter",                &Frostbite2CommandHandler::parseVarsGameModeCounterCommand },
        { "vars.hud",                            &Frostbite2CommandHandler::parseVarsHudCommand },
        { "vars.idleBanRounds",                  &Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand },
        { "vars.maxPlayers",                     &Frostbite2CommandHandler::parseVarsMaxPlayersCommand },
        { "vars.nameTag",                        &Frostbite2CommandHandler::parseVarsNameTagCommand },
        { "vars.onlySquadLeaderSpawn",           &Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand },
        { "vars.playerRespawnTime",              &Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand },
        { "vars.regenerateHealth",               &Frostbite2CommandHandler::parseVarsRegenerateHealthCommand },
        { "vars.roundLockdownCountdown",         &Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand },
        { "vars.roundRestartPlayerCount",        &Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand },
        { "vars.roundStartPlayerCount",          &Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand },
        { "vars.serverMessage",                  &Frostbite2CommandHandler::parseVarsServerMessageCommand },
        { "vars.soldierHealth",                  &Frostbite2CommandHandler::parseVarsSoldierHealthCommand },
        { "vars.teamKillKickForBan",             &Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand },
        { "vars.unlockMode",                     &Frostbite2CommandHandler::parseVarsUnlockModeCommand },
        { "vars.vehicleSpawnAllowed",            &Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand },
        { "vars.vehicleSpawnDelay",              &Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand }
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    } else {
        return FrostbiteCommandHandler::parse(request, packet, lastSentPacket);
    }
}

/* Send commands */
// Admin
void Frostbite2CommandHandler::sendAdminEventsEnabledCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendAdminHelpCommand()
{
    m_connection->sendCommand("admin.help");
}

void Frostbite2CommandHandler::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    m_connection->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void Frostbite2CommandHandler::sendAdminKillPlayerCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill)
{
    m_connection->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void Frostbite2CommandHandler::sendAdminPasswordCommand(const QString &password)
{
    if (password.isEmpty()) {
        m_connection->sendCommand("admin.password");
    } else {
        m_connection->sendCommand(QString("\"admin.password\" \"%1\"").arg(password));
    }
}

void Frostbite2CommandHandler::sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset, int parameter)
{
    if (playerSubset == PlayerSubset::All) {
        m_connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(message, getPlayerSubsetString(playerSubset)));
    } else {
        m_connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(message, getPlayerSubsetString(playerSubset)).arg(parameter));
    }
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset, int parameter)
{
    sendAdminYellCommand(message, 10, playerSubset, parameter);
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, int duration, const PlayerSubset &playerSubset, int parameter)
{
    if (message.length() <= 256) {
        if (playerSubset == PlayerSubset::All) {
            m_connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(getPlayerSubsetString(playerSubset)));
        } else {
            m_connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(message).arg(duration).arg(getPlayerSubsetString(playerSubset)).arg(parameter));
        }
    }
}

// Maplist
void Frostbite2CommandHandler::sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet)
{
    m_connection->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListAvailableMapsCommand(const QString &filter)
{
    m_connection->sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void Frostbite2CommandHandler::sendMapListClearCommand()
{
    m_connection->sendCommand("mapList.clear");
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListEndRoundCommand(int teamId)
{
    m_connection->sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendMapListGetMapIndicesCommand()
{
    m_connection->sendCommand("mapList.getMapIndices");
}

void Frostbite2CommandHandler::sendMapListGetRoundsCommand()
{
    m_connection->sendCommand("mapList.getRounds");
}

void Frostbite2CommandHandler::sendMapListListCommand(int index)
{
    if (index == 0) {
        m_connection->sendCommand("mapList.list");
    } else {
        m_connection->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void Frostbite2CommandHandler::sendMapListLoadCommand()
{
    m_connection->sendCommand("mapList.load");
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListRemoveCommand(int index)
{
    m_connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListRestartRoundCommand()
{
    m_connection->sendCommand("mapList.restartRound");
}

void Frostbite2CommandHandler::sendMapListRunNextRoundCommand()
{
    m_connection->sendCommand("mapList.runNextRound");
}

void Frostbite2CommandHandler::sendMapListSaveCommand()
{
    m_connection->sendCommand("mapList.save");
}

void Frostbite2CommandHandler::sendMapListSetNextMapIndexCommand(int index)
{
    m_connection->sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

// Player
void Frostbite2CommandHandler::sendPlayerIdleDurationCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"player.idleDuration\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerIsAliveCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"player.isAlive\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerPingCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"player.ping\" \"%1\"").arg(player));
}

// PunkBuster
void Frostbite2CommandHandler::sendPunkBusterActivateCommand()
{
    m_connection->sendCommand("punkBuster.activate");
}

void Frostbite2CommandHandler::sendPunkBusterIsActiveCommand()
{
    m_connection->sendCommand("punkBuster.isActive");
}

// Reserved Slots
void Frostbite2CommandHandler::sendReservedSlotsListAddCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand()
{
    m_connection->sendCommand("reservedSlotsList.aggressiveJoin");
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendReservedSlotsListClearCommand()
{
    m_connection->sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListListCommand()
{
    m_connection->sendCommand("reservedSlotsList.list");
}

void Frostbite2CommandHandler::sendReservedSlotsListLoadCommand()
{
    m_connection->sendCommand("reservedSlotsList.load");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListRemoveCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListSaveCommand()
{
    m_connection->sendCommand("reservedSlotsList.save");
    sendReservedSlotsListListCommand();
}

// Squad
void Frostbite2CommandHandler::sendSquadLeaderCommand(int teamId, int squadId, const QString &player)
{
    m_connection->sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void Frostbite2CommandHandler::sendSquadListActiveCommand(int teamId)
{
    m_connection->sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendSquadListPlayersCommand(int teamId, int squadId)
{
    m_connection->sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void Frostbite2CommandHandler::sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate)
{
    m_connection->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}

// Vars
void Frostbite2CommandHandler::sendVars3dSpottingCommand()
{
    m_connection->sendCommand("vars.3dSpotting");
}

void Frostbite2CommandHandler::sendVars3dSpottingCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVars3pCamCommand()
{
    m_connection->sendCommand("vars.3pCam");
}

void Frostbite2CommandHandler::sendVars3pCamCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.3pCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsAutoBalanceCommand()
{
    m_connection->sendCommand("vars.autoBalance");
}

void Frostbite2CommandHandler::sendVarsAutoBalanceCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.autoBalance\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsBulletDamageCommand(int damage)
{
    if (damage == -1) {
        m_connection->sendCommand("vars.bulletDamage");
    } else {
        m_connection->sendCommand(QString("\"vars.bulletDamage\" \"%1\"").arg(damage));
    }
}

void Frostbite2CommandHandler::sendVarsFriendlyFireCommand()
{
    m_connection->sendCommand("vars.friendlyFire");
}

void Frostbite2CommandHandler::sendVarsFriendlyFireCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsGameModeCounterCommand(int scale)
{
    if (scale == -1) {
        m_connection->sendCommand("vars.gameModeCounter");
    } else {
        m_connection->sendCommand(QString("\"vars.gameModeCounter\" \"%1\"").arg(scale));
    }
}

void Frostbite2CommandHandler::sendVarsGamePasswordCommand(const QString &password)
{
    if (password == 0) {
        m_connection->sendCommand("vars.gamePassword");
    } else {
        m_connection->sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
}

void Frostbite2CommandHandler::sendVarsHudCommand()
{
    m_connection->sendCommand("vars.hud");
}

void Frostbite2CommandHandler::sendVarsHudCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.hud\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsIdleBanRoundsCommand(int rounds)
{
    if (rounds == -1) {
        m_connection->sendCommand("vars.idleBanRounds");
    } else {
        m_connection->sendCommand(QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds));
    }
}

void Frostbite2CommandHandler::sendVarsIdleTimeoutCommand(int seconds)
{
    if (seconds == -1) {
        m_connection->sendCommand("vars.idleTimeout");
    } else {
        m_connection->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void Frostbite2CommandHandler::sendVarsKillCamCommand()
{
    m_connection->sendCommand("vars.killCam");
}

void Frostbite2CommandHandler::sendVarsKillCamCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsMaxPlayersCommand(int players)
{
    if (players == -1) {
        m_connection->sendCommand("vars.maxPlayers");
    } else {
        m_connection->sendCommand(QString("\"vars.maxPlayers\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsMiniMapCommand()
{
    m_connection->sendCommand("vars.miniMap");
}

void Frostbite2CommandHandler::sendVarsMiniMapCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsMiniMapSpottingCommand()
{
    m_connection->sendCommand("vars.miniMapSpotting");
}

void Frostbite2CommandHandler::sendVarsMiniMapSpottingCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsNameTagCommand()
{
    m_connection->sendCommand("vars.nameTag");
}

void Frostbite2CommandHandler::sendVarsNameTagCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.nameTag\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsOnlySquadLeaderSpawnCommand()
{
    m_connection->sendCommand("vars.onlySquadLeaderSpawn");
}

void Frostbite2CommandHandler::sendVarsOnlySquadLeaderSpawnCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.onlySquadLeaderSpawn\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsPlayerRespawnTimeCommand(int respawnTime)
{
    if (respawnTime == -1) {
        m_connection->sendCommand("vars.playerRespawnTime");
    } else {
        m_connection->sendCommand(QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime));
    }
}

void Frostbite2CommandHandler::sendVarsRegenerateHealthCommand()
{
    m_connection->sendCommand("vars.regenerateHealth");
}

void Frostbite2CommandHandler::sendVarsRegenerateHealthCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.regenerateHealth\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsRoundLockdownCountdownCommand(int seconds)
{
    if (seconds == -1) {
        m_connection->sendCommand("vars.roundLockdownCountdown");
    } else {
        m_connection->sendCommand(QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds));
    }
}

void Frostbite2CommandHandler::sendVarsRoundRestartPlayerCountCommand(int players)
{
    if (players == -1) {
        m_connection->sendCommand("vars.roundRestartPlayerCount");
    } else {
        m_connection->sendCommand(QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsRoundStartPlayerCountCommand(int players)
{
    if (players == -1) {
        m_connection->sendCommand("vars.roundStartPlayerCount");
    } else {
        m_connection->sendCommand(QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsServerDescriptionCommand(const QString &description)
{
    if (description == 0) {
        m_connection->sendCommand("vars.serverDescription");
    } else {
        m_connection->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void Frostbite2CommandHandler::sendVarsServerMessageCommand(const QString &message)
{
    if (message == 0) {
        m_connection->sendCommand("vars.serverMessage");
    } else {
        m_connection->sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(message));
    }
}

void Frostbite2CommandHandler::sendVarsServerNameCommand(const QString &name)
{
    if (name == 0) {
        m_connection->sendCommand("vars.serverName");
    } else {
        m_connection->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void Frostbite2CommandHandler::sendVarsSoldierHealthCommand(int percent)
{
    if (percent == -1) {
        m_connection->sendCommand("vars.soldierHealth");
    } else {
        m_connection->sendCommand(QString("\"vars.soldierHealth\" \"%1\"").arg(percent));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillCountForKickCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.teamKillCountForKick");
    } else {
        m_connection->sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillKickForBanCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.teamKillKickForBan");
    } else {
        m_connection->sendCommand(QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueDecreasePerSecondCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        m_connection->sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueForKickCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.teamKillValueForKick");
    } else {
        m_connection->sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueIncreaseCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.teamKillValueIncrease");
    } else {
        m_connection->sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsUnlockModeCommand(const QString &type)
{
    if (type == 0) {
        m_connection->sendCommand("vars.unlockMode");
    } else {
        m_connection->sendCommand(QString("\"vars.unlockMode\" \"%1\"").arg(type));
    }
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnAllowedCommand()
{
    m_connection->sendCommand("vars.vehicleSpawnAllowed");
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnAllowedCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.vehicleSpawnAllowed\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnDelayCommand(int percent)
{
    if (percent == -1) {
        m_connection->sendCommand("vars.vehicleSpawnDelay");
    } else {
        m_connection->sendCommand(QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent));
    }
}

/* Parse events */
void Frostbite2CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void Frostbite2CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void Frostbite2CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

    emit (onPlayerSpawnEvent(player, teamId));
}

void Frostbite2CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void Frostbite2CommandHandler::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    // TODO: Implement this, not implemented yet as i don't have any docs for this and i could trigger the event.
}

void Frostbite2CommandHandler::parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

/* Parse commands */
// Admin
void Frostbite2CommandHandler::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onAdminEventsEnabledCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList commandList;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            commandList.append(packet.getWord(i).getContent());
        }

        emit (onAdminHelpCommand(commandList));
    }
}

//void Frostbite2CommandHandler::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void Frostbite2CommandHandler::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void Frostbite2CommandHandler::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onAdminPasswordCommand(password));
    }
}

//void Frostbite2CommandHandler::parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// MapList
//void Frostbite2CommandHandler::parseMapListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

//void Frostbite2CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentMapIndex = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        int nextMapIndex = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onMapListGetMapIndicesCommand(currentMapIndex, nextMapIndex));
    }
}

void Frostbite2CommandHandler::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentRound = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        int totalRounds = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onMapListGetRoundsCommand(currentRound, totalRounds));
    }
}

void Frostbite2CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

//void Frostbite2CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}


// Player
void Frostbite2CommandHandler::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        float idleDuration = FrostbiteUtils::toFloat(packet.getWord(1).getContent());

        emit (onPlayerIdleDurationCommand(idleDuration));
    }
}

void Frostbite2CommandHandler::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool alive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPlayerIsAliveCommand(alive));
    }
}

void Frostbite2CommandHandler::parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString player = packet.getWord(1).getContent();
        int ping = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onPlayerPingCommand(player, ping));
    }
}

// PunkBuster
//void Frostbite2CommandHandler::parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool active = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(active));
    }
}

// Reserved Slots
//void Frostbite2CommandHandler::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

//void Frostbite2CommandHandler::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

//void Frostbite2CommandHandler::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// Squad
void Frostbite2CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString player = packet.getWord(1).getContent();

        emit (onSquadLeaderCommand(player));
    }
}

//void Frostbite2CommandHandler::parseSquadListActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        QStringList playerList;

        for (int i = 2; i < playerCount; i++) {
            playerList.append(packet.getWord(i).getContent());
        }

        emit (onSquadListPlayersCommand(playerList));
    }
}

void Frostbite2CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isPrivate = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onSquadPrivateCommand(isPrivate));
    }
}

// Variables
void Frostbite2CommandHandler::parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3pCamCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAutoBalanceCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsBulletDamageCommand(percent));
    }
}

void Frostbite2CommandHandler::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsGameModeCounterCommand(percent));
    }
}

void Frostbite2CommandHandler::parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHudCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int rounds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsIdleBanRoundsCommand(rounds));
    }
}

void Frostbite2CommandHandler::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void Frostbite2CommandHandler::parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsNameTagCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsOnlySquadLeaderSpawnCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int respawnTime = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerRespawnTimeCommand(respawnTime));
    }
}

void Frostbite2CommandHandler::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsRegenerateHealthCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundLockdownCountdownCommand(seconds));
    }
}

void Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int players = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundRestartPlayerCountCommand(players));
    }
}

void Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int players = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundStartPlayerCountCommand(players));
    }
}

void Frostbite2CommandHandler::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString message = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(message));
    }
}

void Frostbite2CommandHandler::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int health = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsSoldierHealthCommand(health));
    }
}

void Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillKickForBanCommand(count));
    }
}

void Frostbite2CommandHandler::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsUnlockModeCommand(type));
    }
}

void Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnAllowedCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int delay = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnDelayCommand(delay));
    }
}

PlayerSubset Frostbite2CommandHandler::getPlayerSubset(const QString &playerSubsetString)
{
    if (playerSubsetString == "all") {
        return PlayerSubset::All;
    } else if (playerSubsetString == "team") {
        return PlayerSubset::Team;
    } else if (playerSubsetString == "squad") {
        return PlayerSubset::Squad;
    } else if (playerSubsetString == "player") {
        return PlayerSubset::Player;
    } else {
        return PlayerSubset::Unknown;
    }
}

QString Frostbite2CommandHandler::getPlayerSubsetString(const PlayerSubset &playerSubset)
{
    switch (playerSubset) {
    case PlayerSubset::All:
        return "all";
        break;

    case PlayerSubset::Team:
        return "team";
        break;

    case PlayerSubset::Squad:
        return "squad";
        break;

    case PlayerSubset::Player:
        return "player";
        break;

    default:
        return QString();
    }
}
