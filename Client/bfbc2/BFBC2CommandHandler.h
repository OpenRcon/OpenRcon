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
    explicit BFBC2CommandHandler(QObject *parent = 0);
    ~BFBC2CommandHandler();

    void parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

private:
    // Call events.
    void responsePlayerJoinEvent(const FrostbiteRconPacket &packet);
    void responsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet);
    void responsePlayerLeaveEvent(const FrostbiteRconPacket &packet);
    void responsePlayerSpawnEvent(const FrostbiteRconPacket &packet);
    void responsePlayerKillEvent(const FrostbiteRconPacket &packet);
    void responsePlayerChatEvent(const FrostbiteRconPacket &packet);
    void responsePlayerKickedEvent(const FrostbiteRconPacket &packet);
    void responsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet);
    void responsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet);
    void responsePunkBusterMessageEvent(const FrostbiteRconPacket &packet);
    void responsePunkBusterVersionEvent(const FrostbiteRconPacket &packet);
    void responseServerLoadingLevelEvent(const FrostbiteRconPacket &packet);
    void responseServerLevelStartedEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet);
    void responseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet);

    // Call commands.
    void responseLoginPlainTextCommand(const FrostbiteRconPacket &packet);
    void responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSendPacket);
    void responseLogoutCommand(const FrostbiteRconPacket &packet);
    void responseQuitCommand(const FrostbiteRconPacket &packet);
    void responseVersionCommand(const FrostbiteRconPacket &packet);
    void responseListPlayersCommand(const FrostbiteRconPacket &packet);
    void responseEventsEnabledCommand(const FrostbiteRconPacket &packet);
    void responseHelpCommand(const FrostbiteRconPacket &packet);
    void responseAdminRunScriptCommand(const FrostbiteRconPacket &packet);
    void responsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void responseServerInfoCommand(const FrostbiteRconPacket &packet);
    void responseAdminYellCommand(const FrostbiteRconPacket &packet);
    void responseAdminSayCommand(const FrostbiteRconPacket &packet);
    void responseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet);
    void responseAdminRestartRoundCommand(const FrostbiteRconPacket &packet);
    void responseAdminEndRoundCommand(const FrostbiteRconPacket &packet);
    void responseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet);
    void responseAdminRestartMapCommand(const FrostbiteRconPacket &packet);
    void responseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet);
    void responseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet);
    void responseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet);
    void responseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet);
    void responseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet);
    void responseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet);
    void responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminListPlayersCommand(const FrostbiteRconPacket &packet);
    void responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet);
    void responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet);
    void responseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet);
    void responseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet);
    void responseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet);
    void responseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet);
    void responseTextChatModerationListListCommand(const FrostbiteRconPacket &packet);
    void responseBanListLoadCommand(const FrostbiteRconPacket &packet);
    void responseBanListSaveCommand(const FrostbiteRconPacket &packet);
    void responseBanListAddCommand(const FrostbiteRconPacket &packet);
    void responseBanListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseBanListClearCommand(const FrostbiteRconPacket &packet);
    void responseBanListListCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsClearCommand(const FrostbiteRconPacket &packet);
    void responseReservedSlotsListCommand(const FrostbiteRconPacket &packet);
    void responseMapListLoadCommand(const FrostbiteRconPacket &packet);
    void responseMapListSaveCommand(const FrostbiteRconPacket &packet);
    void responseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void responseMapListClearCommand(const FrostbiteRconPacket &packet);
    void responseMapListRemoveCommand(const FrostbiteRconPacket &packet);
    void responseMapListAppendCommand(const FrostbiteRconPacket &packet);
    void responseMaplistInsertCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerNameCommand(const FrostbiteRconPacket &packet);
    void responseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet);
    void responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet);
    void responseVarsPunkBusterCommand(const FrostbiteRconPacket &packet);
    void responseVarsHardCoreCommand(const FrostbiteRconPacket &packet);
    void responseVarsRankedCommand(const FrostbiteRconPacket &packet);
    void responseVarsRankLimitCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet);
    void responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet);
    void responseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void responseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void responseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet);
    void responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet);
    void responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet);
    void responseVarsKillCamCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapCommand(const FrostbiteRconPacket &packet);
    void responseVarsCrossHairCommand(const FrostbiteRconPacket &packet);
    void responseVars3dSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet);
    void responseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet);
    void responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet);
    void responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet);
    void responseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet);
    void responseLevelVarsSetCommand(const FrostbiteRconPacket &packet);
    void responseLevelVarsGetCommand(const FrostbiteRconPacket &packet);
    void responseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet);
    void responseLevelVarsClearCommand(const FrostbiteRconPacket &packet);
    void responseLevelVarsListCommand(const FrostbiteRconPacket &packet);

signals:
    void onLogMessage(const int &type, const QString &message);
    void onRefresh();
    void onLogEvent(const QString &event, const QString &message);
    void onIngameCommands(const QString &player, const QString &command);

    // Event signals.
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

    // Command signals.
    void onLoginPlainTextCommand(const QString &response);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand();
    void onLogoutCommand(const QString &response);
    void onQuitCommand(const QString &response);
    void onVersionCommand(const QString &type, const int &buildId, const QString &version);
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

#endif // BFBC2COMMANDHANDLER_H
