/*
 * Copyright (C) 2016 The OpenRcon Project.
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
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) :
    FrostbiteCommandHandler(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

bool BFBC2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BFBC2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */
        { "player.onAuthenticated",                 nullptr /*&BFBC2CommandHandler::parsePlayerAuthenticatedEvent*/ },
        { "player.onJoin",                          nullptr /*&BFBC2CommandHandler::parsePlayerJoinEvent*/ },
        { "player.onLeave",                         nullptr /*&BFBC2CommandHandler::parsePlayerLeaveEvent*/ },
        { "player.onSpawn",                         nullptr /*&BFBC2CommandHandler::parsePlayerSpawnEvent*/ },
        { "player.onKill",                          nullptr /*&BFBC2CommandHandler::parsePlayerKillEvent*/ },
        { "player.onChat",                          nullptr /*&BFBC2CommandHandler::parsePlayerChatEvent*/ },
        { "player.onKicked",                        nullptr /*&BFBC2CommandHandler::parsePlayerKickedEvent*/ },
        { "player.onSquadChange",                   nullptr /*&BFBC2CommandHandler::parsePlayerSquadChangeEvent*/ },
        { "player.onTeamChange",                    nullptr /*&BFBC2CommandHandler::parsePlayerTeamChangeEvent*/ },
        { "punkBuster.onMessage",                   nullptr /*&BFBC2CommandHandler::parsePunkBusterMessageEvent*/ },
        { "punkBuster.onVersion",                   nullptr /*&BFBC2CommandHandler::parsePunkBusterVersionEvent*/ },
        { "server.onLoadingLevel",                  nullptr /*&BFBC2CommandHandler::parseServerLoadingLevelEvent*/ },
        { "server.onLevelStarted",                  nullptr /*&BFBC2CommandHandler::parseServerLevelStartedEvent*/ },
        { "server.onRoundOver",                     nullptr /*&BFBC2CommandHandler::parseServerRoundOverEvent*/ },
        { "server.onRoundOverPlayers",              nullptr /*&BFBC2CommandHandler::parseServerRoundOverPlayersEvent*/ },
        { "server.onRoundOverTeamScores",           nullptr /*&BFBC2CommandHandler::parseServerRoundOverTeamScoresEvent*/ },

        /* Commands */
        // Misc
        { "login.plainText",                        &Frostbite2CommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",                           &Frostbite2CommandHandler::parseLoginHashedCommand },
        { "serverInfo",                             &Frostbite2CommandHandler::parseServerInfoCommand },
        { "logout",                                 &Frostbite2CommandHandler::parseLogoutCommand },
        { "quit",                                   &Frostbite2CommandHandler::parseQuitCommand },
        { "version",                                &Frostbite2CommandHandler::parseVersionCommand },
        ///--{ "currentLevel",                           &Frostbite2CommandHandler::parseCurrentLevelCommand },
        { "listPlayers",                            nullptr /*&Frostbite2CommandHandler::parseListPlayersCommand*/ },

        /// BFBC2 Only.
        //eventsEnabled
        //help

        // Admin
        ///--{ "admin.eventsEnabled",                    &Frostbite2CommandHandler::parseAdminEventsEnabledCommand },
        ///--{ "admin.help",                             &Frostbite2CommandHandler::parseAdminHelpCommand },
        { "admin.kickPlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.listPlayers",                      nullptr /*&Frostbite2CommandHandler::parseAdminListPlayersCommand*/ },
        { "admin.movePlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminMovePlayerCommand*/ },
        ///--{ "admin.password",                         &Frostbite2CommandHandler::parseAdminPasswordCommand },
        { "admin.say",                              nullptr /*&Frostbite2CommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                             nullptr /*&Frostbite2CommandHandler::parseAdminYellCommand*/ },

        /// BFBC2 Only.
        //admin.runscript <filename>
        //admin.runNextRound
        //admin.restartRound
        //admin.endRound <teamID>
        //admin.currentLevel
        //admin.supportedMaps <play list>
        //admin.setPlaylist <name>
        //admin.getPlaylist
        //admin.getPlaylists

        // Banning
        { "banList.add",                            nullptr /*&Frostbite2CommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                          nullptr /*&Frostbite2CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                           &Frostbite2CommandHandler::parseBanListListCommand },
        { "banList.load",                           nullptr /*&Frostbite2CommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                         nullptr /*&Frostbite2CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                           nullptr /*&Frostbite2CommandHandler::parseBanListSaveCommand*/ },

        // Maplist
        ///--{ "mapList.add",                            nullptr /*&Frostbite2CommandHandler::parseMapListAddCommand*/ },
        ///--{ "mapList.availableMaps",                  &Frostbite2CommandHandler::parseMapListAvailableMapsCommand },
        { "mapList.clear",                          nullptr /*&Frostbite2CommandHandler::parseMapListClearCommand*/ },
        ///--{ "mapList.endRound",                       nullptr /*&Frostbite2CommandHandler::parseMapListEndRoundCommand*/ },
        ///--{ "mapList.getMapIndices",                  &Frostbite2CommandHandler::parseMapListGetMapIndicesCommand },
        ///--{ "mapList.getRounds",                      &Frostbite2CommandHandler::parseMapListGetRoundsCommand },
        { "mapList.list",                           &Frostbite2CommandHandler::parseMapListListCommand },
        { "mapList.load",                           nullptr /*&Frostbite2CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                         nullptr /*&Frostbite2CommandHandler::parseMapListRemoveCommand*/ },
        ///--{ "mapList.restartRound",                   nullptr /*&Frostbite2CommandHandler::parseMapListRestartRoundCommand*/ },
        ///--{ "mapList.runNextRound",                   nullptr /*&Frostbite2CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.save",                           nullptr /*&Frostbite2CommandHandler::parseMapListSaveCommand*/ },
        ///--{ "mapList.setNextMapIndex",                nullptr /*&Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand*/ },

        /// BFBC2 Only.
        //mapList.append <name, rounds>
        //mapList.insert <index, name, rounds>
        //mapList.nextLevelIndex [index: integer]

        // Player
        ///--{ "player.idleDuration",                    &Frostbite2CommandHandler::parsePlayerIdleDurationCommand },
        ///--{ "player.isAlive",                         &Frostbite2CommandHandler::parsePlayerIsAliveCommand },
        ///--{ "player.ping",                            &Frostbite2CommandHandler::parsePlayerPingCommand },

        // Punkbuster
        ///--{ "punkBuster.activate",                    nullptr /*&Frostbite2CommandHandler::parsePunkBusterActivateCommand*/ },
        ///--{ "punkBuster.isActive",                    &Frostbite2CommandHandler::parsePunkBusterIsActiveCommand },
        { "punkBuster.pb_sv_command",               nullptr /*&Frostbite2CommandHandler::parsePunkBusterPbSvCommand*/ },

        // Reserved Slots
        ///--{ "reservedSlotsList.add",                  nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListAddCommand*/ },
        ///--{ "reservedSlotsList.aggressiveJoin",       &Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        ///--{ "reservedSlotsList.clear",                nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListClearCommand*/ },
        ///--{ "reservedSlotsList.list",                 &Frostbite2CommandHandler::parseReservedSlotsListListCommand },
        ///--{ "reservedSlotsList.load",                 nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListLoadCommand*/ },
        ///--{ "reservedSlotsList.remove",               nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        ///--{ "reservedSlotsList.save",                 nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListSaveCommand*/ },

        /// BFBC2 Only.
        //reservedSlots.load
        //reservedSlots.save
        //reservedSlots.addPlayer <name>
        //reservedSlots.removePlayer <name>
        //reservedSlots.clear
        //reservedSlots.list

        // Squad
        ///--{ "squad.leader",                           &Frostbite2CommandHandler::parseSquadLeaderCommand },
        ///--{ "squad.listActive",                       nullptr /*&Frostbite2CommandHandler::parseSquadListActiveCommand*/ },
        ///--{ "squad.listPlayers",                      &Frostbite2CommandHandler::parseSquadListPlayersCommand },
        ///--{ "squad.private",                          &Frostbite2CommandHandler::parseSquadPrivateCommand },

        // Text Chat Moderation
        //textChatModerationList.load
        //textChatModerationList.save
        //textChatModerationList.add <moderationlevel> <name>
        //textChatModerationList.remove <name>
        //textChatModerationList.clear
        //textChatModerationList.list [startOffset]

        // Level Variables
        //levelVars.set <context> <var name> <value>
        //levelVars.get <context> <var name>
        //levelVars.evaluate <var name>
        //levelVars.clear <context> [var name]
        //levelVars.list <context> [var name]

        // Variables
        { "vars.3dSpotting",                        &Frostbite2CommandHandler::parseVars3dSpottingCommand },
        ///--{ "vars.3pCam",                             &Frostbite2CommandHandler::parseVars3pCamCommand },
        ///--{ "vars.autoBalance",                       &Frostbite2CommandHandler::parseVarsAutoBalanceCommand },
        ///--{ "vars.bulletDamage",                      &Frostbite2CommandHandler::parseVarsBulletDamageCommand },
        { "vars.friendlyFire",                      &Frostbite2CommandHandler::parseVarsFriendlyFireCommand },
        ///--{ "vars.gameModeCounter",                   &Frostbite2CommandHandler::parseVarsGameModeCounterCommand },
        { "vars.gamePassword",                      &Frostbite2CommandHandler::parseVarsGamePasswordCommand },
        ///--{ "vars.hud",                               &Frostbite2CommandHandler::parseVarsHudCommand },
        ///--{ "vars.idleBanRounds",                     &Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand },
        { "vars.idleTimeout",                       &Frostbite2CommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.killCam",                           &Frostbite2CommandHandler::parseVarsKillCamCommand },
        ///--{ "vars.maxPlayers",                        &Frostbite2CommandHandler::parseVarsMaxPlayersCommand },
        { "vars.miniMap",                           &Frostbite2CommandHandler::parseVarsMiniMapCommand },
        { "vars.miniMapSpotting",                   &Frostbite2CommandHandler::parseVarsMiniMapSpottingCommand },
        ///--{ "vars.nameTag",                           &Frostbite2CommandHandler::parseVarsNameTagCommand },
        ///--{ "vars.onlySquadLeaderSpawn",              &Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand },
        ///--{ "vars.playerRespawnTime",                 &Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand },
        ///--{ "vars.regenerateHealth",                  &Frostbite2CommandHandler::parseVarsRegenerateHealthCommand },
        ///--{ "vars.roundLockdownCountdown",            &Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand },
        ///--{ "vars.roundRestartPlayerCount",           &Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand },
        ///--{ "vars.roundStartPlayerCount",             &Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand },
        { "vars.serverDescription",                 &Frostbite2CommandHandler::parseVarsServerDescriptionCommand },
        ///--{ "vars.serverMessage",                     &Frostbite2CommandHandler::parseVarsServerMessageCommand },
        { "vars.serverName",                        &Frostbite2CommandHandler::parseVarsServerNameCommand },
        ///--{ "vars.soldierHealth",                     &Frostbite2CommandHandler::parseVarsSoldierHealthCommand },
        { "vars.teamKillCountForKick",              &Frostbite2CommandHandler::parseVarsTeamKillCountForKickCommand },
        ///--{ "vars.teamKillKickForBan",                &Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand },
        { "vars.teamKillValueDecreasePerSecond",    &Frostbite2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },
        { "vars.teamKillValueForKick",              &Frostbite2CommandHandler::parseVarsTeamKillValueForKickCommand },
        { "vars.teamKillValueIncrease",             &Frostbite2CommandHandler::parseVarsTeamKillValueIncreaseCommand },
        ///--{ "vars.unlockMode",                        &Frostbite2CommandHandler::parseVarsUnlockModeCommand },
        ///--{ "vars.vehicleSpawnAllowed",               &Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand },
        ///--{ "vars.vehicleSpawnDelay",                 &Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand },
        ///--{ "vars.gunMasterWeaponsPreset",            nullptr /*&Frostbite2CommandHandler::parseGunMasterWeaponsPresetCommand*/ }

        /// BFBC2 Only.
        //vars.adminPassword [password]
        //vars.punkBuster [enabled]
        //vars.hardCore
        //vars.ranked
        //vars.rankLimit [rank]
        //vars.teamBalance [enabled]
        //vars.currentPlayerLimit
        //vars.maxPlayerLimit
        //vars.playerLimit [nr of players]
        //vars.bannerUrl [url]
        //vars.crossHair [enabled]
        //vars.thirdPersonVehicleCameras [enabled]
        //vars.profanityFilter [enabled]
        //vars.textChatModerationMode [moderation mode]
        //vars.textChatSpamTriggerCount [count]
        //vars.textChatSpamDetectionTime [time]
        //vars.textChatSpamCoolDownTime [time]
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    } else {
        return FrostbiteCommandHandler::parse(request, packet, lastSentPacket);
    }
}
