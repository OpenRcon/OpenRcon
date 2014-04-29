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

#ifndef BF4_H
#define BF4_H

#include <QCryptographicHash>

#include "FrostbiteGame.h"
#include "BF4Connection.h"
#include "BF4LevelDictionary.h"

class BF4 : public FrostbiteGame {
    Q_OBJECT

public:
    explicit BF4(const QString &host, const int &port, const QString &password);
    ~BF4();

    virtual Connection* getConnection() { return con; }

protected:
    BF4Connection *con;
    BF4LevelDictionary *levelDictionary;

    bool isAuthenticated();

    /* Commands */

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
    void sendVars3dSpotting(const bool &isEnabled = 0);
    void sendVars3pCam(const bool &isEnabled = 0);
    void sendVarsAlwaysAllowSpectators(const bool &isEnabled = 0);
    void sendVarsAutoBalance(const bool &isEnabled = 0);
    void sendVarsBulletDamage(const int &damage = 0);
    void sendVarsCommander(const bool &isEnabled = 0);
    void sendVarsForceReloadWholeMags(const bool &isEnabled = 0);
    void sendVarsFriendlyFire(const bool &isEnabled = 0);
    void sendVarsGameModeCounter(const int &scale = 0);
    void sendVarsGamePassword(const QString &password = 0);
    void sendVarsHitIndicatorsEnabled(const bool &isEnabled = 0);
    void sendVarsHud(const bool &isEnabled = 0);
    void sendVarsIdleBanRounds(const int &rounds = 0);
    void sendVarsIdleTimeout(const int &seconds = 0);
    void sendVarsKillCam(const bool &isEnabled = 0);
    void sendVarsMaxPlayers(const int &players = 0);
    void sendVarsMaxSpectators(const int &spectators = 0);
    void sendVarsMiniMap(const bool &isEnabled = 0);
    void sendVarsMiniMapSpotting(const bool &isEnabled = 0);
    void sendVarsMpExperience(const QString &experience = 0);
    void sendVarsNameTag(const bool &isEnabled = 0);
    void sendVarsOnlySquadLeaderSpawn(const bool &isEnabled = 0);
    void sendVarsPlayerRespawnTime(const int &respawnTime = 0);
    void sendVarsPreset(const QString &serverPreset = 0, const bool &lockPresetSetting = 0);
    void sendVarsRegenerateHealth(const bool &isEnabled = 0);
    void sendVarsRoundLockdownCountdown(const int &seconds = 0);
    void sendVarsRoundRestartPlayerCount(const int &players = 0);
    void sendVarsRoundStartPlayerCount(const int &players = 0);
    void sendVarsRoundTimeLimit(const int &percent = 0);
    void sendVarsRoundWarmupTimeout(const int &timeout = 0);
    void sendVarsServerDescription(const QString &description = 0);
    void sendVarsServerMessage(const QString &message = 0);
    void sendVarsServerName(const QString &name = 0);
    void sendVarsServerType(const QString &type = 0);
    void sendVarsSoldierHealth(const int &percent = 0);
    void sendVarsTeamFactionOverride(const int &teamId = 0, const int &factionId = 0);
    void sendVarsTeamKillCountForKick(const int &count = 0);
    void sendVarsTeamKillKickForBan(const int &count = 0);
    void sendVarsTeamKillValueDecreasePerSecond(const int &count = 0);
    void sendVarsTeamKillValueForKick(const int &count = 0);
    void sendVarsTeamKillValueIncrease(const int &count = 0);
    void sendVarsTicketBleedRate(const int &percent = 0);
    void sendVarsUnlockMode(const QString &type = 0);
    void sendVarsVehicleSpawnAllowed(const bool &isEnabled = 0);
    void sendVarsVehicleSpawnDelay(const int &percent = 0);

private:
    bool authenticated;

private slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(const bool &auth);
    void onVersionCommand(const QString &type, const int &build);

};

#endif // BF4_H
