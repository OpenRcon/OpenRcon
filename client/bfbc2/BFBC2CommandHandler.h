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

#ifndef BFBC2COMMANDHANDLER_H
#define BFBC2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;

class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    BFBC2CommandHandler(FrostbiteConnection *parent = nullptr);
    ~BFBC2CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

    /* Send commands */
    // Misc
//    void sendListPlayersCommand();
//    void sendEventsEnabledCommand();
//    void sendHelpCommand();
//    void sendServerInfoCommand();

    // Admin
//    void sendAdminRunscriptCommand();
//    void sendAdminYellCommand();
//    void sendAdminSayCommand();
//    void sendAdminRunNextRoundCommand();
//    void sendAdminRestartRoundCommand();
//    void sendAdminEndRoundCommand();
//    void sendAdminRunNextLevelCommand();
//    void sendAdminRestartMapCommand();
//    void sendAdminCurrentLevelCommand();
//    void sendAdminSupportedMapsCommand();
//    void sendAdminSetPlaylistCommand();
//    void sendAdminGetPlaylistCommand();
//    void sendAdminGetPlaylistsCommand();
//    void sendAdminKickPlayerCommand();
//    void sendAdminListPlayersCommand();
//    void sendAdminMovePlayerCommand();
//    void sendAdminKillPlayerCommand();

    // Text Chat Moderation List
//    void sendTextChatModerationListLoadCommand();
//    void sendTextChatModerationListSaveCommand();
//    void sendTextChatModerationListAddCommand();
//    void sendTextChatModerationListRemoveCommand();
//    void sendTextChatModerationListClearCommand();
//    void sendTextChatModerationListListCommand();

    // Reserved Slots
//    void sendReservedSlotsLoadCommand();
//    void sendReservedSlotsSaveCommand();
//    void sendReservedSlotsAddPlayerCommand();
//    void sendReservedSlotsRemovePlayerCommand();
//    void sendReservedSlotsClearCommand();
//    void sendReservedSlotsListCommand();

    // MapList
//    void sendMapListNextLevelIndexCommand();
//    void sendMapListLoadCommand();
//    void sendMapListSaveCommand();
//    void sendMapListListCommand();
//    void sendMapListClearCommand();
//    void sendMapListRemoveCommand();
//    void sendMapListAppendCommand();
//    void sendMapListInsertCommand();

    // Variables
//    void sendVarsTextChatModerationModeCommand();
//    void sendVarsTextChatSpamTriggerCountCommand();
//    void sendVarsTextChatSpamDetectionTimeCommand();
//    void sendVarsTextChatSpamCoolDownTimeCommand();
//    void sendVarsAdminPasswordCommand();
//    void sendVarsPunkBusterCommand();
//    void sendVarsHardCoreCommand();
//    void sendVarsRankedCommand();
//    void sendVarsRankLimitCommand();
//    void sendVarsTeamBalanceCommand();
//    void sendVarsCurrentPlayerLimitCommand();
//    void sendVarsMaxPlayerLimitCommand();
//    void sendVarsPlayerLimitCommand();
//    void sendVarsBannerUrlCommand();
//    void sendVarsCrossHairCommand();
//    void sendVarsThirdPersonVehicleCamerasCommand();
//    void sendVarsProfanityFilterCommand();

    // Level variables
//    void sendLevelVarsSetCommand();
//    void sendLevelVarsGetCommand();
//    void sendLevelVarsEvaluateCommand();
//    void sendLevelVarsClearCommand();
//    void sendLevelVarsListCommand();

private:
    /* Parse events */
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
//    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin
//    void parseAdminRunscriptCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminRestartMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Text Chat Moderation List
//    void parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Reserved Slots
//    void parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // MapList
    void parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListAppendCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseMapListInsertCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Variables
    void parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsHardCoreCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsRankLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Level variables
//    void parseLevelVarsSetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseLevelVarsGetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseLevelVarsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseLevelVarsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    void onPlayerJoinEvent(const QString &player);
    void onPlayerAuthenticatedEvent(const QString &player, const QString &guid);
    void onPlayerSpawnEvent(const QString &player, const QString &kit, const QStringList &weaponList);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerKickedEvent(const QString &player, const QString &reason);
    void onPunkBusterVersionEvent(const QString &version);
    void onServerLoadingLevelEvent(const QString &levelName, int roundsPlayed, int roundsTotal);
    void onServerLevelStartedEvent();

    /* Command signals */
    // Misc
//    void onListPlayersCommand();
//    void onEventsEnabledCommand();
    void onHelpCommand(const QStringList &helpList);
    void onServerInfoCommand(const QStringList &serverInfo);

    // Admin
//    void onAdminRunscriptCommand();
//    void onAdminYellCommand();
//    void onAdminSayCommand();
//    void onAdminRunNextRoundCommand();
//    void onAdminRestartRoundCommand();
//    void onAdminEndRoundCommand();
//    void onAdminRunNextLevelCommand();
//    void onAdminRestartMapCommand();
//    void onAdminCurrentLevelCommand();
//    void onAdminSupportedMapsCommand();
//    void onAdminSetPlaylistCommand();
//    void onAdminGetPlaylistCommand();
//    void onAdminGetPlaylistsCommand();
//    void onAdminKickPlayerCommand();
    void onAdminListPlayersCommand(const PlayerList &playerList);
//    void onAdminMovePlayerCommand();
//    void onAdminKillPlayerCommand();

    // Text Chat Moderation List
//    void onTextChatModerationListLoadCommand();
//    void onTextChatModerationListSaveCommand();
//    void onTextChatModerationListAddCommand();
//    void onTextChatModerationListRemoveCommand();
//    void onTextChatModerationListClearCommand();
//    void onTextChatModerationListListCommand();

    // Reserved Slots
//    void onReservedSlotsLoadCommand();
//    void onReservedSlotsSaveCommand();
//    void onReservedSlotsAddPlayerCommand();
//    void onReservedSlotsRemovePlayerCommand();
//    void onReservedSlotsClearCommand();
    void onReservedSlotsListCommand(const QStringList &reservedSlotsList);

    // MapList
    void onMapListNextLevelIndexCommand(int index);
//    void onMapListLoadCommand();
//    void onMapListSaveCommand();
    void onMapListListCommand(const QStringList &mapList);
//    void onMapListClearCommand();
//    void onMapListRemoveCommand();
//    void onMapListAppendCommand();
//    void onMapListInsertCommand();

    // Variables
    void onVarsTextChatModerationModeCommand(const QString &mode);
    void onVarsTextChatSpamTriggerCountCommand(int count);
    void onVarsTextChatSpamDetectionTimeCommand(int count);
    void onVarsTextChatSpamCoolDownTimeCommand(int count);
//    void onVarsAdminPasswordCommand();
//    void onVarsPunkBusterCommand();
//    void onVarsHardCoreCommand();
//    void onVarsRankedCommand();
//    void onVarsRankLimitCommand();
//    void onVarsTeamBalanceCommand();
//    void onVarsCurrentPlayerLimitCommand();
//    void onVarsMaxPlayerLimitCommand();
//    void onVarsPlayerLimitCommand();
    void onVarsBannerUrlCommand(const QString &bannerUrl);
//    void onVarsCrossHairCommand();
//    void onVarsThirdPersonVehicleCamerasCommand();
//    void onVarsProfanityFilterCommand();

    // Level variables
//    void onLevelVarsSetCommand();
//    void onLevelVarsGetCommand();
//    void onLevelVarsEvaluateCommand();
//    void onLevelVarsClearCommand();
//    void onLevelVarsListCommand();

};

#endif // BFBC2COMMANDHANDLER_H
