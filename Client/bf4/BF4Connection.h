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
    void responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet);
    void responsePlayerDisconnectEvent(const FrostbiteRconPacket &packet);
    void responsePlayerJoinEvent(const FrostbiteRconPacket &packet);
    void responsePlayerLeaveEvent(const FrostbiteRconPacket &packet);
    void responsePlayerSpawnEvent(const FrostbiteRconPacket &packet);
    void responsePlayerKillEvent(const FrostbiteRconPacket &packet);
    void responsePlayerChatEvent(const FrostbiteRconPacket &packet);
    void responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet);
    void responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet);
    void responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet);
    void responseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet);
    void responseServerLevelLoadedEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet);

    // Commands
    void responseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseServerInfoCommand(const FrostbiteRconPacket &packet);
    void responseLogoutCommand(const FrostbiteRconPacket &packet);
    void responseQuitCommand(const FrostbiteRconPacket &packet);
    void responseVersionCommand(const FrostbiteRconPacket &packet);
    void responseCurrentLevelCommand(const FrostbiteRconPacket &packet);
    void responseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void responseAdminHelpCommand(const FrostbiteRconPacket &packet);
    void responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void responseAdminSayCommand(const FrostbiteRconPacket &packet);
    void responseAdminShutDownCommand(const FrostbiteRconPacket &packet);
    void responseAdminYellCommand(const FrostbiteRconPacket &packet);
    void responseBanListAddCommand(const FrostbiteRconPacket &packet);
    void responseBanListClearCommand(const FrostbiteRconPacket &packet);
    void responseBanListListCommand(const FrostbiteRconPacket &packet);
    void responseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void responseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void responseFairFightActivateCommand(const FrostbiteRconPacket &packet);
    void responseFairFightDeactivateCommand(const FrostbiteRconPacket &packet);
    void responseFairFightIsActiveCommand(const FrostbiteRconPacket &packet);
    void responseMapListAddCommand(const FrostbiteRconPacket &packet);
    void responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet);
    void responseMapListClearCommand(const FrostbiteRconPacket &packet);
    void responseMapListEndRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet);
    void responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet);
    void responseMapListListCommand(const FrostbiteRconPacket &packet);
    void responseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void responseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet);
    void responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet);
    void responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet);
    void responsePlayerPingCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet);
    void responseSpectatorListAddCommand(const FrostbiteRconPacket &packet);
    void responseSpectatorListClearCommand(const FrostbiteRconPacket &packet);
    void responseSpectatorListListCommand(const FrostbiteRconPacket &packet);
    void responseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseSpectatorListSaveCommand(const FrostbiteRconPacket &packet);
    void responseSquadLeaderCommand(const FrostbiteRconPacket &packet);
    void responseSquadListActiveCommand(const FrostbiteRconPacket &packet);
    void responseSquadListPlayersCommand(const FrostbiteRconPacket &packet);
    void responseSquadPrivateCommand(const FrostbiteRconPacket &packet);
    void responseVars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVars3pCamCommand(const FrostbiteRconPacket &packet);
    void responseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet);
    void responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet);
    void responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet);
    void responseVarsCommanderCommand(const FrostbiteRconPacket &packet);
    void responseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet);
    void responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet);
    void responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void responseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet);
    void responseVarsHudCommand(const FrostbiteRconPacket &packet);
    void responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet);
    void responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void responseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void responseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVarsMpExperienceCommand(const FrostbiteRconPacket &packet);
    void responseVarsNameTagCommand(const FrostbiteRconPacket &packet);
    void responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet);
    void responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet);
    void responseVarsPresetCommand(const FrostbiteRconPacket &packet);
    void responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerMessageCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerTypeCommand(const FrostbiteRconPacket &packet);
    void responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeam1FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeam2FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeam3FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeam4FactionOverrideCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void responseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet);
    void responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet);
    void responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet);
    void responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet);

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
    void onCurrentLevelCommand();
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void onAdminEventsEnabledCommand();
    void onAdminHelpCommand();
    void onAdminKickPlayerCommand();
    void onAdminKillPlayerCommand();
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void onAdminMovePlayerCommand();
    void onAdminPasswordCommand();
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
    void onMapListAvailableMapsCommand();
    void onMapListClearCommand();
    void onMapListEndRoundCommand();
    void onMapListGetMapIndicesCommand();
    void onMapListGetRoundsCommand();
    void onMapListListCommand(const MapList &mapList);
    void onMapListLoadCommand();
    void onMapListRemoveCommand();
    void onMapListRestartRoundCommand();
    void onMapListRunNextRoundCommand();
    void onMapListSaveCommand();
    void onMapListSetNextMapIndexCommand();
    void onPlayerIdleDurationCommand();
    void onPlayerIsAliveCommand();
    void onPlayerPingCommand();
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
