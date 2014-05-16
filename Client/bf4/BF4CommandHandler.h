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

#include "Frostbite2CommandHandler.h"
#include "PlayerInfo.h"

#include "BF4ServerInfo.h"

class BF4CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF4CommandHandler(FrostbiteConnection *parent = nullptr);
    ~BF4CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc
    void sendServerInfoCommand();
    void sendCurrentLevelCommand();
    void sendListPlayersCommand(const PlayerSubset &playerSubset);

    // Admin
    void sendAdminListPlayersCommand(const PlayerSubset &playerSubset);
    void sendAdminShutdownCommand();
    void sendAdminShutdownCommand(bool graceful);
    void sendAdminShutdownCommand(bool graceful, int seconds);

    // FairFight
    void sendFairFightActivateCommand();
    void sendFairFightDeactivateCommand();
    void sendFairFightIsActiveCommand();

    // Spectator list
    void sendSpectatorListAddCommand(const QString &player);
    void sendSpectatorListClearCommand();
    void sendSpectatorListListCommand(int index = 0);
    void sendSpectatorListRemoveCommand(const QString &player);
    void sendSpectatorListSaveCommand();

    // Variables
    void sendVars3dSpottingCommand();
    void sendVars3dSpottingCommand(bool enabled);
    void sendVars3pCamCommand();
    void sendVars3pCamCommand(bool enabled);
    void sendVarsAlwaysAllowSpectatorsCommand();
    void sendVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void sendVarsAutoBalanceCommand();
    void sendVarsAutoBalanceCommand(bool enabled);
    void sendVarsBulletDamageCommand(int damage = -1);
    void sendVarsCommanderCommand();
    void sendVarsCommanderCommand(bool enabled);
    void sendVarsForceReloadWholeMagsCommand();
    void sendVarsForceReloadWholeMagsCommand(bool enabled);
    void sendVarsFriendlyFireCommand();
    void sendVarsFriendlyFireCommand(bool enabled);
    void sendVarsGameModeCounterCommand(int scale = -1);
    void sendVarsGamePasswordCommand(const QString &password = 0);
    void sendVarsHitIndicatorsEnabledCommand();
    void sendVarsHitIndicatorsEnabledCommand(bool enabled);
    void sendVarsHudCommand();
    void sendVarsHudCommand(bool enabled);
    void sendVarsIdleBanRoundsCommand(int rounds = -1);
    void sendVarsIdleTimeoutCommand(int seconds = -1);
    void sendVarsKillCamCommand();
    void sendVarsKillCamCommand(bool enabled);
    void sendVarsMaxPlayersCommand(int players = -1);
    void sendVarsMaxSpectatorsCommand(int spectators = -1);
    void sendVarsMiniMapCommand();
    void sendVarsMiniMapCommand(bool enabled);
    void sendVarsMiniMapSpottingCommand();
    void sendVarsMiniMapSpottingCommand(bool enabled);
    void sendVarsMpExperienceCommand(const QString &experience = 0);
    void sendVarsNameTagCommand();
    void sendVarsNameTagCommand(bool enabled);
    void sendVarsOnlySquadLeaderSpawnCommand();
    void sendVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void sendVarsPlayerRespawnTimeCommand(int respawnTime = -1);
    void sendVarsPresetCommand(const QString &serverPreset = 0, bool lockPresetSetting = 0);
    void sendVarsRegenerateHealthCommand();
    void sendVarsRegenerateHealthCommand(bool enabled);
    void sendVarsRoundLockdownCountdownCommand(int seconds = -1);
    void sendVarsRoundRestartPlayerCountCommand(int players = -1);
    void sendVarsRoundStartPlayerCountCommand(int players = -1);
    void sendVarsRoundTimeLimitCommand(int percent = -1);
    void sendVarsRoundWarmupTimeoutCommand(int timeout = -1);
    void sendVarsServerDescriptionCommand(const QString &description = 0);
    void sendVarsServerMessageCommand(const QString &message = 0);
    void sendVarsServerNameCommand(const QString &name = 0);
    void sendVarsServerTypeCommand(const QString &type = 0);
    void sendVarsSoldierHealthCommand(int percent = -1);
    void sendVarsTeamFactionOverrideCommand(int teamId = -1, int factionId = -1);
    void sendVarsTeamKillCountForKickCommand(int count = -1);
    void sendVarsTeamKillKickForBanCommand(int count = -1);
    void sendVarsTeamKillValueDecreasePerSecondCommand(int count = -1);
    void sendVarsTeamKillValueForKickCommand(int count = -1);
    void sendVarsTeamKillValueIncreaseCommand(int count = -1);
    void sendVarsTicketBleedRateCommand(int percent = -1);
    void sendVarsUnlockModeCommand(const QString &type = 0);
    void sendVarsVehicleSpawnAllowedCommand();
    void sendVarsVehicleSpawnAllowedCommand(bool enabled);
    void sendVarsVehicleSpawnDelayCommand(int percent = -1);

private:
    /* Parse events */
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminShutDownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // FairFight
    /*void parseFairFightActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Spectator List
    /*void parseSpectatorListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSpectatorListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/

    // Vars
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent);
    void parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent);
    void parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastPacketSent);
    void parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    QList<PlayerInfo> parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    void onPlayerDisconnectEvent(const QString &player);
    void onServerMaxPlayerCountChangeEvent();
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);

    /* Command signals */
    // Misc
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onCurrentLevelCommand(const QString &level);
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    // Admin
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
//    void onAdminShutDownCommand();

    // FairFight
//    void onFairFightActivateCommand();
//    void onFairFightDeactivateCommand();
    void onFairFightIsActiveCommand(bool isActive);

    // Spectator List
//    void onSpectatorListAddCommand();
//    void onSpectatorListClearCommand();
    void onSpectatorListListCommand(const QStringList &spectatorList);
//    void onSpectatorListRemoveCommand();
//    void onSpectatorListSaveCommand();

    // Vars
    void onVars3dSpottingCommand(bool enabled);
    void onVars3pCamCommand(bool enabled);
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void onVarsAutoBalanceCommand(bool enabled);
    void onVarsBulletDamageCommand(int percent);
    void onVarsCommanderCommand(bool enabled);
    void onVarsForceReloadWholeMagsCommand(bool enabled);
    void onVarsFriendlyFireCommand(bool enabled);
    void onVarsGameModeCounterCommand(int percent);
    void onVarsGamePasswordCommand(const QString &password);
    void onVarsHitIndicatorsEnabledCommand(bool enabled);
    void onVarsHudCommand(bool enabled);
    void onVarsIdleBanRoundsCommand(int rounds);
    void onVarsIdleTimeoutCommand(int seconds);
    void onVarsKillCamCommand(bool enabled);
    void onVarsMaxPlayersCommand(int playerCount);
    void onVarsMaxSpectatorsCommand(int spectatorCount);
    void onVarsMiniMapCommand(bool enabled);
    void onVarsMiniMapSpottingCommand(bool enabled);
    void onVarsMpExperienceCommand(const QString &experience);
    void onVarsNameTagCommand(bool enabled);
    void onVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void onVarsPlayerRespawnTimeCommand(int respawnTime);
    void onVarsPresetCommand(const QString &serverPreset, bool lockPresetSetting);
    void onVarsRegenerateHealthCommand(bool enabled);
    void onVarsRoundLockdownCountdownCommand(int seconds);
    void onVarsRoundRestartPlayerCountCommand(int players);
    void onVarsRoundStartPlayerCountCommand(int players);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int time);
    void onVarsServerDescriptionCommand(const QString &description);
    void onVarsServerMessageCommand(const QString &message);
    void onVarsServerNameCommand(const QString &name);
    void onVarsServerTypeCommand(const QString &type);
    void onVarsSoldierHealthCommand(int health);
    void onVarsTeamFactionOverrideCommand(int team1, int team2, int team3, int team4);
    void onVarsTeamKillCountForKickCommand(int count);
    void onVarsTeamKillKickForBanCommand(int count);
    void onVarsTeamKillValueDecreasePerSecondCommand(int count);
    void onVarsTeamKillValueForKickCommand(int count);
    void onVarsTeamKillValueIncreaseCommand(int count);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsUnlockModeCommand(const QString &type);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);

};

#endif // BF4COMMANDHANDLER_H
