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

#include "BF3CommandHandler.h"

BF3CommandHandler::BF3CommandHandler(BF3Connection *parent) : FrostbiteCommandHandler(parent)
{

}

BF3CommandHandler::~BF3CommandHandler()
{

}

bool BF3CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF3CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */

        /* Commands */
        // Misc
        { "serverinfo",                          nullptr /*&BF3CommandHandler::parseServerInfoCommand*/ },
        { "admin.help",                          nullptr /*&BF3CommandHandler::parseAdminHelpCommand*/ },
        { "listPlayers",                         nullptr /*&BF3CommandHandler::parseListPlayersCommand*/ },

        // Admin
        { "admin.eventsEnabled",                 nullptr /*&BF3CommandHandler::parseAdminEventsEnabledCommand*/ },
        { "admin.password",                      nullptr /*&BF3CommandHandler::parseAdminPasswordCommand*/ },
        { "admin.effectiveMaxPlayers",           nullptr /*&BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand*/ },
        { "admin.say",                           nullptr /*&BF3CommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                          nullptr /*&BF3CommandHandler::parseAdminYellCommand*/ },
        { "admin.kickPlayer",                    nullptr /*&BF3CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.listPlayers",                   nullptr /*&BF3CommandHandler::parseAdminListPlayersCommand*/ },
        { "admin.movePlayer",                    nullptr /*&BF3CommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.killPlayer",                    nullptr /*&BF3CommandHandler::parseAdminKillPlayerCommand*/ },

        // Player
        { "player.idleDuration",                 nullptr /*&BF3CommandHandler::parsePlayerIdleDurationCommand*/ },
        { "player.isAlive",                      nullptr /*&BF3CommandHandler::parsePlayerIsAliveCommand*/ },
        { "player.ping",                         nullptr /*&BF3CommandHandler::parsePlayerPingCommand*/ },

        // Squad
        { "squad.listActive",                    nullptr /*&BF3CommandHandler::parseSquadListActiveCommand*/ },
        { "squad.listPlayers",                   nullptr /*&BF3CommandHandler::parseSquadListPlayersCommand*/ },
        { "squad.private",                       nullptr /*&BF3CommandHandler::parseSquadPrivateCommand*/ },
        { "squad.leader",                        nullptr /*&BF3CommandHandler::parseSquadLeaderCommand*/ },

        // PunkBuster
        { "punkBuster.isActive",                 nullptr /*&BF3CommandHandler::parsePunkBusterIsActiveCommand*/ },
        { "punkBuster.activate",                 nullptr /*&BF3CommandHandler::parsePunkBusterActivateCommand*/ },
        { "punkBuster.pb_sv_command",            nullptr /*&BF3CommandHandler::parsePunkBusterPbSvCommandCommand*/ },

        // MapList
        { "banList.load",                        nullptr /*&BF3CommandHandler::parseBanListLoadCommand*/ },
        { "banList.save",                        nullptr /*&BF3CommandHandler::parseBanListSaveCommand*/ },
        { "banList.add",                         nullptr /*&BF3CommandHandler::parseBanListAddCommand*/ },
        { "banList.remove",                      nullptr /*&BF3CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.clear",                       nullptr /*&BF3CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        nullptr /*&BF3CommandHandler::parseBanListListCommand*/ },

        // Reserved Slots
        { "reservedSlotsList.load",              nullptr /*&BF3CommandHandler::parseReservedSlotsListLoadCommand*/ },
        { "reservedSlotsList.save",              nullptr /*&BF3CommandHandler::parseReservedSlotsListSaveCommand*/ },
        { "reservedSlotsList.add",               nullptr /*&BF3CommandHandler::parseReservedSlotsListAddCommand*/ },
        { "reservedSlotsList.remove",            nullptr /*&BF3CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        { "reservedSlotsList.clear",             nullptr /*&BF3CommandHandler::parseReservedSlotsListClearCommand*/ },
        { "reservedSlotsList.list",              nullptr /*&BF3CommandHandler::parseReservedSlotsListListCommand*/ },
        { "reservedSlotsList.aggressiveJoin",    nullptr /*&BF3CommandHandler::parseReservedSlotsListAggressiveJoinCommand*/ },

        // MapList
        { "mapList.load",                        nullptr /*&BF3CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.save",                        nullptr /*&BF3CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.add",                         nullptr /*&BF3CommandHandler::parseMapListAddCommand*/ },
        { "mapList.remove",                      nullptr /*&BF3CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.clear",                       nullptr /*&BF3CommandHandler::parseMapListClearCommand*/ },
        { "mapList.list",                        nullptr /*&BF3CommandHandler::parseMapListListCommand*/ },
        { "mapList.setNextMapIndex",             nullptr /*&BF3CommandHandler::parseMapListSetNextMapIndexCommand*/ },
        { "mapList.getMapIndices",               nullptr /*&BF3CommandHandler::parseMapListGetMapIndicesCommand*/ },
        { "mapList.getRounds",                   nullptr /*&BF3CommandHandler::parseMapListGetRoundsCommand*/ },
        { "mapList.endRound",                    nullptr /*&BF3CommandHandler::parseMapListEndRoundCommand*/ },
        { "mapList.runNextRound",                nullptr /*&BF3CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.restartRound",                nullptr /*&BF3CommandHandler::parseMapListRestartRoundCommand*/ },
        { "mapList.availableMaps",               nullptr /*&BF3CommandHandler::parseMapListAvailableMapsCommand*/ },

        // Vars
        { "vars.ranked",                         nullptr /*&BF3CommandHandler::parseVarsRankedCommand*/ },
        { "vars.serverName",                     nullptr /*&BF3CommandHandler::parseVarsServerNameCommand*/ },
        { "vars.gamePassword",                   nullptr /*&BF3CommandHandler::parseVarsGamePasswordCommand*/ },
        { "vars.autoBalance",                    nullptr /*&BF3CommandHandler::parseVarsAutoBalanceCommand*/ },
        { "vars.roundStartPlayerCount",          nullptr /*&BF3CommandHandler::parseVarsRoundStartPlayerCountCommand*/ },
        { "vars.roundRestartPlayerCount",        nullptr /*&BF3CommandHandler::parseVarsRoundRestartPlayerCountCommand*/ },
        { "vars.roundLockdownCountdown",         nullptr /*&BF3CommandHandler::parseVarsRoundLockdownCountdownCommand*/ },
        { "vars.serverMessage",                  nullptr /*&BF3CommandHandler::parseVarsServerMessageCommand*/ },
        { "vars.friendlyFire",                   nullptr /*&BF3CommandHandler::parseVarsFriendlyFireCommand*/ },
        { "vars.maxPlayers",                     nullptr /*&BF3CommandHandler::parseVarsMaxPlayersCommand*/ },
        { "vars.serverDescription",              nullptr /*&BF3CommandHandler::parseVarsServerDescriptionCommand*/ },
        { "vars.killCam",                        nullptr /*&BF3CommandHandler::parseVarsKillCamCommand*/ },
        { "vars.miniMap",                        nullptr /*&BF3CommandHandler::parseVarsMiniMapCommand*/ },
        { "vars.hud",                            nullptr /*&BF3CommandHandler::parseVarsHudCommand*/ },
        { "vars.crossHair",                      nullptr /*&BF3CommandHandler::parseVarsCrossHairCommand*/ },
        { "vars.3dSpotting",                     nullptr /*&BF3CommandHandler::parsevars3dSpottingCommand*/ },
        { "vars.miniMapSpotting",                nullptr /*&BF3CommandHandler::parseVarsMiniMapSpottingCommand*/ },
        { "vars.nameTag",                        nullptr /*&BF3CommandHandler::parseVarsNameTagCommand*/ },
        { "vars.3pCam",                          nullptr /*&BF3CommandHandler::parseVars3pCamCommand*/ },
        { "vars.regenerateHealth",               nullptr /*&BF3CommandHandler::parseVarsRegenerateHealthCommand*/ },
        { "vars.teamKillCountForKick",           nullptr /*&BF3CommandHandler::parseVarsTeamKillCountForKickCommand*/ },
        { "vars.teamKillValueForKick",           nullptr /*&BF3CommandHandler::parseVarsTeamKillValueForKickCommand*/ },
        { "vars.teamKillValueIncrease",          nullptr /*&BF3CommandHandler::parseVarsTeamKillValueIncreaseCommand*/ },
        { "vars.teamKillValueDecreasePerSecond", nullptr /*&BF3CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand*/ },
        { "vars.teamKillKickForBan",             nullptr /*&BF3CommandHandler::parseVarsTeamKillKickForBanCommand*/ },
        { "vars.idleTimeout",                    nullptr /*&BF3CommandHandler::parseVarsIdleTimeoutCommand*/ },
        { "vars.idleBanRounds",                  nullptr /*&BF3CommandHandler::parseVarsIdleBanRoundsCommand*/ },
        { "vars.vehicleSpawnAllowed",            nullptr /*&BF3CommandHandler::parseVarsVehicleSpawnAllowedCommand*/ },
        { "vars.vehicleSpawnDelay",              nullptr /*&BF3CommandHandler::parseVarsVehicleSpawnDelayCommand*/ },
        { "vars.soldierHealth",                  nullptr /*&BF3CommandHandler::parseVarsSoldierHealthCommand*/ },
        { "vars.playerRespawnTime",              nullptr /*&BF3CommandHandler::parseVarsPlayerRespawnTimeCommand*/ },
        { "vars.playerManDownTime",              nullptr /*&BF3CommandHandler::parseVarsPlayerManDownTimeCommand*/ },
        { "vars.bulletDamage",                   nullptr /*&BF3CommandHandler::parseVarsBulletDamageCommand*/ },
        { "vars.gameModeCounter",                nullptr /*&BF3CommandHandler::parseVarsGameModeCounterCommand*/ },
        { "vars.onlySquadLeaderSpawn",           nullptr /*&BF3CommandHandler::parseVarsOnlySquadLeaderSpawnCommand*/ },
        { "vars.unlockMode",                     nullptr /*&BF3CommandHandler::parseVarsUnlockModeCommand*/ },
        { "vars.premiumStatus",                  nullptr /*&BF3CommandHandler::parseVarsPremiumStatusCommand*/ },
        { "vars.bannerUrl",                      nullptr /*&BF3CommandHandler::parseVarsBannerUrlCommand*/ },
        { "vars.roundsPerMap",                   nullptr /*&BF3CommandHandler::parseVarsRoundsPerMapCommand*/ },
        { "vars.gunMasterWeaponsPreset",         nullptr /*&BF3CommandHandler::parseVarsGunMasterWeaponsPresetCommand*/ }
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
// Misc
void BF3CommandHandler::sendServerInfoCommand()
{
    con->sendCommand("serverInfo");
}

void BF3CommandHandler::sendCurrentLevelCommand()
{
    con->sendCommand("currentLevel");
}

void BF3CommandHandler::sendListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        con->sendCommand("\"listPlayers\" \"all\"");
    }
}

/* Parse commands */
// Misc
/*void BF3CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

/*void BF3CommandHandler::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket)
}

void BF3CommandHandler::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Player
/*void BF3CommandHandler::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}*/

// Squad
/*void BF3CommandHandler::parseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}*/

// PunkBuster
/*void BF3CommandHandler::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}*/

// BanList
/*void BF3CommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Reserved Slots
/*void BF3CommandHandler::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/


// MapList
/*void BF3CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Vars
/*void BF3CommandHandler::parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parsevars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/
