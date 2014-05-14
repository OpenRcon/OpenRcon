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
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "BF3CommandHandler.h"

BF3CommandHandler::BF3CommandHandler(FrostbiteConnection *parent) : Frostbite2CommandHandler(parent)
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
        { "server.onMaxPlayerCountChange",       &BF3CommandHandler::parseMaxPlayerCountChangeEvent },
        { "server.onLevelLoaded",                &BF3CommandHandler::parseLevelLoadedEvent },

        /* Commands */
        // Misc
        { "serverinfo",                          nullptr /*&BF3CommandHandler::parseServerInfoCommand*/ },
        { "admin.help",                          nullptr /*&BF3CommandHandler::parseAdminHelpCommand*/ },
        { "listPlayers",                         nullptr /*&BF3CommandHandler::parseListPlayersCommand*/ },

        // Admin
        { "admin.effectiveMaxPlayers",           nullptr /*&BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand*/ },
        { "admin.listPlayers",                   nullptr /*&BF3CommandHandler::parseAdminListPlayersCommand*/ },

        // BanList
        { "banList.load",                        nullptr /*&BF3CommandHandler::parseBanListLoadCommand*/ },
        { "banList.save",                        nullptr /*&BF3CommandHandler::parseBanListSaveCommand*/ },
        { "banList.add",                         nullptr /*&BF3CommandHandler::parseBanListAddCommand*/ },
        { "banList.remove",                      nullptr /*&BF3CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.clear",                       nullptr /*&BF3CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        nullptr /*&BF3CommandHandler::parseBanListListCommand*/ },

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
        return Frostbite2CommandHandler::parse(request, packet, lastSentPacket);
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

/* Parse events */
void BF3CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void BF3CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void BF3CommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BF3CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

    emit (onPlayerSpawnEvent(player, teamId));
}

void BF3CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BF3CommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BF3CommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BF3CommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BF3CommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BF3CommandHandler::parseMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    // TODO: Implement this, not implemented yet as i don't have any docs for this and i could trigger the event.
}

void BF3CommandHandler::parseLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void BF3CommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void BF3CommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BF3CommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
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

// Admin
//void BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void BF3CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket)
//}

// Squad
/*void BF3CommandHandler::parseSquadListActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
