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

#ifndef BF4CONNECTION_H
#define BF4CONNECTION_H

#include <QCryptographicHash>

#include "FrostbiteConnection.h"

#include "BF4ServerInfo.h"
#include "PlayerInfo.h"
#include "BanListEntry.h"
#include "MapListEntry.h"

typedef QList<BanListEntry> BanList;
typedef QList<MapListEntry> MapList;

class BF4Connection : public FrostbiteConnection
{
    Q_OBJECT

public:
    explicit BF4Connection(QObject *parent = 0);
    ~BF4Connection();

    /* Send */

    // Misc
    void sendLoginPlainTextCommand(const QString &password);
    void sendLoginHashedCommand(const QByteArray &salt = 0, const QString &password = 0);
    void sendServerInfoCommand();
    void sendLogoutCommand();
    void sendQuitCommand();
    void sendVersionCommand();
    void sendCurrentLevelCommand();
    void sendListPlayersCommand(const PlayerSubset &playerSubset);

    // Admin
    void sendAdminEventsEnabledCommand(const bool &enabled);
    void sendAdminHelpCommand();
    void sendAdminKickPlayerCommand(const QString &player, const QString &reason);
    void sendAdminKillPlayerCommand(const QString &player);
    void sendAdminListPlayersCommand(const PlayerSubset &playerSubset);
    void sendAdminMovePlayerCommand(const QString &player, const int &teamId, const int &squadId, const bool &forceKill);
    void sendAdminPasswordCommand();
    void sendAdminPasswordCommand(const QString &password);
    void sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset);
    void sendAdminShutdownCommand();
    void sendAdminShutdownCommand(const bool &graceful);
    void sendAdminShutdownCommand(const bool &graceful, const int &seconds);
    void sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset);
    void sendAdminYellCommand(const QString &message, const int &duration, const PlayerSubset &playerSubset);

    // Banning
    void sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason);
    void sendBanListAddCommand(const QString &idType, const QString &id, const int &timeout, const bool &useRounds, const QString &reason);
    void sendBanListClearCommand();
    void sendBanListListCommand(const int &index = 0);
    void sendBanListLoadCommand();
    void sendBanListRemoveCommand(const QString &idType, const QString &id);
    void sendBanListSaveCommand();

    // FairFight
    void sendFairFightActivateCommand();
    void sendFairFightDeactivateCommand();
    void sendFairFightIsActiveCommand();

    // Maplist
    void sendMapListAdd(const QString &level, const QString &gameMode, const int &rounds, const int &offSet = 0);
    void sendMapListAvailableMaps(const QString &filter);
    void sendMapListClear();
    void sendMapListEndRound(const int &teamId);
    void sendMapListGetMapIndices();
    void sendMapListGetRounds();
    void sendMapListList(const int &index = 0);
    void sendMapListLoad();
    void sendMapListRemove(const int &index);
    void sendMapListRestartRound();
    void sendMapListRunNextRound();
    void sendMapListSave();
    void sendMapListSetNextMapIndex(const int &index);

    // Player
    void sendPlayerIdleDuration(const QString &player);
    void sendPlayerIsAlive(const QString &player);
    void sendPlayerPing(const QString &player);

    // PunkBuster
    void sendPunkBusterActivate();
    void sendPunkBusterIsActive();
    void sendPunkBusterPbSvCommand(const QString &command);

    // Reserved Slots
    void sendReservedSlotsListAdd(const QString &player);
    void sendReservedSlotsListAggressiveJoin();
    void sendReservedSlotsListAggressiveJoin(const bool &isEnabled);
    void sendReservedSlotsListClear();
    void sendReservedSlotsListList();
    void sendReservedSlotsListLoad();
    void sendReservedSlotsListRemove(const QString &player);
    void sendReservedSlotsListSave();

    // Spectator list
    void sendSpectatorListAdd(const QString &player);
    void sendSpectatorListClear();
    void sendSpectatorListList(const int &index = 0);
    void sendSpectatorListRemove(const QString &player);
    void sendSpectatorListSave();

    // Squad
    void sendSquadLeader(const int &teamId, const int &squadId, const QString &player);
    void sendSquadListActive(const int &teamId);
    void sendSquadListPlayers(const int &teamId, const int &squadId);
    void sendSquadPrivate(const int &teamId, const int &squadId, const bool &isPrivate);

    // Variables
    void sendVars3dSpotting();
    void sendVars3dSpotting(const bool &enabled);
    void sendVars3pCam();
    void sendVars3pCam(const bool &enabled);
    void sendVarsAlwaysAllowSpectators();
    void sendVarsAlwaysAllowSpectators(const bool &enabled);
    void sendVarsAutoBalance();
    void sendVarsAutoBalance(const bool &enabled);
    void sendVarsBulletDamage(const int &damage = -1);
    void sendVarsCommander();
    void sendVarsCommander(const bool &enabled);
    void sendVarsForceReloadWholeMags();
    void sendVarsForceReloadWholeMags(const bool &enabled);
    void sendVarsFriendlyFire();
    void sendVarsFriendlyFire(const bool &enabled);
    void sendVarsGameModeCounter(const int &scale = -1);
    void sendVarsGamePassword(const QString &password = 0);
    void sendVarsHitIndicatorsEnabled();
    void sendVarsHitIndicatorsEnabled(const bool &enabled);
    void sendVarsHud();
    void sendVarsHud(const bool &enabled);
    void sendVarsIdleBanRounds(const int &rounds = -1);
    void sendVarsIdleTimeout(const int &seconds = -1);
    void sendVarsKillCam();
    void sendVarsKillCam(const bool &enabled);
    void sendVarsMaxPlayers(const int &players = -1);
    void sendVarsMaxSpectators(const int &spectators = -1);
    void sendVarsMiniMap();
    void sendVarsMiniMap(const bool &enabled);
    void sendVarsMiniMapSpotting();
    void sendVarsMiniMapSpotting(const bool &enabled);
    void sendVarsMpExperience(const QString &experience = 0);
    void sendVarsNameTag();
    void sendVarsNameTag(const bool &enabled);
    void sendVarsOnlySquadLeaderSpawn();
    void sendVarsOnlySquadLeaderSpawn(const bool &enabled);
    void sendVarsPlayerRespawnTime(const int &respawnTime = -1);
    void sendVarsPreset(const QString &serverPreset = 0, const bool &lockPresetSetting = 0);
    void sendVarsRegenerateHealth();
    void sendVarsRegenerateHealth(const bool &enabled);
    void sendVarsRoundLockdownCountdown(const int &seconds = -1);
    void sendVarsRoundRestartPlayerCount(const int &players = -1);
    void sendVarsRoundStartPlayerCount(const int &players = -1);
    void sendVarsRoundTimeLimit(const int &percent = -1);
    void sendVarsRoundWarmupTimeout(const int &timeout = -1);
    void sendVarsServerDescription(const QString &description = 0);
    void sendVarsServerMessage(const QString &message = 0);
    void sendVarsServerName(const QString &name = 0);
    void sendVarsServerType(const QString &type = 0);
    void sendVarsSoldierHealth(const int &percent = -1);
    void sendVarsTeamFactionOverride(const int &teamId = -1, const int &factionId = -1);
    void sendVarsTeamKillCountForKick(const int &count = -1);
    void sendVarsTeamKillKickForBan(const int &count = -1);
    void sendVarsTeamKillValueDecreasePerSecond(const int &count = -1);
    void sendVarsTeamKillValueForKick(const int &count = -1);
    void sendVarsTeamKillValueIncrease(const int &count = -1);
    void sendVarsTicketBleedRate(const int &percent = -1);
    void sendVarsUnlockMode(const QString &type = 0);
    void sendVarsVehicleSpawnAllowed();
    void sendVarsVehicleSpawnAllowed(const bool &enabled);
    void sendVarsVehicleSpawnDelay(const int &percent = -1);

private:
    void parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse */

    // Events
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet);
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet);
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet);
    void parsePlayerLeaveEvent(const FrostbiteRconPacket &packet);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet);
    void parsePlayerChatEvent(const FrostbiteRconPacket &packet);
    void parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet);
    void parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet);
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet);
    void parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet);
    void parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet);

    // Commands
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet);
    void parseLogoutCommand(const FrostbiteRconPacket &packet);
    void parseQuitCommand(const FrostbiteRconPacket &packet);
    void parseVersionCommand(const FrostbiteRconPacket &packet);
    void parseCurrentLevelCommand(const FrostbiteRconPacket &packet);
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void parseAdminHelpCommand(const FrostbiteRconPacket &packet);
    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void parseAdminSayCommand(const FrostbiteRconPacket &packet);
    void parseAdminShutDownCommand(const FrostbiteRconPacket &packet);
    void parseAdminYellCommand(const FrostbiteRconPacket &packet);
    void parseBanListAddCommand(const FrostbiteRconPacket &packet);
    void parseBanListClearCommand(const FrostbiteRconPacket &packet);
    void parseBanListListCommand(const FrostbiteRconPacket &packet);
    void parseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void parseFairFightActivateCommand(const FrostbiteRconPacket &packet);
    void parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet);
    void parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet);
    void parseMapListAddCommand(const FrostbiteRconPacket &packet);
    void parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet);
    void parseMapListClearCommand(const FrostbiteRconPacket &packet);
    void parseMapListEndRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet);
    void parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet);
    void parseMapListListCommand(const FrostbiteRconPacket &packet);
    void parseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet);
    void parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet);
    void parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet);
    void parsePlayerPingCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet);
    void parseSpectatorListAddCommand(const FrostbiteRconPacket &packet);
    void parseSpectatorListClearCommand(const FrostbiteRconPacket &packet);
    void parseSpectatorListListCommand(const FrostbiteRconPacket &packet);
    void parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet);
    void parseSquadLeaderCommand(const FrostbiteRconPacket &packet);
    void parseSquadListActiveCommand(const FrostbiteRconPacket &packet);
    void parseSquadListPlayersCommand(const FrostbiteRconPacket &packet);
    void parseSquadPrivateCommand(const FrostbiteRconPacket &packet);
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVars3pCamCommand(const FrostbiteRconPacket &packet);
    void parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet);
    void parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet);
    void parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet);
    void parseVarsCommanderCommand(const FrostbiteRconPacket &packet);
    void parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet);
    void parseVarsHudCommand(const FrostbiteRconPacket &packet);
    void parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet);
    void parseVarsNameTagCommand(const FrostbiteRconPacket &packet);
    void parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet);
    void parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet);
    void parseVarsPresetCommand(const FrostbiteRconPacket &packet);
    void parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerMessageCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerTypeCommand(const FrostbiteRconPacket &packet);
    void parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeam1FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeam2FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeam3FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeam4FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet);
    void parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet);
    void parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet);
    void parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet);

    QList<PlayerInfo> getPlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    PlayerSubset getPlayerSubset(const QString &playerSubsetString);

signals:
    // Events
    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerDisconnectEvent();
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, const int &teamId);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChangeEvent(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChangeEvent(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onServerMaxPlayerCountChangeEvent();
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, const int &roundsPlayed, const int &roundsTotal);
    void onServerRoundOverEvent(const int &winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    // Commands
    void onLoginPlainTextCommand();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(const bool &auth);
    void onServerInfoCommand(const ServerInfo &serverInfo);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, const int &build);
    void onCurrentLevelCommand(const QString &level);
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void onAdminEventsEnabledCommand();
    void onAdminHelpCommand(const QStringList &commandList);
    void onAdminKickPlayerCommand();
    void onAdminKillPlayerCommand();
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void onAdminMovePlayerCommand();
    void onAdminPasswordCommand(const QString &password);
    void onAdminSayCommand();
    void onAdminShutDownCommand();
    void onAdminYellCommand();
    void onBanListAddCommand();
    void onBanListClearCommand();
    void onBanListListCommand(const BanList &banList);
    void onBanListLoadCommand();
    void onBanListRemoveCommand();
    void onBanListSaveCommand();
    void onFairFightActivateCommand();
    void onFairFightDeactivateCommand();
    void onFairFightIsActiveCommand(const bool &isActive);
    void onMapListAddCommand();
    void onMapListAvailableMapsCommand(const QString &value, const QStringList &list);
    void onMapListClearCommand();
    void onMapListEndRoundCommand();
    void onMapListGetMapIndicesCommand(int &currentMapIndex, int &nextMapIndex);
    void onMapListGetRoundsCommand(int &currentRound, int &totalRounds);
    void onMapListListCommand(const MapList &mapList);
    void onMapListLoadCommand();
    void onMapListRemoveCommand();
    void onMapListRestartRoundCommand();
    void onMapListRunNextRoundCommand();
    void onMapListSaveCommand();
    void onMapListSetNextMapIndexCommand();
    void onPlayerIdleDurationCommand(float &idleDuration);
    void onPlayerIsAliveCommand(bool &alive);
    void onPlayerPingCommand(const QString &player, int &ping);
    void onPunkBusterActivateCommand();
    void onPunkBusterIsActiveCommand(const bool &isActive);
    void onPunkBusterPbSvCommand();
    void onReservedSlotsListAddCommand();
    void onReservedSlotsListAggressiveJoinCommand(const bool &enabled);
    void onReservedSlotsListClearCommand();
    void onReservedSlotsListListCommand(const QStringList &reservedSlotList);
    void onReservedSlotsListLoadCommand();
    void onReservedSlotsListRemoveCommand();
    void onReservedSlotsListSaveCommand();
    void onSpectatorListAddCommand();
    void onSpectatorListClearCommand();
    void onSpectatorListListCommand(const QStringList &spectatorList);
    void onSpectatorListRemoveCommand();
    void onSpectatorListSaveCommand();
    void onSquadLeaderCommand();
    void onSquadListActiveCommand();
    void onSquadListPlayersCommand();
    void onSquadPrivateCommand();
    void onVars3dSpottingCommand();
    void onVars3pCamCommand();
    void onVarsAlwaysAllowSpectatorsCommand(const bool &enabled);
    void onVarsAutoBalanceCommand();
    void onVarsBulletDamageCommand();
    void onVarsCommanderCommand(const bool &enabled);
    void onVarsForceReloadWholeMagsCommand();
    void onVarsFriendlyFireCommand(const bool &enabled);
    void onVarsGameModeCounterCommand();
    void onVarsGamePasswordCommand();
    void onVarsHitIndicatorsEnabledCommand();
    void onVarsHudCommand();
    void onVarsIdleBanRoundsCommand();
    void onVarsIdleTimeoutCommand(const int &seconds);
    void onVarsKillCamCommand(const bool &enabled);
    void onVarsMaxPlayersCommand(const int &playerCount);
    void onVarsMaxSpectatorsCommand(const int &spectatorCount);
    void onVarsMiniMapCommand();
    void onVarsMiniMapSpottingCommand();
    void onVarsMpExperienceCommand();
    void onVarsNameTagCommand();
    void onVarsOnlySquadLeaderSpawnCommand();
    void onVarsPlayerRespawnTimeCommand();
    void onVarsPresetCommand();
    void onVarsRegenerateHealthCommand();
    void onVarsRoundLockdownCountdownCommand();
    void onVarsRoundRestartPlayerCountCommand();
    void onVarsRoundStartPlayerCountCommand();
    void onVarsRoundTimeLimitCommand();
    void onVarsRoundWarmupTimeoutCommand();
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerTypeCommand(const QString &serverType);
    void onVarsSoldierHealthCommand();
    void onVarsTeam1FactionOverrideCommand();
    void onVarsTeam2FactionOverrideCommand();
    void onVarsTeam3FactionOverrideCommand();
    void onVarsTeam4FactionOverrideCommand();
    void onVarsTeamKillCountForKickCommand();
    void onVarsTeamKillKickForBanCommand();
    void onVarsTeamKillValueDecreasePerSecondCommand();
    void onVarsTeamKillValueForKickCommand();
    void onVarsTeamKillValueIncreaseCommand();
    void onVarsTicketBleedRateCommand();
    void onVarsUnlockModeCommand();
    void onVarsVehicleSpawnAllowedCommand();
    void onVarsVehicleSpawnDelayCommand();

};

#endif // BF4CONNECTION_H
