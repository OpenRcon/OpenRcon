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

#ifndef BF3COMMANDHANDLER_H
#define BF3COMMANDHANDLER_H

#include "Frostbite2CommandHandler.h"

class Frostbite2ServerInfo;

class BF3CommandHandler : public Frostbite2CommandHandler
{
    Q_OBJECT

public:
    BF3CommandHandler(FrostbiteConnection *parent = nullptr);
    ~BF3CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc
    void sendServerInfoCommand();
    void sendCurrentLevelCommand();
    void sendListPlayersCommand(const PlayerSubset &playerSubset);

    // Admin
    void sendAdminEffectiveMaxPlayersCommand();
    void sendAdminListPlayersCommand();

    // Variables
    void sendVarsRankedCommand();
    void sendVarsRankedCommand(bool ranked);
    void sendVarsCrossHairCommand();
    void sendVarsCrossHairCommand(bool enabled);
    void sendVarsPlayerManDownTimeCommand(int percent = -1);
    void sendVarsPremiumStatusCommand();
    void sendVarsPremiumStatusCommand(bool enabled);
    void sendVarsBannerUrlCommand(const QString &bannerUrl = QString());
    void sendVarsRoundsPerMapCommand(int rounds = -1);
    void sendVarsGunMasterWeaponsPresetCommand(int weaponPreset = -1);

private:
    /* Parse commands */
    // Misc
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin
    void parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Variables
    void parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Command signals */
    // Misc
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);
    void onCurrentLevelCommand(const QString &currentLevel);
    void onListPlayersCommand();

    // Admin
    void onAdminEffectiveMaxPlayersCommand(int effectiveMaxPlayers);
    void onAdminListPlayersCommand();

    // Variables
    void onVarsRankedCommand(bool ranked);
    void onVarsCrossHairCommand(bool enabled);
    void onVarsPlayerManDownTimeCommand(int percent);
    void onVarsPremiumStatusCommand(bool enabled);
    void onVarsBannerUrlCommand(const QString &bannerUrl);
    void onVarsRoundsPerMapCommand(int rounds);
    void onVarsGunMasterWeaponsPresetCommand(int weaponPreset);

};

#endif // BF3COMMANDHANDLER_H
