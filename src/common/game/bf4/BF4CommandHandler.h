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

enum class BF4PresetEnum;
enum class BF4ServerTypeEnum;

class BF4CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF4CommandHandler(QObject *parent = nullptr);
    ~BF4CommandHandler() final;

    bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) final;

public slots:
    /* Send commands */
    // Admin
    void sendAdminShutdownCommand();
    void sendAdminShutdownCommand(bool graceful, int seconds = -1);

    /// Not confirmed.
    //admin.teamSwitchPlayer

    // FairFight
    void sendFairFightActivateCommand();
    void sendFairFightDeactivateCommand();
    void sendFairFightIsActiveCommand();

    // Spectator list
    /// BF4 Only.
    /// Note: The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    void sendSpectatorListAddCommand(const QString &player);
    void sendSpectatorListClearCommand();
    void sendSpectatorListListCommand(int index = -1);
    void sendSpectatorListRemoveCommand(const QString &player);
    void sendSpectatorListSaveCommand();

    // Variables
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

    /// Not confirmed.
    //"vars.idleTimeoutActiveMinPlayersPercent
    //"vars.isCompetitive
    //"vars.outHighFrequency
    //"vars.outHighFrequencyRconCap

private:
    /* Parse events */
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Admin
    //admin.shutDown <gracefulShutdown: boolean> <timeInSeconds: integer>

    /// Not confirmed.
    //admin.teamSwitchPlayer

    // FairFight
    /// BF4 Only.
    //fairFight.activate
    //fairfight.deactivate
    void parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Spectator list
    /// BF4 Only.
    /// The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    //spectatorList.add <player name>
    //spectatorList.clear
    void parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //spectatorList.remove <player name>
    //spectatorList.save

    // Variables
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

    /// Not confirmed.
    //"vars.idleTimeoutActiveMinPlayersPercent
    //"vars.isCompetitive
    //"vars.outHighFrequency
    //"vars.outHighFrequencyRconCap

signals:
    /* Event signals */
    void onPlayerDisconnectEvent(const QString &player);

    /* Command signals */
    // Admin
    //admin.shutDown <gracefulShutdown: boolean> <timeInSeconds: integer>

    /// Not confirmed.
    //admin.teamSwitchPlayer

    // FairFight
    /// BF4 Only.
    //fairFight.activate
    //fairfight.deactivate
    void onFairFightIsActiveCommand(bool isActive);

    // Spectator list
    //// The Spectator list will only be in effect if vars.alwaysAllowSpectators is set to false
    //spectatorList.add <player name>
    //spectatorList.clear
    void onSpectatorListListCommand(const QStringList &spectatorList);
    //spectatorList.remove <player name>
    //spectatorList.save

    // Variables
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
    void onVarsServerTypeCommand(const BF4ServerTypeEnum &serverType);
    void onVarsTeamFactionOverrideCommand(int team1, int team2, int team3, int team4);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsRoundPlayersReadyBypassTimerCommand(int timer);
    void onVarsRoundPlayersReadyMinCountCommand(int count);
    void onVarsRoundPlayersReadyPercentCommand(int percent);
    //vars.isNoobOnlyJoin <enabled>
    //vars.serverTickTime

    /// Not confirmed.
    //"vars.idleTimeoutActiveMinPlayersPercent
    //"vars.isCompetitive
    //"vars.outHighFrequency
    //"vars.outHighFrequencyRconCap

};

#endif // BF4COMMANDHANDLER_H
