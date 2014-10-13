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

class BF4ServerInfo;
struct PlayerInfo;

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
    void sendVarsAlwaysAllowSpectatorsCommand();
    void sendVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void sendVarsCommanderCommand();
    void sendVarsCommanderCommand(bool enabled);
    void sendVarsForceReloadWholeMagsCommand();
    void sendVarsForceReloadWholeMagsCommand(bool enabled);
    void sendVarsHitIndicatorsEnabledCommand();
    void sendVarsHitIndicatorsEnabledCommand(bool enabled);
    void sendVarsMaxSpectatorsCommand(int spectators = -1);
    void sendVarsMpExperienceCommand(const QString &experience = QString());
    void sendVarsPresetCommand(const QString &serverPreset = QString(), bool lockPresetSetting = false);
    void sendVarsRoundTimeLimitCommand(int percent = -1);
    void sendVarsRoundWarmupTimeoutCommand(int timeout = -1);
    void sendVarsServerTypeCommand(const QString &type = QString());
    void sendVarsTeamFactionOverrideCommand(int teamId = -1, int factionId = -1);
    void sendVarsTicketBleedRateCommand(int percent = -1);

private:
    /* Parse events */
    void parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

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
//    void parseFairFightActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Spectator List
//    void parseSpectatorListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseSpectatorListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Variables
    void parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
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

    QList<PlayerInfo> parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    void onPlayerDisconnectEvent(const QString &player);

    /* Command signals */
    // Misc
    void onServerInfoCommand(BF4ServerInfo &serverInfo);
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

    // Variables
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void onVarsCommanderCommand(bool enabled);
    void onVarsForceReloadWholeMagsCommand(bool enabled);
    void onVarsHitIndicatorsEnabledCommand(bool enabled);
    void onVarsMaxSpectatorsCommand(int spectatorCount);
    void onVarsMpExperienceCommand(const QString &experience);
    void onVarsPresetCommand(const QString &serverPreset, bool lockPresetSetting);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int timeout);
    void onVarsServerTypeCommand(const QString &type);
    void onVarsTeamFactionOverrideCommand(int team1, int team2, int team3, int team4);
    void onVarsTicketBleedRateCommand(int percent);

};

#endif // BF4COMMANDHANDLER_H
