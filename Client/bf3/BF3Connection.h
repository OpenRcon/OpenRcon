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
    BF3Connection(QObject *parent = 0);
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
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet);
    void parseAdminHelpCommand(const FrostbiteRconPacket &packet);
    void parseLogoutCommand(const FrostbiteRconPacket &packet);
    void parseQuitCommand(const FrostbiteRconPacket &packet);
    void parseVersionCommand(const FrostbiteRconPacket &packet);
    void parseListPlayersCommand(const FrostbiteRconPacket &packet);
    void parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void parseAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void parseAdminSayCommand(const FrostbiteRconPacket &packet);
    void parseAdminYellCommand(const FrostbiteRconPacket &packet);
    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet);
    void parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet);
    void parsePlayerPingCommand(const FrostbiteRconPacket &packet);
    void parseSquadListActiveCommand(const FrostbiteRconPacket &packet);
    void parseSquadListPlayersCommand(const FrostbiteRconPacket &packet);
    void parseSquadPrivateCommand(const FrostbiteRconPacket &packet);
    void parseSquadLeaderCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet);
    void parseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void parseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void parseBanListAddCommand(const FrostbiteRconPacket &packet);
    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseBanListClearCommand(const FrostbiteRconPacket &packet);
    void parseBanListListCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet);
    void parseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void parseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void parseMapListAddCommand(const FrostbiteRconPacket &packet);
    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseMapListClearCommand(const FrostbiteRconPacket &packet);
    void parseMapListListCommand(const FrostbiteRconPacket &packet);
    void parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet);
    void parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet);
    void parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet);
    void parseMapListEndRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet);
    void parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet);
    void parseVarsRankedCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerMessageCommand(const FrostbiteRconPacket &packet);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void parseVarsHudCommand(const FrostbiteRconPacket &packet);
    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet);
    void parsevars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVarsNameTagCommand(const FrostbiteRconPacket &packet);
    void parseVars3pCamCommand(const FrostbiteRconPacket &packet);
    void parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet);
    void parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet);
    void parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet);
    void parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet);
    void parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet);
    void parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet);
    void parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet);
    void parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet);
    void parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet);
    void parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet);
    void parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet);
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet);
    void parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet);
    void parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet);

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
