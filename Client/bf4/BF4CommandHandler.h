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

#ifndef BF4COMMANDHANDLER_H
#define BF4COMMANDHANDLER_H

#include "BFBaseCommandHandler.h"

#include "ServerInfo.h"
#include "PlayerInfo.h"
#include "MapListEntry.h"

typedef QList<MapListEntry> MapList;

class BF4CommandHandler : public BFBaseCommandHandler
{
    Q_OBJECT

public:
    explicit BF4CommandHandler(QObject *parent = 0);
    ~BF4CommandHandler();

    void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

private:
    // Call events.
    void eventOnPlayerAuthenticated(const FrostbiteRconPacket &packet);
    void eventOnPlayerDisconnect(const FrostbiteRconPacket &packet);
    void eventOnPlayerJoin(const FrostbiteRconPacket &packet);
    void eventOnPlayerLeave(const FrostbiteRconPacket &packet);
    void eventOnPlayerSpawn(const FrostbiteRconPacket &packet);
    void eventOnPlayerKill(const FrostbiteRconPacket &packet);
    void eventOnPlayerChat(const FrostbiteRconPacket &packet);
    void eventOnPlayerSquadChange(const FrostbiteRconPacket &packet);
    void eventOnPlayerTeamChange(const FrostbiteRconPacket &packet);
    void eventOnPunkBusterMessage(const FrostbiteRconPacket &packet);
    void eventOnServerMaxPlayerCountChange(const FrostbiteRconPacket &packet);
    void eventOnServerLevelLoaded(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOver(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOverPlayers(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOverTeamScores(const FrostbiteRconPacket &packet);

    // Call commands.
    void commandLoginPlainText(const FrostbiteRconPacket &packet);
    void commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSendPacket);
    void commandServerInfo(const FrostbiteRconPacket &packet);
    void commandLogout(const FrostbiteRconPacket &packet);
    void commandQuit(const FrostbiteRconPacket &packet);
    void commandVersion(const FrostbiteRconPacket &packet);
    void commandCurrentLevel(const FrostbiteRconPacket &packet);
    void commandListPlayers(const FrostbiteRconPacket &packet);
    void commandAdminEventsEnabled(const FrostbiteRconPacket &packet);
    void commandAdminHelp(const FrostbiteRconPacket &packet);
    void commandAdminKickPlayer(const FrostbiteRconPacket &packet);
    void commandAdminKillPlayer(const FrostbiteRconPacket &packet);
    void commandAdminListPlayers(const FrostbiteRconPacket &packet);
    void commandAdminMovePlayer(const FrostbiteRconPacket &packet);
    void commandAdminPassword(const FrostbiteRconPacket &packet);
    void commandAdminSay(const FrostbiteRconPacket &packet);
    void commandAdminShutDown(const FrostbiteRconPacket &packet);
    void commandAdminYell(const FrostbiteRconPacket &packet);
    void commandBanListAdd(const FrostbiteRconPacket &packet);
    void commandBanListClear(const FrostbiteRconPacket &packet);
    void commandBanListList(const FrostbiteRconPacket &packet);
    void commandBanListLoad(const FrostbiteRconPacket &packet);
    void commandBanListRemove(const FrostbiteRconPacket &packet);
    void commandBanListSave(const FrostbiteRconPacket &packet);
    void commandFairFightActivate(const FrostbiteRconPacket &packet);
    void commandFairFightDeactivate(const FrostbiteRconPacket &packet);
    void commandFairFightIsActive(const FrostbiteRconPacket &packet);
    void commandMapListAdd(const FrostbiteRconPacket &packet);
    void commandMapListAvailableMaps(const FrostbiteRconPacket &packet);
    void commandMapListClear(const FrostbiteRconPacket &packet);
    void commandMapListEndRound(const FrostbiteRconPacket &packet);
    void commandMapListGetMapIndices(const FrostbiteRconPacket &packet);
    void commandMapListGetRounds(const FrostbiteRconPacket &packet);
    void commandMapListList(const FrostbiteRconPacket &packet);
    void commandMapListLoad(const FrostbiteRconPacket &packet);
    void commandMapListRemove(const FrostbiteRconPacket &packet);
    void commandMapListRestartRound(const FrostbiteRconPacket &packet);
    void commandMapListRunNextRound(const FrostbiteRconPacket &packet);
    void commandMapListSave(const FrostbiteRconPacket &packet);
    void commandMapListSetNextMapIndex(const FrostbiteRconPacket &packet);
    void commandPlayerIdleDuration(const FrostbiteRconPacket &packet);
    void commandPlayerIsAlive(const FrostbiteRconPacket &packet);
    void commandPlayerPing(const FrostbiteRconPacket &packet);
    void commandPunkBusterActivate(const FrostbiteRconPacket &packet);
    void commandPunkBusterIsActive(const FrostbiteRconPacket &packet);
    void commandPunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListAdd(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListAggressiveJoin(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListClear(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListList(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListLoad(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListRemove(const FrostbiteRconPacket &packet);
    void commandReservedSlotsListSave(const FrostbiteRconPacket &packet);
    void commandSpectatorListAdd(const FrostbiteRconPacket &packet);
    void commandSpectatorListClear(const FrostbiteRconPacket &packet);
    void commandSpectatorListList(const FrostbiteRconPacket &packet);
    void commandSpectatorListRemove(const FrostbiteRconPacket &packet);
    void commandSpectatorListSave(const FrostbiteRconPacket &packet);
    void commandSquadLeader(const FrostbiteRconPacket &packet);
    void commandSquadListActive(const FrostbiteRconPacket &packet);
    void commandSquadListPlayers(const FrostbiteRconPacket &packet);
    void commandSquadPrivate(const FrostbiteRconPacket &packet);
    void commandVars3dSpotting(const FrostbiteRconPacket &packet);
    void commandVars3pCam(const FrostbiteRconPacket &packet);
    void commandVarsAlwaysAllowSpectators(const FrostbiteRconPacket &packet);
    void commandVarsAutoBalance(const FrostbiteRconPacket &packet);
    void commandVarsBulletDamage(const FrostbiteRconPacket &packet);
    void commandVarsCommander(const FrostbiteRconPacket &packet);
    void commandVarsCrossHair(const FrostbiteRconPacket &packet);
    void commandVarsForceReloadWholeMags(const FrostbiteRconPacket &packet);
    void commandVarsFriendlyFire(const FrostbiteRconPacket &packet);
    void commandVarsGameModeCounter(const FrostbiteRconPacket &packet);
    void commandVarsGamePassword(const FrostbiteRconPacket &packet);
    void commandVarsHitIndicatorsEnabled(const FrostbiteRconPacket &packet);
    void commandVarsHud(const FrostbiteRconPacket &packet);
    void commandVarsIdleBanRounds(const FrostbiteRconPacket &packet);
    void commandVarsIdleTimeout(const FrostbiteRconPacket &packet);
    void commandVarsKillCam(const FrostbiteRconPacket &packet);
    void commandVarsMaxPlayers(const FrostbiteRconPacket &packet);
    void commandVarsMaxSpectators(const FrostbiteRconPacket &packet);
    void commandVarsMiniMap(const FrostbiteRconPacket &packet);
    void commandVarsMiniMapSpotting(const FrostbiteRconPacket &packet);
    void commandVarsMpExperience(const FrostbiteRconPacket &packet);
    void commandVarsNameTag(const FrostbiteRconPacket &packet);
    void commandVarsOnlySquadLeaderSpawn(const FrostbiteRconPacket &packet);
    void commandVarsPlayerRespawnTime(const FrostbiteRconPacket &packet);
    void commandVarsPreset(const FrostbiteRconPacket &packet);
    void commandVarsRegenerateHealth(const FrostbiteRconPacket &packet);
    void commandVarsRoundLockdownCountdown(const FrostbiteRconPacket &packet);
    void commandVarsRoundRestartPlayerCount(const FrostbiteRconPacket &packet);
    void commandVarsRoundStartPlayerCount(const FrostbiteRconPacket &packet);
    void commandVarsRoundTimeLimit(const FrostbiteRconPacket &packet);
    void commandVarsRoundWarmupTimeout(const FrostbiteRconPacket &packet);
    void commandVarsServerDescription(const FrostbiteRconPacket &packet);
    void commandVarsServerMessage(const FrostbiteRconPacket &packet);
    void commandVarsServerName(const FrostbiteRconPacket &packet);
    void commandVarsServerType(const FrostbiteRconPacket &packet);
    void commandVarsSoldierHealth(const FrostbiteRconPacket &packet);
    void commandVarsTeam1FactionOverride(const FrostbiteRconPacket &packet);
    void commandVarsTeam2FactionOverride(const FrostbiteRconPacket &packet);
    void commandVarsTeam3FactionOverride(const FrostbiteRconPacket &packet);
    void commandVarsTeam4FactionOverride(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillCountForKick(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillKickForBan(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueDecreasePerSecond(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueForKick(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueIncrease(const FrostbiteRconPacket &packet);
    void commandVarsTicketBleedRate(const FrostbiteRconPacket &packet);
    void commandVarsUnlockMode(const FrostbiteRconPacket &packet);
    void commandVarsVehicleSpawnAllowed(const FrostbiteRconPacket &packet);
    void commandVarsVehicleSpawnDelay(const FrostbiteRconPacket &packet);

signals:
    /* Event signals */
    void onPlayerAuthenticated(const QString &player, const QString &guid);
    void onPlayerDisconnect();
    void onPlayerJoin(const QString &player);
    void onPlayerLeave(const QString &player, const QString &info);
    void onPlayerSpawn(const QString &player, const int &teamId);
    void onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChat(const QString &player, const QString &message, const QString &target);
    void onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessage(const QString &message);
    void onServerMaxPlayerCountChange();
    void onServerLevelLoaded(const QString &levelName, const QString &gameModeName, const int &roundsPlayed, const int &roundsTotal);
    void onServerRoundOver(const int &winningTeamId);
    void onServerRoundOverPlayers(const QString &playerInfo);
    void onServerRoundOverTeamScores(const QString &teamScores);

    // Command signals.
    void onLoginPlainTextCommand();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand();
    void onServerInfoCommand(const ServerInfo &serverInfo);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, const int &buildId, const QString &version);
    void onCurrentLevelCommand();
    void onListPlayersCommand();
    void onAdminEventsEnabledCommand();
    void onAdminHelpCommand();
    void onAdminKickPlayerCommand();
    void onAdminKillPlayerCommand();
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList);
    void onAdminMovePlayerCommand();
    void onAdminPasswordCommand();
    void onAdminSayCommand();
    void onAdminShutDownCommand();
    void onAdminYellCommand();
    void onBanListAddCommand();
    void onBanListClearCommand();
    void onBanListListCommand(const QStringList &banList);
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
    void onReservedSlotsListAggressiveJoinCommand();
    void onReservedSlotsListClearCommand();
    void onReservedSlotsListListCommand(const QStringList &reservedSlotList);
    void onReservedSlotsListLoadCommand();
    void onReservedSlotsListRemoveCommand();
    void onReservedSlotsListSaveCommand();
    void onSpectatorListAddCommand();
    void onSpectatorListClearCommand();
    void onSpectatorListListCommand();
    void onSpectatorListRemoveCommand();
    void onSpectatorListSaveCommand();
    void onSquadLeaderCommand();
    void onSquadListActiveCommand();
    void onSquadListPlayersCommand();
    void onSquadPrivateCommand();
    void onVars3dSpottingCommand();
    void onVars3pCamCommand();
    void onVarsAlwaysAllowSpectatorsCommand();
    void onVarsAutoBalanceCommand();
    void onVarsBulletDamageCommand();
    void onVarsCommanderCommand();
    void onVarsCrossHairCommand();
    void onVarsForceReloadWholeMagsCommand();
    void onVarsFriendlyFireCommand();
    void onVarsGameModeCounterCommand();
    void onVarsGamePasswordCommand();
    void onVarsHitIndicatorsEnabledCommand();
    void onVarsHudCommand();
    void onVarsIdleBanRoundsCommand();
    void onVarsIdleTimeoutCommand(const int &seconds);
    void onVarsKillCamCommand();
    void onVarsMaxPlayersCommand();
    void onVarsMaxSpectatorsCommand();
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

#endif // BF4COMMANDHANDLER_H
