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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FROSTBITE2COMMANDHANDLER_H
#define FROSTBITE2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"
#include "PlayerSubset.h"
#include "BanListEntry.h"
#include "MapListEntry.h"

class QStringList;

enum class PlayerSubsetType;
class Frostbite2ServerInfo;
class BF3ServerInfo;
class BF4ServerInfo;
class PlayerInfo;

class Frostbite2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    Frostbite2CommandHandler(QObject *parent = nullptr);
    virtual ~Frostbite2CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc
    void sendLoginPlainTextCommand(const QString &password);
    void sendLoginHashedCommand(const QByteArray &salt = QByteArray(), const QString &password = QString());
    void sendServerInfoCommand();
    void sendLogoutCommand();
    void sendQuitCommand();
    void sendVersionCommand();
    void sendCurrentLevelCommand();
    //listPlayers <players>

    // Admin
    void sendAdminEventsEnabledCommand(bool enabled);
    void sendAdminHelpCommand();
    void sendAdminKickPlayerCommand(const QString &player, const QString &reason);
    void sendAdminKillPlayerCommand(const QString &player);
    //admin.listPlayers <players>
    void sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill);
    void sendAdminPasswordCommand(const QString &password = QString());
    void sendAdminSayCommand(const QString &message, const PlayerSubsetType &playerSubsetType, int parameter = -1);
    void sendAdminYellCommand(const QString &message, const PlayerSubsetType &playerSubsetType, int parameter = -1);
    void sendAdminYellCommand(const QString &message, int duration, const PlayerSubsetType &playerSubsetType, int parameter = -1);

    // Banning
    void sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason);
    void sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason);
    void sendBanListClearCommand();
    void sendBanListListCommand(int index = 0);
    void sendBanListLoadCommand();
    void sendBanListRemoveCommand(const QString &idType, const QString &id);
    void sendBanListSaveCommand();

    // Maplist
    void sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet = 0);
    void sendMapListAvailableMapsCommand(const QString &filter);
    void sendMapListClearCommand();
    void sendMapListEndRoundCommand(int teamId);
    void sendMapListGetMapIndicesCommand();
    void sendMapListGetRoundsCommand();
    void sendMapListListCommand(int index = 0);
    void sendMapListLoadCommand();
    void sendMapListRemoveCommand(int index);
    void sendMapListRestartRoundCommand();
    void sendMapListRunNextRoundCommand();
    void sendMapListSaveCommand();
    void sendMapListSetNextMapIndexCommand(int index);

    // Player
    /// Differ from BF3?
    void sendPlayerIdleDurationCommand(const QString &player);
    void sendPlayerIsAliveCommand(const QString &player);
    void sendPlayerPingCommand(const QString &player);

    // Punkbuster
    void sendPunkBusterActivateCommand();
    void sendPunkBusterIsActiveCommand();
    void sendPunkBusterPbSvCommand(const QString &command);

    // Reserved Slots
    void sendReservedSlotsListAddCommand(const QString &player);
    void sendReservedSlotsListAggressiveJoinCommand();
    void sendReservedSlotsListAggressiveJoinCommand(bool enabled);
    void sendReservedSlotsListClearCommand();
    void sendReservedSlotsListListCommand();
    void sendReservedSlotsListLoadCommand();
    void sendReservedSlotsListRemoveCommand(const QString &player);
    void sendReservedSlotsListSaveCommand();

    // Squad
    void sendSquadLeaderCommand(int teamId, int squadId, const QString &player);
    void sendSquadListActiveCommand(int teamId);
    void sendSquadListPlayersCommand(int teamId, int squadId);
    void sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate);

    // Variables
    void sendVars3dSpottingCommand();
    void sendVars3dSpottingCommand(bool enabled);
    void sendVars3pCamCommand();
    void sendVars3pCamCommand(bool enabled);
    void sendVarsAutoBalanceCommand();
    void sendVarsAutoBalanceCommand(bool enabled);
    void sendVarsBulletDamageCommand(int damage = -1);
    void sendVarsFriendlyFireCommand();
    void sendVarsFriendlyFireCommand(bool enabled);
    void sendVarsGameModeCounterCommand(int scale = -1);
    void sendVarsGamePasswordCommand(const QString &password = QString());
    void sendVarsHudCommand();
    void sendVarsHudCommand(bool enabled);
    void sendVarsIdleBanRoundsCommand(int rounds = -1);
    void sendVarsIdleTimeoutCommand(int seconds = -1);
    void sendVarsKillCamCommand();
    void sendVarsKillCamCommand(bool enabled);
    void sendVarsMaxPlayersCommand(int players = -1);
    void sendVarsMiniMapCommand();
    void sendVarsMiniMapCommand(bool enabled);
    void sendVarsMiniMapSpottingCommand();
    void sendVarsMiniMapSpottingCommand(bool enabled);
    void sendVarsNameTagCommand();
    void sendVarsNameTagCommand(bool enabled);
    void sendVarsOnlySquadLeaderSpawnCommand();
    void sendVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void sendVarsPlayerRespawnTimeCommand(int respawnTime = -1);
    void sendVarsRegenerateHealthCommand();
    void sendVarsRegenerateHealthCommand(bool enabled);
    void sendVarsRoundLockdownCountdownCommand(int seconds = -1);
    void sendVarsRoundRestartPlayerCountCommand(int players = -1);
    void sendVarsRoundStartPlayerCountCommand(int players = -1);
    void sendVarsServerDescriptionCommand(const QString &description = QString());
    void sendVarsServerMessageCommand(const QString &message = QString());
    void sendVarsServerNameCommand(const QString &name = QString());
    void sendVarsSoldierHealthCommand(int percent = -1);
    void sendVarsTeamKillCountForKickCommand(int count = -1);
    void sendVarsTeamKillKickForBanCommand(int count = -1);
    void sendVarsTeamKillValueDecreasePerSecondCommand(int count = -1);
    void sendVarsTeamKillValueForKickCommand(int count = -1);
    void sendVarsTeamKillValueIncreaseCommand(int count = -1);
    void sendVarsUnlockModeCommand(const QString &type = QString());
    void sendVarsVehicleSpawnAllowedCommand();
    void sendVarsVehicleSpawnAllowedCommand(bool enabled);
    void sendVarsVehicleSpawnDelayCommand(int percent = -1);
    //vars.gunMasterWeaponsPreset <index>

protected:
    QList<PlayerInfo> parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

private:
    /* Parse events */
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //listPlayers <players>

    // Admin
    void parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    //admin.listPlayers <players>
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    void parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    void parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    void parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //mapList.clear
    //mapList.endRound <teamId>
    void parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    void parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // PunkBuster
    //punkBuster.activate
    void parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <player name>
    void parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //reservedSlotsList.clear
    void parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Squad
    void parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //squad.listActive <teamId>
    void parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Variables
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.gunMasterWeaponsPreset <index>

signals:
    /* Event signals */
    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, int teamId);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onServerMaxPlayerCountChangeEvent(int count);
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    /* Command signals */
    // Misc
    void onLoginPlainTextCommand(bool auth);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);
    void onServerInfoCommand(const BF3ServerInfo &serverInfo);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, int build);
    void onCurrentLevelCommand(const QString &level);
    //listPlayers <players>

    // Admin
    void onAdminEventsEnabledCommand(bool enabled);
    void onAdminHelpCommand(const QStringList &commandList);
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    //admin.listPlayers <players>
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    void onAdminPasswordCommand(const QString &password);
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    void onBanListListCommand(const QList<BanListEntry> &banList);
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    void onMapListAvailableMapsCommand(const QString &value, const QStringList &list);
    //mapList.clear
    //mapList.endRound <teamId>
    void onMapListGetMapIndicesCommand(int currentMapIndex, int nextMapIndex);
    void onMapListGetRoundsCommand(int currentRound, int totalRounds);
    void onMapListListCommand(const MapList &mapList);
    //mapList.load
    //mapList.remove <index>
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.save
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    void onPlayerIdleDurationCommand(float idleDuration);
    void onPlayerIsAliveCommand(bool alive);
    void onPlayerPingCommand(const QString &player, int ping);

    // PunkBuster
    //punkBuster.activate
    void onPunkBusterIsActiveCommand(bool active);
    //punkBuster.pb_sv_command <command>

    // Reserved Slots
    //reservedSlotsList.add <player name>
    void onReservedSlotsListAggressiveJoinCommand(bool enabled);
    //reservedSlotsList.clear
    void onReservedSlotsListListCommand(const QStringList &reservedSlotList);
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Squad
    void onSquadLeaderCommand(const QString &player);
    //squad.listActive <teamId>
    void onSquadListPlayersCommand(const QStringList &playerList);
    void onSquadPrivateCommand(bool isPrivate);

    // Variables
    void onVars3dSpottingCommand(bool enabled);
    void onVars3pCamCommand(bool enabled);
    void onVarsAutoBalanceCommand(bool enabled);
    void onVarsBulletDamageCommand(int percent);
    void onVarsFriendlyFireCommand(bool enabled);
    void onVarsGameModeCounterCommand(int percent);
    void onVarsGamePasswordCommand(const QString &password);
    void onVarsHudCommand(bool enabled);
    void onVarsIdleBanRoundsCommand(int rounds);
    void onVarsIdleTimeoutCommand(int seconds);
    void onVarsKillCamCommand(bool enabled);
    void onVarsMaxPlayersCommand(int playerCount);
    void onVarsMiniMapCommand(bool enabled);
    void onVarsMiniMapSpottingCommand(bool enabled);
    void onVarsNameTagCommand(bool enabled);
    void onVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void onVarsPlayerRespawnTimeCommand(int respawnTime);
    void onVarsRegenerateHealthCommand(bool enabled);
    void onVarsRoundLockdownCountdownCommand(int seconds);
    void onVarsRoundRestartPlayerCountCommand(int players);
    void onVarsRoundStartPlayerCountCommand(int players);
    void onVarsServerDescriptionCommand(const QString &description);
    void onVarsServerMessageCommand(const QString &message);
    void onVarsServerNameCommand(const QString &name);
    void onVarsSoldierHealthCommand(int health);
    void onVarsTeamKillCountForKickCommand(int count);
    void onVarsTeamKillKickForBanCommand(int count);
    void onVarsTeamKillValueDecreasePerSecondCommand(int count);
    void onVarsTeamKillValueForKickCommand(int count);
    void onVarsTeamKillValueIncreaseCommand(int count);
    void onVarsUnlockModeCommand(const QString &type);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);
    //vars.gunMasterWeaponsPreset <index>

};

#endif // FROSTBITE2COMMANDHANDLER_H
