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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FROSTBITE2COMMANDHANDLER_H
#define FROSTBITE2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"
#include "PlayerSubset.h"
#include "MapListEntry.h"
#include "BanListEntry.h"

class Frostbite2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    Frostbite2CommandHandler(FrostbiteConnection *parent = nullptr);
    ~Frostbite2CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc

    // Admin
    void sendAdminEventsEnabledCommand(bool enabled);
    void sendAdminHelpCommand();
    void sendAdminKickPlayerCommand(const QString &player, const QString &reason);
    void sendAdminKillPlayerCommand(const QString &player);
    void sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill);
    void sendAdminPasswordCommand();
    void sendAdminPasswordCommand(const QString &password);
    void sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset, int parameter = -1);
    void sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset, int parameter = -1);
    void sendAdminYellCommand(const QString &message, int duration, const PlayerSubset &playerSubset, int parameter = -1);

    // BanList
    void sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason);
    void sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason);
    void sendBanListClearCommand();
    void sendBanListListCommand(int index = 0);
    void sendBanListLoadCommand();
    void sendBanListRemoveCommand(const QString &idType, const QString &id);
    void sendBanListSaveCommand();

    // FairFight

    // Maplist
    void sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet = 0);
    void sendMapListAvailableMapsCommand(const QString &filter);
    void sendMapListClearCommand();
    void sendMapListEndRoundCommand(int teamId);
    void sendMapListGetMapIndicesCommand();
    void sendMapListGetRoundsCommand();
    void sendMapListListCommand(int index = 0);
    void sendMapListLoadCommand();
    void sendMapListRemoveCommand(int index);
    void sendMapListRestartRoundCommand();
    void sendMapListRunNextRoundCommand();
    void sendMapListSaveCommand();
    void sendMapListSetNextMapIndexCommand(int index);

    // Player
    void sendPlayerIdleDurationCommand(const QString &player);
    void sendPlayerIsAliveCommand(const QString &player);
    void sendPlayerPingCommand(const QString &player);

    // PunkBuster
    void sendPunkBusterActivateCommand();
    void sendPunkBusterIsActiveCommand();
    void sendPunkBusterPbSvCommand(const QString &command);

    // Reserved Slots
    void sendReservedSlotsListAddCommand(const QString &player);
    void sendReservedSlotsListAggressiveJoinCommand();
    void sendReservedSlotsListAggressiveJoinCommand(bool enabled);
    void sendReservedSlotsListClearCommand();
    void sendReservedSlotsListListCommand();
    void sendReservedSlotsListLoadCommand();
    void sendReservedSlotsListRemoveCommand(const QString &player);
    void sendReservedSlotsListSaveCommand();

    // Squad
    void sendSquadLeaderCommand(int teamId, int squadId, const QString &player);
    void sendSquadListActiveCommand(int teamId);
    void sendSquadListPlayersCommand(int teamId, int squadId);
    void sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate);

    // Vars

protected:
    PlayerSubset getPlayerSubset(const QString &playerSubsetString);
    QString getPlayerSubsetString(const PlayerSubset &playerSubset);

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

    // Admin
    void parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // BanList
//    void parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // FairFight

    // MapList
//    void parseMapListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Player
    void parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // PunkBuster
//    void parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Reserverd Slots
//    void parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Squad
    void parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseSquadListActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Vars

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

    // Admin
    void onAdminEventsEnabledCommand(bool enabled);
    void onAdminHelpCommand(const QStringList &commandList);
//    void onAdminKickPlayerCommand();
//    void onAdminKillPlayerCommand();
//    void onAdminMovePlayerCommand();
    void onAdminPasswordCommand(const QString &password);
//    void onAdminSayCommand();
//    void onAdminShutDownCommand();
//    void onAdminYellCommand();

    // BanList
//    void onBanListAddCommand();
//    void onBanListClearCommand();
    void onBanListListCommand(const BanList &banList);
//    void onBanListLoadCommand();
//    void onBanListRemoveCommand();
//    void onBanListSaveCommand();

    // FairFight

    // MapList
//    void onMapListAddCommand();
    void onMapListAvailableMapsCommand(const QString &value, const QStringList &list);
//    void onMapListClearCommand();
//    void onMapListEndRoundCommand();
    void onMapListGetMapIndicesCommand(int currentMapIndex, int nextMapIndex);
    void onMapListGetRoundsCommand(int currentRound, int totalRounds);
    void onMapListListCommand(const MapList &mapList);
//    void onMapListLoadCommand();
//    void onMapListRemoveCommand();
//    void onMapListRestartRoundCommand();
//    void onMapListRunNextRoundCommand();
//    void onMapListSaveCommand();
//    void onMapListSetNextMapIndexCommand();

    // Player
    void onPlayerIdleDurationCommand(float idleDuration);
    void onPlayerIsAliveCommand(bool alive);
    void onPlayerPingCommand(const QString &player, int ping);

    // Punkbuster
//    void onPunkBusterActivateCommand();
    void onPunkBusterIsActiveCommand(bool isActive);
//    void onPunkBusterPbSvCommand();

    // Reserved Slots
//    void onReservedSlotsListAddCommand();
    void onReservedSlotsListAggressiveJoinCommand(bool enabled);
//    void onReservedSlotsListClearCommand();
    void onReservedSlotsListListCommand(const QStringList &reservedSlotList);
//    void onReservedSlotsListLoadCommand();
//    void onReservedSlotsListRemoveCommand();
//    void onReservedSlotsListSaveCommand();

    // Squad
    void onSquadLeaderCommand(const QString &player);
    void onSquadListActiveCommand();
    void onSquadListPlayersCommand(const QStringList &playerList);
    void onSquadPrivateCommand(bool isPrivate);

    // Vars

};

#endif // FROSTBITE2COMMANDHANDLER_H
