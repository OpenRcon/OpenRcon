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

#ifndef BFBC2CONNECTION_H
#define BFBC2CONNECTION_H

#include "FrostbiteConnection.h"

typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;

class BFBC2Connection : public FrostbiteConnection
{
    Q_OBJECT

public:
    BFBC2Connection(QObject *parent = 0);
    ~BFBC2Connection();

protected:
    void parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

private:
    /* Parse */

    // Events
    void parsePlayerJoinEvent(const FrostbiteRconPacket &packet);
    void parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet);
    void parsePlayerLeaveEvent(const FrostbiteRconPacket &packet);
    void parsePlayerSpawnEvent(const FrostbiteRconPacket &packet);
    void parsePlayerKillEvent(const FrostbiteRconPacket &packet);
    void parsePlayerChatEvent(const FrostbiteRconPacket &packet);
    void parsePlayerKickedEvent(const FrostbiteRconPacket &packet);
    void parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet);
    void parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet);
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet);
    void parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet);
    void parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet);
    void parseServerLevelStartedEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet);
    void parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet);

    // Commands
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSendPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet);
    void parseQuitCommand(const FrostbiteRconPacket &packet);
    void parseVersionCommand(const FrostbiteRconPacket &packet);
    void parseListPlayersCommand(const FrostbiteRconPacket &packet);
    void parseEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void parseHelpCommand(const FrostbiteRconPacket &packet);
    void parseAdminRunScriptCommand(const FrostbiteRconPacket &packet);
    void parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void parseServerInfoCommand(const FrostbiteRconPacket &packet);
    void parseAdminYellCommand(const FrostbiteRconPacket &packet);
    void parseAdminSayCommand(const FrostbiteRconPacket &packet);
    void parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet);
    void parseAdminEndRoundCommand(const FrostbiteRconPacket &packet);
    void parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet);
    void parseAdminRestartMapCommand(const FrostbiteRconPacket &packet);
    void parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet);
    void parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet);
    void parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet);
    void parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet);
    void parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet);
    void parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet);
    void parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminListPlayersCommand(const FrostbiteRconPacket &packet);
    void parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet);
    void parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet);
    void parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet);
    void parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet);
    void parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet);
    void parseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void parseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void parseBanListAddCommand(const FrostbiteRconPacket &packet);
    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseBanListClearCommand(const FrostbiteRconPacket &packet);
    void parseBanListListCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet);
    void parseReservedSlotsListCommand(const FrostbiteRconPacket &packet);
    void parseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void parseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListClearCommand(const FrostbiteRconPacket &packet);
    void parseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void parseMapListAppendCommand(const FrostbiteRconPacket &packet);
    void parseMaplistInsertCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet);
    void parseVarsHardCoreCommand(const FrostbiteRconPacket &packet);
    void parseVarsRankedCommand(const FrostbiteRconPacket &packet);
    void parseVarsRankLimitCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet);
    void parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet);
    void parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void parseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void parseVarsCrossHairCommand(const FrostbiteRconPacket &packet);
    void parseVars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet);
    void parseLevelVarsSetCommand(const FrostbiteRconPacket &packet);
    void parseLevelVarsGetCommand(const FrostbiteRconPacket &packet);
    void parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet);
    void parseLevelVarsClearCommand(const FrostbiteRconPacket &packet);
    void parseLevelVarsListCommand(const FrostbiteRconPacket &packet);

signals:
    // Events
    void onPlayerJoinEvent(const QString &player);
    void onPlayerAuthenticatedEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, const QString &kit, const QStringList &weaponList);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChatEvent(const QString &player, const QString &message, const QString &target);
    void onPlayerKickedEvent(const QString &player, const QString &reason);
    void onPlayerSquadChangeEvent(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChangeEvent(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onPunkBusterVersionEvent(const QString &version);
    void onServerLoadingLevelEvent(const QString &levelName, const int &roundsPlayed, const int &roundsTotal);
    void onServerLevelStartedEvent();
    void onServerRoundOverEvent(const int &winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    // Commands
    void onLoginPlainTextCommand(const QString &parse);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand();
    void onLogoutCommand(const QString &parse);
    void onQuitCommand(const QString &parse);
    void onVersionCommand(const QString &type, const int &build);
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
    void onMapListNextLevelIndexCommand(const int &index);
    void onAdminSupportedMapsCommand();
    void onAdminSetPlaylistCommand();
    void onAdminGetPlaylistCommand();
    void onAdminGetPlaylistsCommand();
    void onAdminKickPlayerCommand();
    void onAdminListPlayersCommand(const PlayerList &playerList);
    void onAdminMovePlayerCommand();
    void onAdminKillPlayerCommand();
    void onVarsTextChatModerationModeCommand(const QString &mode);
    void onVarsTextChatSpamTriggerCountCommand(const int &count);
    void onVarsTextChatSpamDetectionTimeCommand(const int &count);
    void onVarsTextChatSpamCoolDownTimeCommand(const int &count);
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
    void onVarsIdleTimeoutCommand(const int &seconds);
    void onVarsProfanityFilterCommand();
    void onLevelVarsSetCommand();
    void onLevelVarsGetCommand();
    void onLevelVarsEvaluateCommand();
    void onLevelVarsClearCommand();
    void onLevelVarsListCommand();

};

#endif // BFBC2CONNECTION_H
