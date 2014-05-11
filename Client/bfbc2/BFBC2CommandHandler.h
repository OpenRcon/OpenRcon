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

class BFBC2Connection;
class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    BFBC2CommandHandler(BFBC2Connection *parent = nullptr);
    ~BFBC2CommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

private:
    /* Parse */

    // Events
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Commands.

    // General commands.
    void parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Admin commands.
    /*void parseAdminRunScriptCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminRestartMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/

    void parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    // Ban List commands.
    /*void parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    // Reserved Slots commands.
    /*void parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseReservedSlotsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Map List commands.
    /*void parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListAppendCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListInsertCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Vars commands.
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHardCoreCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRankLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    /*void parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/
    // Level Vars commands.
    /*void parseLevelVarsSetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLevelVarsGetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLevelVarsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLevelVarsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);*/

signals:
    // Events
    void onPlayerJoinEvent(const QString &player);
    void onPlayerAuthenticatedEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, const QString &kit, const QStringList &weaponList);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &player, const QString &message, const QString &target);
    void onPlayerKickedEvent(const QString &player, const QString &reason);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onPunkBusterVersionEvent(const QString &version);
    void onServerLoadingLevelEvent(const QString &levelName, int roundsPlayed, int roundsTotal);
    void onServerLevelStartedEvent();
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    // Commands
    void onListPlayersCommand();
    void onEventsEnabledCommand();
    void onHelpCommand(const QStringList &helpList);
    void onAdminRunScriptCommand();
    void onPunkBusterPbSvCommand();
    void onServerInfoCommand(const QStringList &serverInfo);
    void onAdminYellCommand();
    void onAdminSayCommand();
    void onAdminRunNextRoundCommand();
    void onAdminRestartRoundCommand();
    void onAdminEndRoundCommand();
    void onAdminRunNextLevelCommand();
    void onAdminRestartMapCommand();
    void onAdminCurrentLevelCommand();
    void onMapListNextLevelIndexCommand(int index);
    void onAdminSupportedMapsCommand();
    void onAdminSetPlaylistCommand();
    void onAdminGetPlaylistCommand();
    void onAdminGetPlaylistsCommand();
    void onAdminKickPlayerCommand();
    void onAdminListPlayersCommand(const PlayerList &playerList);
    void onAdminMovePlayerCommand();
    void onAdminKillPlayerCommand();
    void onVarsTextChatModerationModeCommand(const QString &mode);
    void onVarsTextChatSpamTriggerCountCommand(int count);
    void onVarsTextChatSpamDetectionTimeCommand(int count);
    void onVarsTextChatSpamCoolDownTimeCommand(int count);
    void onTextChatModerationListLoadCommand();
    void onTextChatModerationListSaveCommand();
    void onTextChatModerationListAddCommand();
    void onTextChatModerationListRemoveCommand();
    void onTextChatModerationListClearCommand();
    void onTextChatModerationListListCommand();
    void onBanListLoadCommand();
    void onBanListSaveCommand();
    void onBanListAddCommand();
    void onBanListRemoveCommand();
    void onBanListClearCommand();
    void onBanListListCommand(const QStringList &banList);
    void onReservedSlotsLoadCommand();
    void onReservedSlotsSaveCommand();
    void onReservedSlotsAddPlayerCommand();
    void onReservedSlotsRemovePlayerCommand();
    void onReservedSlotsClearCommand();
    void onReservedSlotsListCommand(const QStringList &reservedSlotList);
    void onMapListLoadCommand();
    void onMapListSaveCommand();
    void onMapListListCommand(const QStringList &mapList);
    void onMapListClearCommand();
    void onMapListRemoveCommand();
    void onMapListAppendCommand();
    void onMaplistInsertCommand();
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsAdminPasswordCommand();
    void onVarsGamePasswordCommand();
    void onVarsPunkBusterCommand();
    void onVarsHardCoreCommand();
    void onVarsRankedCommand();
    void onVarsRankLimitCommand();
    void onVarsTeamBalanceCommand();
    void onVarsFriendlyFireCommand();
    void onVarsCurrentPlayerLimitCommand();
    void onVarsMaxPlayerLimitCommand();
    void onVarsPlayerLimitCommand();
    void onVarsBannerUrlCommand(const QString &bannerUrl);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsKillCamCommand();
    void onVarsMiniMapCommand();
    void onVarsCrossHairCommand();
    void onVars3dSpottingCommand();
    void onVarsMiniMapSpottingCommand();
    void onVarsThirdPersonVehicleCamerasCommand();
    void onVarsTeamKillCountForKickCommand();
    void onVarsTeamKillValueForKickCommand();
    void onVarsTeamKillValueIncreaseCommand();
    void onVarsTeamKillValueDecreasePerSecondCommand();
    void onVarsIdleTimeoutCommand(int seconds);
    void onVarsProfanityFilterCommand();
    void onLevelVarsSetCommand();
    void onLevelVarsGetCommand();
    void onLevelVarsEvaluateCommand();
    void onLevelVarsClearCommand();
    void onLevelVarsListCommand();

};

#endif // BFBC2COMMANDHANDLER_H
