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

#ifndef BF4COMMANDHANDLER_H
#define BF4COMMANDHANDLER_H

#include "Frostbite2CommandHandler.h"

class QStringList;

enum class PlayerSubsetEnum;
enum class BF4PresetEnum;
enum class BF4ServerTypeEnum;
class PlayerInfo;

class BF4CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF4CommandHandler(QObject *parent = nullptr);
    ~BF4CommandHandler() final;

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
    //admin.kickPlayer <player name> <reason>
    //admin.killplayer <player name>
    void sendAdminListPlayersCommand(const PlayerSubsetEnum &playerSubset);
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.password <password>
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    /// BF4 Only.
    void sendAdminShutdownCommand();
    void sendAdminShutdownCommand(bool graceful, int seconds = -1);

    // Banning
    //banList.add <id-type> <id, timeout> reason>
    //banList.clear
    //banList.list <startIndex>
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // FairFight
    /// BF4 Only.
    void sendFairFightActivateCommand();
    void sendFairFightDeactivateCommand();
    void sendFairFightIsActiveCommand();

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps <filter>
    //mapList.clear
    //mapList.endRound <teamId>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list <startIndex>
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    //player.idleDuration <player name>
    //player.isAlive <player name>
    //player.ping <player name>

    // Punkbuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <player name>
    //reservedSlotsList.aggressiveJoin <enabled>
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Spectator list
    /// BF4 Only.
    /// Note: The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    void sendSpectatorListAddCommand(const QString &player);
    void sendSpectatorListClearCommand();
    void sendSpectatorListListCommand(int index = -1);
    void sendSpectatorListRemoveCommand(const QString &player);
    void sendSpectatorListSaveCommand();

    // Squad
    //squad.leader <teamId> <squadId> <player name>
    //squad.listActive <teamId>
    //squad.listPlayers <teamId> <squadId>
    //squad.private <teamId> <squadId> <private>

    // Variables
    //vars.3dSpotting <enabled>
    //vars.3pCam <enabled>
    //vars.autoBalance <enabled>
    //vars.bulletDamage <modifier: percent>
    //vars.friendlyFire <enabled>
    //vars.gameModeCounter <modifier: integer>
    //vars.gamePassword <password>
    //vars.hud <enabled>
    //vars.idleBanRounds <enabled>
    //vars.idleTimeout <time>
    //vars.killCam <enabled>
    //vars.maxPlayers <numPlayers>
    //vars.miniMap <enabled>
    //vars.miniMapSpotting <enabled>
    //vars.nameTag <enabled>
    //vars.onlySquadLeaderSpawn <enabled>
    //vars.playerRespawnTime <modifier: percent>
    //vars.regenerateHealth <enabled>
    //vars.roundLockdownCountdown <time>
    //vars.roundRestartPlayerCount <numPlayers>
    //vars.roundStartPlayerCount <numPlayers>
    //vars.serverDescription <description>
    //vars.serverMessage <message>
    //vars.serverName <name>
    //vars.soldierHealth <modifier: percent>
    //vars.teamKillCountForKick <count>
    //vars.teamKillKickForBan <count>
    //vars.teamKillValueDecreasePerSecond <count>
    //vars.teamKillValueForKick <count>
    //vars.teamKillValueIncrease <count>
    //vars.unlockMode <type>
    void sendVarsVehicleSpawnAllowedCommand();
    void sendVarsVehicleSpawnAllowedCommand(bool enabled);
    //vars.vehicleSpawnDelay <modifier: percent>
    //vars.gunMasterWeaponsPreset <index>

    /// BF4 Only.
    void sendVarsAlwaysAllowSpectatorsCommand();
    void sendVarsAlwaysAllowSpectatorsCommand(bool enabled);
    //vars.skillbasedbalance <enabled
    void sendVarsCommanderCommand();
    void sendVarsCommanderCommand(bool enabled);
    void sendVarsForceReloadWholeMagsCommand();
    void sendVarsForceReloadWholeMagsCommand(bool enabled);
    void sendVarsHitIndicatorsEnabledCommand();
    void sendVarsHitIndicatorsEnabledCommand(bool enabled);
    void sendVarsMaxSpectatorsCommand(int spectators = -1);
    void sendVarsMpExperienceCommand(const QString &experience = QString());
    void sendVarsPresetCommand();
    void sendVarsPresetCommand(const BF4PresetEnum &preset, bool lockPresetSetting = false);
    void sendVarsRoundTimeLimitCommand(int percent = -1);
    void sendVarsRoundWarmupTimeoutCommand(int timeout = -1);
    void sendVarsServerTypeCommand();
    void sendVarsServerTypeCommand(const BF4ServerTypeEnum &serverType);
    void sendVarsTeamFactionOverrideCommand(int teamId = -1, int factionId = -1);
    void sendVarsTicketBleedRateCommand(int percent = -1);
    void sendVarsRoundPlayersReadyBypassTimerCommand(int time = -1);
    void sendVarsRoundPlayersReadyMinCountCommand(int count = -1);
    void sendVarsRoundPlayersReadyPercentCommand(int percent = -1);
    void sendVarsIsNoobOnlyJoinCommand();
    void sendVarsIsNoobOnlyJoinCommand(bool enabled);
    //vars.serverTickTime

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

    /// BF4 Only.
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
    //login.plainText
    //login.hashed
    //serverInfo
    //logout
    //quit
    //version
    //currentLevel
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.password <password>
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    /// BF4 Only.
    //admin.shutDown <gracefulShutdown: boolean> <timeInSeconds: integer>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    //banList.list <startIndex>
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // FairFight
    /// BF4 Only.
    //fairFight.activate
    //fairfight.deactivate
    void parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps <filter>
    //mapList.clear
    //mapList.endRound <teamId>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list <startIndex>
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    //player.idleDuration <player name>
    //player.isAlive <player name>
    //player.ping <player name>

    // PunkBuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <player name>
    //reservedSlotsList.aggressiveJoin <enabled>
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Spectator list
    /// BF4 Only.
    /// The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    //spectatorList.add <player name>
    //spectatorList.clear
    void parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //spectatorList.remove <player name>
    //spectatorList.save

    // Squad
    //squad.leader <teamId> <squadId> <player name>
    //squad.listActive <teamId>
    //squad.listPlayers <teamId> <squadId>
    //squad.private <teamId> <squadId> <private>

    // Variables
    //vars.3dSpotting <enabled>
    //vars.3pCam <enabled>
    //vars.autoBalance <enabled>
    //vars.bulletDamage <modifier: percent>
    //vars.friendlyFire <enabled>
    //vars.gameModeCounter <modifier: integer>
    //vars.gamePassword <password>
    //vars.hud <enabled>
    //vars.idleBanRounds <enabled>
    //vars.idleTimeout <time>
    //vars.killCam <enabled>
    //vars.maxPlayers <numPlayers>
    //vars.miniMap <enabled>
    //vars.miniMapSpotting <enabled>
    //vars.nameTag <enabled>
    //vars.onlySquadLeaderSpawn <enabled>
    //vars.playerRespawnTime <modifier: percent>
    //vars.regenerateHealth <enabled>
    //vars.roundLockdownCountdown <time>
    //vars.roundRestartPlayerCount <numPlayers>
    //vars.roundStartPlayerCount <numPlayers>
    //vars.serverDescription <description>
    //vars.serverMessage <message>
    //vars.serverName <name>
    //vars.soldierHealth <modifier: percent>
    //vars.teamKillCountForKick <count>
    //vars.teamKillKickForBan <count>
    //vars.teamKillValueDecreasePerSecond <count>
    //vars.teamKillValueForKick <count>
    //vars.teamKillValueIncrease <count>
    //vars.unlockMode <type>
    //vars.vehicleSpawnAllowed <enabled>
    //vars.vehicleSpawnDelay <modifier: percent>
    //vars.gunMasterWeaponsPreset <index>

    /// BF4 Only.
    void parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.skillBasedBalance <enabled>
    void parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundPlayersReadyBypassTimerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundPlayersReadyMinCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundPlayersReadyPercentCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.isNoobOnlyJoin <enabled>
    //vars.serverTickTime

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

    /// BF4 Only.
    void onPlayerDisconnectEvent(const QString &player);

    /* Command signals */
    // Misc
    //login.plainText
    //login.hashed
    //serverInfo
    //logout
    //quit
    //version
    //currentLevel
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset);

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset);
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.password <password>
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    /// BF4 Only.
    //admin.shutDown <gracefulShutdown: boolean> <timeInSeconds: integer>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    //banList.list <startIndex>
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // FairFight
    /// BF4 Only.
    //fairFight.activate
    //fairfight.deactivate
    void onFairFightIsActiveCommand(bool isActive);

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    //mapList.availableMaps <filter>
    //mapList.clear
    //mapList.endRound <teamId>
    //mapList.getMapIndices
    //mapList.getRounds
    //mapList.list <startIndex>
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    //player.idleDuration <player name>
    //player.isAlive <player name>
    //player.ping <player name>

    // PunkBuster
    //punkBuster.activate
    //punkBuster.isActive
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <player name>
    //reservedSlotsList.aggressiveJoin <enabled>
    //reservedSlotsList.clear
    //reservedSlotsList.list
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Spectator list
    //// The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    //spectatorList.add <player name>
    //spectatorList.clear
    void onSpectatorListListCommand(const QStringList &spectatorList);
    //spectatorList.remove <player name>
    //spectatorList.save

    // Squad
    //squad.leader <teamId> <squadId> <player name>
    //squad.listActive <teamId>
    //squad.listPlayers <teamId> <squadId>
    //squad.private <teamId> <squadId> <private>

    // Variables
    //vars.3dSpotting <enabled>
    //vars.3pCam <enabled>
    //vars.autoBalance <enabled>
    //vars.bulletDamage <modifier: percent>
    //vars.friendlyFire <enabled>
    //vars.gameModeCounter <modifier: integer>
    //vars.gamePassword <password>
    //vars.hud <enabled>
    //vars.idleBanRounds <enabled>
    //vars.idleTimeout <time>
    //vars.killCam <enabled>
    //vars.maxPlayers <numPlayers>
    //vars.miniMap <enabled>
    //vars.miniMapSpotting <enabled>
    //vars.nameTag <enabled>
    //vars.onlySquadLeaderSpawn <enabled>
    //vars.playerRespawnTime <modifier: percent>
    //vars.regenerateHealth <enabled>
    //vars.roundLockdownCountdown <time>
    //vars.roundRestartPlayerCount <numPlayers>
    //vars.roundStartPlayerCount <numPlayers>
    //vars.serverDescription <description>
    //vars.serverMessage <message>
    //vars.serverName <name>
    //vars.soldierHealth <modifier: percent>
    //vars.teamKillCountForKick <count>
    //vars.teamKillKickForBan <count>
    //vars.teamKillValueDecreasePerSecond <count>
    //vars.teamKillValueForKick <count>
    //vars.teamKillValueIncrease <count>
    //vars.unlockMode <type>
    //vars.vehicleSpawnAllowed <enabled>
    //vars.vehicleSpawnDelay <modifier: percent>
    //vars.gunMasterWeaponsPreset <index>

    /// BF4 Only.
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);
    //vars.skillBasedBalance <enabled>
    void onVarsCommanderCommand(bool enabled);
    void onVarsForceReloadWholeMagsCommand(bool enabled);
    void onVarsHitIndicatorsEnabledCommand(bool enabled);
    void onVarsMaxSpectatorsCommand(int spectatorCount);
    void onVarsMpExperienceCommand(const QString &experience);
    void onVarsPresetCommand(const BF4PresetEnum &preset, bool lockPresetSetting);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int timeout);
    void onVarsServerTypeCommand(const QString &type);
    void onVarsTeamFactionOverrideCommand(int team1, int team2, int team3, int team4);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsRoundPlayersReadyBypassTimerCommand(int timer);
    void onVarsRoundPlayersReadyMinCountCommand(int count);
    void onVarsRoundPlayersReadyPercentCommand(int percent);
    //vars.isNoobOnlyJoin <enabled>
    //vars.serverTickTime

};

#endif // BF4COMMANDHANDLER_H
