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

#ifndef BF3COMMANDHANDLER_H
#define BF3COMMANDHANDLER_H

#include "Frostbite2CommandHandler.h"

class QStringList;

enum class PlayerSubsetEnum;
class PlayerInfo;

class BF3CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF3CommandHandler(QObject *parent = nullptr);
    ~BF3CommandHandler() final;

    bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) final;

    /* Send commands */
    // Misc
    //login.plainText <password>
    //login.hashed
    //login.hashed <passwordHard>
    //serverInfo
    //logout
    //quit
    //version
    //currentLevel
    void sendListPlayersCommand(const PlayerSubsetEnum &playerSubset);

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <soldier name, reason>
    //admin.killPlayer <name>
    void sendAdminListPlayersCommand(const PlayerSubsetEnum &playerSubset);
    //admin.movePlayer <name, teamID, squadID, forceKill>
    //admin.password [password]
    //admin.say <message, players>
    //admin.yell <message, duration, players>

    /// BF3 Only.
    void sendAdminEffectiveMaxPlayersCommand();

    // Banning
    //banList.add <id-type, id, timeout, reason>
    //banList.clear
    //banList.list [startIndex]
    //banList.load
    //banList.remove <id-type, id>
    //banList.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps
    //mapList.clear
    //mapList.endRound <teamID>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list [startIndex]
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF4?
    //player.idleDuration
    //player.isAlive
    //player.ping

    // Punkbuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <name> Add <name>
    //reservedSlotsList.aggressiveJoin [enabled]
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <name>
    //reservedSlotsList.save

    // Squad
    //squad.leader <team id, squad id, [soldier name]>
    //squad.listActive <team id>
    //squad.listPlayers <team id, squad id>
    //squad.private <team id, squad id, [private]>

    // Variables
    //vars.3dSpotting [enabled]
    //vars.3pCam [enabled]
    //vars.autoBalance [enabled]
    //vars.bulletDamage [modifier: percent]
    //vars.friendlyFire [enabled]
    //vars.gameModeCounter [modifier: integer]
    //vars.gamePassword [password]
    //vars.hud [enabled]
    //vars.idleBanRounds [enabled]
    //vars.idleTimeout [time]
    //vars.killCam [enabled]
    //vars.maxPlayers [nr of players]
    //vars.miniMap [enabled]
    //vars.miniMapSpotting [enabled]
    //vars.nameTag [enabled]
    //vars.onlySquadLeaderSpawn [enabled]
    //vars.playerRespawnTime [modifier: percent]
    //vars.regenerateHealth [enabled]
    //vars.roundLockdownCountdown [time]
    //vars.roundRestartPlayerCount [numPlayers]
    //vars.roundStartPlayerCount [numPlayers]
    //vars.serverDescription [description]
    //vars.serverMessage [message]
    //vars.serverName [name]
    //vars.soldierHealth [modifier: percent]
    //vars.teamKillCountForKick [count]
    //vars.teamKillKickForBan [count]
    //vars.teamKillValueDecreasePerSecond [count]
    //vars.teamKillValueForKick [count]
    //vars.teamKillValueIncrease [count]
    //vars.unlockMode [mode]
    //vars.vehicleSpawnAllowed [enabled]
    //vars.vehicleSpawnDelay [modifier: percent]
    void sendVarsGunMasterWeaponsPresetCommand(int weaponPreset = -1);

    /// BF3 Only.
    void sendVarsRankedCommand();
    void sendVarsRankedCommand(bool ranked);
    void sendVarsCrossHairCommand();
    void sendVarsCrossHairCommand(bool enabled);
    void sendVarsPlayerManDownTimeCommand(int percent = -1);
    void sendVarsPremiumStatusCommand();
    void sendVarsPremiumStatusCommand(bool enabled);
    void sendVarsBannerUrlCommand(const QString &bannerUrl = QString());
    void sendVarsRoundsPerMapCommand(int rounds = -1);

private:
    /* Parse events */
    //player.onAuthenticated
    //player.onJoin
    //player.onLeave
    //player.onSpawn
    //player.onKill
    //player.onChat
    //player.onSquadChange
    //player.onTeamChange
    //punkBuster.onMessage
    //server.onMaxPlayerCountChange
    //server.onLevelLoaded
    //server.onRoundOver
    //server.onRoundOverPlayers
    //server.onRoundOverTeamScores

    /* Parse commands */
    // Misc
    //login.plainText <password>
    //login.hashed
    //login.hashed <passwordHard>
    //serverInfo
    //logout
    //quit
    //version
    //currentLevel
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <soldier name, reason>
    //admin.killPlayer <name>
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.movePlayer <name, teamID, squadID, forceKill>
    //admin.password [password]
    //admin.say <message, players>
    //admin.yell <message, duration, players>

    /// BF3 Only.
    void parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Banning
    //banList.add <id-type, id, timeout, reason>
    //banList.clear
    //banList.list [startIndex]
    //banList.load
    //banList.remove <id-type, id>
    //banList.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps
    //mapList.clear
    //mapList.endRound <teamID>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list [startIndex]
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF4?
    //player.idleDuration
    //player.isAlive
    //player.ping

    // PunkBuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <name> Add <name>
    //reservedSlotsList.aggressiveJoin [enabled]
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <name>
    //reservedSlotsList.save

    // Squad
    //squad.leader <team id, squad id, [soldier name]>
    //squad.listActive <team id>
    //squad.listPlayers <team id, squad id>
    //squad.private <team id, squad id, [private]>

    // Variables
    //vars.3dSpotting [enabled]
    //vars.3pCam [enabled]
    //vars.autoBalance [enabled]
    //vars.bulletDamage [modifier: percent]
    //vars.friendlyFire [enabled]
    //vars.gameModeCounter [modifier: integer]
    //vars.gamePassword [password]
    //vars.hud [enabled]
    //vars.idleBanRounds [enabled]
    //vars.idleTimeout [time]
    //vars.killCam [enabled]
    //vars.maxPlayers [nr of players]
    //vars.miniMap [enabled]
    //vars.miniMapSpotting [enabled]
    //vars.nameTag [enabled]
    //vars.onlySquadLeaderSpawn [enabled]
    //vars.playerRespawnTime [modifier: percent]
    //vars.regenerateHealth [enabled]
    //vars.roundLockdownCountdown [time]
    //vars.roundRestartPlayerCount [numPlayers]
    //vars.roundStartPlayerCount [numPlayers]
    //vars.serverDescription [description]
    //vars.serverMessage [message]
    //vars.serverName [name]
    //vars.soldierHealth [modifier: percent]
    //vars.teamKillCountForKick [count]
    //vars.teamKillKickForBan [count]
    //vars.teamKillValueDecreasePerSecond [count]
    //vars.teamKillValueForKick [count]
    //vars.teamKillValueIncrease [count]
    //vars.unlockMode [mode]
    //vars.vehicleSpawnAllowed [enabled]
    //vars.vehicleSpawnDelay [modifier: percent]
    void parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /// BF3 Only.
    void parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    //player.onAuthenticated
    //player.onJoin
    //player.onLeave
    //player.onSpawn
    //player.onKill
    //player.onChat
    //player.onSquadChange
    //player.onTeamChange
    //punkBuster.onMessage
    //server.onMaxPlayerCountChange
    //server.onLevelLoaded
    //server.onRoundOver
    //server.onRoundOverPlayers
    //server.onRoundOverTeamScores

    /* Command signals */
    // Misc
    //login.plainText <password>
    //login.hashed
    //login.hashed <passwordHard>
    //serverInfo
    //logout
    //quit
    //version
    //currentLevel
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset);

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <soldier name, reason>
    //admin.killPlayer <name>
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset);
    //admin.movePlayer <name, teamID, squadID, forceKill>
    //admin.password [password]
    //admin.say <message, players>
    //admin.yell <message, duration, players>

    /// BF3 Only.
    void onAdminEffectiveMaxPlayersCommand(int effectiveMaxPlayers);

    // Banning
    //banList.add <id-type, id, timeout, reason>
    //banList.clear
    //banList.list [startIndex]
    //banList.load
    //banList.remove <id-type, id>
    //banList.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps
    //mapList.clear
    //mapList.endRound <teamID>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list [startIndex]
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF4?
    //player.idleDuration
    //player.isAlive
    //player.ping

    // PunkBuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <name> Add <name>
    //reservedSlotsList.aggressiveJoin [enabled]
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <name>
    //reservedSlotsList.save

    // Squad
    //squad.leader <team id, squad id, [soldier name]>
    //squad.listActive <team id>
    //squad.listPlayers <team id, squad id>
    //squad.private <team id, squad id, [private]>

    // Variables
    //vars.3dSpotting [enabled]
    //vars.3pCam [enabled]
    //vars.autoBalance [enabled]
    //vars.bulletDamage [modifier: percent]
    //vars.friendlyFire [enabled]
    //vars.gameModeCounter [modifier: integer]
    //vars.gamePassword [password]
    //vars.hud [enabled]
    //vars.idleBanRounds [enabled]
    //vars.idleTimeout [time]
    //vars.killCam [enabled]
    //vars.maxPlayers [nr of players]
    //vars.miniMap [enabled]
    //vars.miniMapSpotting [enabled]
    //vars.nameTag [enabled]
    //vars.onlySquadLeaderSpawn [enabled]
    //vars.playerRespawnTime [modifier: percent]
    //vars.regenerateHealth [enabled]
    //vars.roundLockdownCountdown [time]
    //vars.roundRestartPlayerCount [numPlayers]
    //vars.roundStartPlayerCount [numPlayers]
    //vars.serverDescription [description]
    //vars.serverMessage [message]
    //vars.serverName [name]
    //vars.soldierHealth [modifier: percent]
    //vars.teamKillCountForKick [count]
    //vars.teamKillKickForBan [count]
    //vars.teamKillValueDecreasePerSecond [count]
    //vars.teamKillValueForKick [count]
    //vars.teamKillValueIncrease [count]
    //vars.unlockMode [mode]
    //vars.vehicleSpawnAllowed [enabled]
    //vars.vehicleSpawnDelay [modifier: percent]
    void onVarsGunMasterWeaponsPresetCommand(int weaponPreset);

    /// BF3 Only.
    void onVarsRankedCommand(bool ranked);
    void onVarsCrossHairCommand(bool enabled);
    void onVarsPlayerManDownTimeCommand(int percent);
    void onVarsPremiumStatusCommand(bool enabled);
    void onVarsBannerUrlCommand(const QString &bannerUrl);
    void onVarsRoundsPerMapCommand(int rounds);

};

#endif // BF3COMMANDHANDLER_H
