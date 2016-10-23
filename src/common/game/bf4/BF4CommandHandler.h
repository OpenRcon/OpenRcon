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

class QString;
class QStringList;

enum class PlayerSubsetType;
enum class BF4PresetType;
enum class BF4ServerType;
class BF4ServerInfo;
class PlayerInfo;

class BF4CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF4CommandHandler(FrostbiteConnection *parent = nullptr);
    ~BF4CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc
    //login.plainText <password>
    //login.hashed
    //login.hashed <passwordHard>
    void sendServerInfoCommand();
    //logout
    //quit
    //version
    void sendCurrentLevelCommand();
    void sendListPlayersCommand(const PlayerSubsetType &playerSubsetType);
    //vars.serverTickTime

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <player name> <reason>
    //admin.killplayer <player name>
    void sendAdminListPlayersCommand(const PlayerSubsetType &playerSubsetType);
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.password <password>
    //admin.say <message> <players>
    void sendAdminShutdownCommand();
    void sendAdminShutdownCommand(bool graceful);
    void sendAdminShutdownCommand(bool graceful, int seconds);
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout> reason>
    //banList.clear
    //banList.list <startIndex>
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // FairFight
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
    //// The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    void sendSpectatorListAddCommand(const QString &player);
    void sendSpectatorListClearCommand();
    void sendSpectatorListListCommand(int index = 0);
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
    void sendVarsAlwaysAllowSpectatorsCommand();
    void sendVarsAlwaysAllowSpectatorsCommand(bool enabled);
    //vars.autoBalance <enabled>
    //vars.skillbasedbalance <enabled>
    //vars.bulletDamage <modifier: percent>
    void sendVarsCommanderCommand();
    void sendVarsCommanderCommand(bool enabled);
    void sendVarsForceReloadWholeMagsCommand();
    void sendVarsForceReloadWholeMagsCommand(bool enabled);
    //vars.friendlyFire <enabled>
    //vars.gameModeCounter <modifier: integer>
    //vars.gamePassword <password>
    void sendVarsHitIndicatorsEnabledCommand();
    void sendVarsHitIndicatorsEnabledCommand(bool enabled);
    //vars.hud <enabled>
    //vars.idleBanRounds <enabled>
    //vars.idleTimeout <time>
    //vars.killCam <enabled>
    //vars.maxPlayers <numPlayers>
    void sendVarsMaxSpectatorsCommand(int spectators = -1);
    //vars.miniMap <enabled>
    //vars.miniMapSpotting <enabled>
    void sendVarsMpExperienceCommand(const QString &experience = QString());
    //vars.nameTag <enabled>
    //vars.onlySquadLeaderSpawn <enabled>
    //vars.playerRespawnTime <modifier: percent>
    void sendVarsPresetCommand();
    void sendVarsPresetCommand(const BF4PresetType &presetType, bool lockPresetSetting = false);
    //vars.regenerateHealth <enabled>
    //vars.roundLockdownCountdown <time>
    //vars.roundRestartPlayerCount <numPlayers>
    //vars.roundStartPlayerCount <numPlayers>
    void sendVarsRoundTimeLimitCommand(int percent = -1);
    void sendVarsRoundWarmupTimeoutCommand(int timeout = -1);
    //vars.serverDescription <description>
    //vars.serverMessage <message>
    //vars.serverName <name>
    void sendVarsServerTypeCommand();
    void sendVarsServerTypeCommand(const BF4ServerType &type);
    //vars.soldierHealth <modifier: percent>
    void sendVarsTeamFactionOverrideCommand(int teamId = -1, int factionId = -1);
    //vars.teamKillCountForKick <count>
    //vars.teamKillKickForBan <count>
    //vars.teamKillValueDecreasePerSecond <count>
    //vars.teamKillValueForKick <count>
    //vars.teamKillValueIncrease <count>
    void sendVarsTicketBleedRateCommand(int percent = -1);
    //vars.unlockMode <type>
    void sendVarsVehicleSpawnAllowedCommand();
    void sendVarsVehicleSpawnAllowedCommand(bool enabled);
    //vars.vehicleSpawnDelay <modifier: percent>
    void sendVarsRoundPlayersReadyBypassTimerCommand(int time = -1);
    void sendVarsRoundPlayersReadyMinCountCommand(int count = -1);
    void sendVarsRoundPlayersReadyPercentCommand(int percent = -1);
    void sendVarsIsNoobOnlyJoinCommand();
    void sendVarsIsNoobOnlyJoinCommand(bool enabled);
    //vars.gunMasterWeaponsPreset <index>

private:
    /* Parse events */
    //player.onAuthenticated
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
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
    //login.plainText
    //login.hashed
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //quit
    //version
    void parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.serverTickTime

    // Admin
    //admin.eventsEnabled <enabled>
    //admin.help
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.password <password>
    //admin.say <message> <players>
    void parseAdminShutDownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    //banList.list <startIndex>
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // FairFight
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
    void parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.autoBalance <enabled>
    //vars.skillBasedBalance <enabled>
    //vars.bulletDamage <modifier: percent>
    void parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.friendlyFire <enabled>
    //vars.gameModeCounter <modifier: integer>
    //vars.gamePassword <password>
    void parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.hud <enabled>
    //vars.idleBanRounds <enabled>
    //vars.idleTimeout <time>
    //vars.killCam <enabled>
    //vars.maxPlayers <numPlayers>
    void parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.miniMap <enabled>
    //vars.miniMapSpotting <enabled>
    void parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.nameTag <enabled>
    //vars.onlySquadLeaderSpawn <enabled>
    //vars.playerRespawnTime <modifier: percent>
    void parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.regenerateHealth <enabled>
    //vars.roundLockdownCountdown <time>
    //vars.roundRestartPlayerCount <numPlayers>
    //vars.roundStartPlayerCount <numPlayers>
    void parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.serverDescription <description>
    //vars.serverMessage <message>
    //vars.serverName <name>
    void parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.soldierHealth <modifier: percent>
    void parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.teamKillCountForKick <count>
    //vars.teamKillKickForBan <count>
    //vars.teamKillValueDecreasePerSecond <count>
    //vars.teamKillValueForKick <count>
    //vars.teamKillValueIncrease <count>
    void parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.unlockMode <type>
    //vars.vehicleSpawnAllowed <enabled>
    //vars.vehicleSpawnDelay <modifier: percent>
    void parseVarsRoundPlayersReadyBypassTimerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundPlayersReadyMinCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundPlayersReadyPercentCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.isNoobOnlyJoin <enabled>
    //vars.gunMasterWeaponsPreset <index>

    QList<PlayerInfo> parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    void onPlayerDisconnectEvent(const QString &player);

    /* Command signals */
    // Misc
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onCurrentLevelCommand(const QString &level);
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetType &playerSubsetType);

    // Admin
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetType &playerSubsetType);

    // FairFight
    void onFairFightIsActiveCommand(bool isActive);

    // Spectator List
    void onSpectatorListListCommand(const QStringList &spectatorList);

    // Variables
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void onVarsCommanderCommand(bool enabled);
    void onVarsForceReloadWholeMagsCommand(bool enabled);
    void onVarsHitIndicatorsEnabledCommand(bool enabled);
    void onVarsMaxSpectatorsCommand(int spectatorCount);
    void onVarsMpExperienceCommand(const QString &experience);
    void onVarsPresetCommand(const BF4PresetType &presetType, bool lockPresetSetting);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int timeout);
    void onVarsServerTypeCommand(const QString &type);
    void onVarsTeamFactionOverrideCommand(int team1, int team2, int team3, int team4);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsRoundPlayersReadyBypassTimerCommand(int timer);
    void onVarsRoundPlayersReadyMinCountCommand(int count);
    void onVarsRoundPlayersReadyPercentCommand(int percent);

};

#endif // BF4COMMANDHANDLER_H
