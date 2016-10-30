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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FROSTBITECOMMANDHANDLER_H
#define FROSTBITECOMMANDHANDLER_H

#include "CommandHandler.h"

class FrostbiteConnection;
class FrostbiteRconPacket;
enum class PlayerSubsetEnum;
class Frostbite2ServerInfo;
class BF3ServerInfo;
class BF4ServerInfo;
class BanListEntry;
class MapListEntry;

class FrostbiteCommandHandler : public CommandHandler
{
    Q_OBJECT

public:
    FrostbiteCommandHandler(QObject *parent = nullptr);
    virtual ~FrostbiteCommandHandler() override;

    void setConnection(FrostbiteConnection *connection);

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Send commands */
    // Misc
    void sendLoginPlainTextCommand(const QString &password);
    void sendLoginHashedCommand(const QByteArray &salt = QByteArray(), const QString &password = QString());
    void sendServerInfoCommand();
    void sendLogoutCommand();
    void sendQuitCommand();
    void sendVersionCommand();
    //listPlayers <players>

    // Admin
    void sendAdminKickPlayerCommand(const QString &player, const QString &reason);
    void sendAdminKillPlayerCommand(const QString &player);
    //admin.listPlayers <players>
    void sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill);
    void sendAdminSayCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter = -1);
    void sendAdminYellCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter = -1);
    void sendAdminYellCommand(const QString &message, int duration, const PlayerSubsetEnum &playerSubset, int parameter = -1);

    // Banning
    void sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason);
    void sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason);
    void sendBanListClearCommand();
    void sendBanListListCommand(int index = 0);
    void sendBanListLoadCommand();
    void sendBanListRemoveCommand(const QString &idType, const QString &id);
    void sendBanListSaveCommand();

    // Maplist
    void sendMapListClearCommand();
    void sendMapListListCommand(int index = 0);
    void sendMapListLoadCommand();
    void sendMapListRemoveCommand(int index);
    void sendMapListSaveCommand();

    // Punkbuster
    void sendPunkBusterPbSvCommand(const QString &command);

    // Reserved Slots

    // Variables
    void sendVars3dSpottingCommand();
    void sendVars3dSpottingCommand(bool enabled);
    void sendVarsFriendlyFireCommand();
    void sendVarsFriendlyFireCommand(bool enabled);
    void sendVarsGamePasswordCommand(const QString &password = QString());
    void sendVarsIdleTimeoutCommand(int seconds = -1);
    void sendVarsKillCamCommand();
    void sendVarsKillCamCommand(bool enabled);
    void sendVarsMiniMapCommand();
    void sendVarsMiniMapCommand(bool enabled);
    void sendVarsMiniMapSpottingCommand();
    void sendVarsMiniMapSpottingCommand(bool enabled);
    void sendVarsServerDescriptionCommand(const QString &description = QString());
    void sendVarsServerNameCommand(const QString &name = QString());
    void sendVarsTeamKillCountForKickCommand(int count = -1);
    void sendVarsTeamKillValueDecreasePerSecondCommand(int count = -1);
    void sendVarsTeamKillValueForKickCommand(int count = -1);
    void sendVarsTeamKillValueIncreaseCommand(int count = -1);

private:
    /* Parse events */
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //listPlayers <players>

    // Admin
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    //admin.listPlayers <players>
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    void parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // Maplist
    //mapList.clear
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //mapList.load
    //mapList.remove <index>
    //mapList.save

    // Punkbuster
    //punkBuster.pb_sv_command <command>

    // Reserved Slots

    // Variables
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

protected:
    FrostbiteConnection *connection;

signals:
    /* Event signals */
    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, int teamId);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    /* Command signals */
    // Misc
    void onLoginPlainTextCommand(bool auth);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);
    void onServerInfoCommand(const BF3ServerInfo &serverInfo);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, int build);
    //listPlayers <players>

    // Admin
    //admin.kickPlayer <player name> <reason>
    //admin.killPlayer <player name>
    //admin.listPlayers <players>
    //admin.movePlayer <name> <teamId> <squadId> <forceKill>
    //admin.say <message> <players>
    //admin.yell <message> <duration> <players>

    // Banning
    //banList.add <id-type> <id, timeout>
    //banList.clear
    void onBanListListCommand(const QList<BanListEntry> &banList);
    //banList.load
    //banList.remove <id-type> <id>
    //banList.save

    // Maplist
    //mapList.clear
    void onMapListListCommand(const QList<MapListEntry> &mapList);
    //mapList.load
    //mapList.remove <index>
    //mapList.save

    // Punkbuster
    //punkBuster.pb_sv_command <command>

    // Reserved Slots

    // Variables
    void onVars3dSpottingCommand(bool enabled);
    void onVarsFriendlyFireCommand(bool enabled);
    void onVarsGamePasswordCommand(const QString &password);
    void onVarsIdleTimeoutCommand(int seconds);
    void onVarsKillCamCommand(bool enabled);
    void onVarsMiniMapCommand(bool enabled);
    void onVarsMiniMapSpottingCommand(bool enabled);
    void onVarsServerDescriptionCommand(const QString &description);
    void onVarsServerNameCommand(const QString &name);
    void onVarsTeamKillCountForKickCommand(int count);
    void onVarsTeamKillValueDecreasePerSecondCommand(int count);
    void onVarsTeamKillValueForKickCommand(int count);
    void onVarsTeamKillValueIncreaseCommand(int count);

};

#endif // FROSTBITECOMMANDHANDLER_H
