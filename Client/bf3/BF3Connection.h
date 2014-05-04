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

#ifndef BF3CONNECTION_H
#define BF3CONNECTION_H

#include <QCryptographicHash>

#include "FrostbiteConnection.h"

#include "PlayerInfo.h"

class BF3Connection : public FrostbiteConnection
{
    Q_OBJECT

public:
    explicit BF3Connection(QObject *parent = 0);
    ~BF3Connection();

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

private:
    void parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse */

    // Events

    // Commands
    void responseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseServerInfoCommand(const FrostbiteRconPacket &packet);
    void responseAdminHelpCommand(const FrostbiteRconPacket &packet);
    void responseLogoutCommand(const FrostbiteRconPacket &packet);
    void responseQuitCommand(const FrostbiteRconPacket &packet);
    void responseVersionCommand(const FrostbiteRconPacket &packet);
    void responseListPlayersCommand(const FrostbiteRconPacket &packet);
    void responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void responseAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void responseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void responseAdminSayCommand(const FrostbiteRconPacket &packet);
    void responseAdminYellCommand(const FrostbiteRconPacket &packet);
    void responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet);
    void responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet);
    void responsePlayerPingCommand(const FrostbiteRconPacket &packet);
    void responseSquadListActiveCommand(const FrostbiteRconPacket &packet);
    void responseSquadListPlayersCommand(const FrostbiteRconPacket &packet);
    void responseSquadPrivateCommand(const FrostbiteRconPacket &packet);
    void responseSquadLeaderCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet);
    void responseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void responseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void responseBanListAddCommand(const FrostbiteRconPacket &packet);
    void responseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseBanListClearCommand(const FrostbiteRconPacket &packet);
    void responseBanListListCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet);
    void responseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void responseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void responseMapListAddCommand(const FrostbiteRconPacket &packet);
    void responseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseMapListClearCommand(const FrostbiteRconPacket &packet);
    void responseMapListListCommand(const FrostbiteRconPacket &packet);
    void responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet);
    void responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet);
    void responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet);
    void responseMapListEndRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet);
    void responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet);
    void responseVarsRankedCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerMessageCommand(const FrostbiteRconPacket &packet);
    void responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void responseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void responseVarsHudCommand(const FrostbiteRconPacket &packet);
    void responseVarsCrossHairCommand(const FrostbiteRconPacket &packet);
    void responsevars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVarsNameTagCommand(const FrostbiteRconPacket &packet);
    void responseVars3pCamCommand(const FrostbiteRconPacket &packet);
    void responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet);
    void responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet);
    void responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet);
    void responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet);
    void responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet);
    void responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet);
    void responseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet);
    void responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet);
    void responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet);
    void responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet);
    void responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet);
    void responseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet);
    void responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet);
    void responseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet);
    void responseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet);

signals:
    // Events

    // Commands
    void onLoginPlainTextCommand();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(const bool &auth);
    void onServerInfoCommand();
    void onAdminHelpCommand();
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, const int &build);
    void onListPlayersCommand();
    void onAdminEventsEnabledCommand();
    void onAdminPasswordCommand();
    void onAdminEffectiveMaxPlayersCommand();
    void onAdminSayCommand();
    void onAdminYellCommand();
    void onAdminKickPlayerCommand();
    void onAdminListPlayersCommand();
    void onAdminMovePlayerCommand();
    void onAdminKillPlayerCommand();
    void onPlayerIdleDurationCommand();
    void onPlayerIsAliveCommand();
    void onPlayerPingCommand();
    void onSquadListActiveCommand();
    void onSquadListPlayersCommand();
    void onSquadPrivateCommand();
    void onSquadLeaderCommand();
    void onPunkBusterIsActiveCommand();
    void onPunkBusterActivateCommand();
    void onPunkBusterPbSvCommandCommand();
    void onBanListLoadCommand();
    void onBanListSaveCommand();
    void onBanListAddCommand();
    void onBanListRemoveCommand();
    void onBanListClearCommand();
    void onBanListListCommand();
    void onReservedSlotsListLoadCommand();
    void onReservedSlotsListSaveCommand();
    void onReservedSlotsListAddCommand();
    void onReservedSlotsListRemoveCommand();
    void onReservedSlotsListClearCommand();
    void onReservedSlotsListListCommand();
    void onReservedSlotsListAggressiveJoinCommand();
    void onMapListLoadCommand();
    void onMapListSaveCommand();
    void onMapListAddCommand();
    void onMapListRemoveCommand();
    void onMapListClearCommand();
    void onMapListListCommand();
    void onMapListSetNextMapIndexCommand();
    void onMapListGetMapIndicesCommand();
    void onMapListGetRoundsCommand();
    void onMapListEndRoundCommand();
    void onMapListRunNextRoundCommand();
    void onMapListRestartRoundCommand();
    void onMapListAvailableMapsCommand();
    void onVarsRankedCommand();
    void onVarsServerNameCommand();
    void onVarsGamePasswordCommand();
    void onVarsAutoBalanceCommand();
    void onVarsRoundStartPlayerCountCommand();
    void onVarsRoundRestartPlayerCountCommand();
    void onVarsRoundLockdownCountdownCommand();
    void onVarsServerMessageCommand();
    void onVarsFriendlyFireCommand();
    void onVarsMaxPlayersCommand();
    void onVarsServerDescriptionCommand();
    void onVarsKillCamCommand();
    void onVarsMiniMapCommand();
    void onVarsHudCommand();
    void onVarsCrossHairCommand();
    void onvars3dSpottingCommand();
    void onVarsMiniMapSpottingCommand();
    void onVarsNameTagCommand();
    void onVars3pCamCommand();
    void onVarsRegenerateHealthCommand();
    void onVarsTeamKillCountForKickCommand();
    void onVarsTeamKillValueForKickCommand();
    void onVarsTeamKillValueIncreaseCommand();
    void onVarsTeamKillValueDecreasePerSecondCommand();
    void onVarsTeamKillKickForBanCommand();
    void onVarsIdleTimeoutCommand();
    void onVarsIdleBanRoundsCommand();
    void onVarsVehicleSpawnAllowedCommand();
    void onVarsVehicleSpawnDelayCommand();
    void onVarsSoldierHealthCommand();
    void onVarsPlayerRespawnTimeCommand();
    void onVarsPlayerManDownTimeCommand();
    void onVarsBulletDamageCommand();
    void onVarsGameModeCounterCommand();
    void onVarsOnlySquadLeaderSpawnCommand();
    void onVarsUnlockModeCommand();
    void onVarsPremiumStatusCommand();
    void onVarsBannerUrlCommand();
    void onVarsRoundsPerMapCommand();
    void onVarsGunMasterWeaponsPresetCommand();

};

#endif // BF3CONNECTION_H
