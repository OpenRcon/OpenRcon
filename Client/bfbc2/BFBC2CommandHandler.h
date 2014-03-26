#ifndef BFBC2COMMANDHANDLER_H
#define BFBC2COMMANDHANDLER_H

#include <QDebug>

#include "FrostbiteCommandHandler.h"


typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;

class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    explicit BFBC2CommandHandler(QObject *parent = 0);
    ~BFBC2CommandHandler();

    void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

private:
    // Call events.
    void eventOnPlayerJoin(const FrostbiteRconPacket &packet);
    void eventOnPlayerAuthenticated(const FrostbiteRconPacket &packet);
    void eventOnPlayerLeave(const FrostbiteRconPacket &packet);
    void eventOnPlayerSpawn(const FrostbiteRconPacket &packet);
    void eventOnPlayerKill(const FrostbiteRconPacket &packet);
    void eventOnPlayerChat(const FrostbiteRconPacket &packet);
    void eventOnPlayerKicked(const FrostbiteRconPacket &packet);
    void eventOnPlayerSquadChange(const FrostbiteRconPacket &packet);
    void eventOnPlayerTeamChange(const FrostbiteRconPacket &packet);
    void eventOnPunkBusterMessage(const FrostbiteRconPacket &packet);
    void eventOnPunkBusterVersion(const FrostbiteRconPacket &packet);
    void eventOnServerLoadingLevel(const FrostbiteRconPacket &packet);
    void eventOnServerLevelStarted(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOver(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOverPlayers(const FrostbiteRconPacket &packet);
    void eventOnServerRoundOverTeamScores(const FrostbiteRconPacket &packet);

    // Call commands.
    void commandLoginPlainText(const FrostbiteRconPacket &packet);
    void commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSendPacket);
    void commandLogout(const FrostbiteRconPacket &packet);
    void commandQuit(const FrostbiteRconPacket &packet);
    void commandVersion(const FrostbiteRconPacket &packet);
    void commandListPlayers(const FrostbiteRconPacket &packet);
    void commandEventsEnabled(const FrostbiteRconPacket &packet);
    void commandHelp(const FrostbiteRconPacket &packet);
    void commandAdminRunScript(const FrostbiteRconPacket &packet);
    void commandPunkBusterPbSvCommand(const FrostbiteRconPacket &packet);
    void commandServerInfo(const FrostbiteRconPacket &packet);
    void commandAdminYell(const FrostbiteRconPacket &packet);
    void commandAdminSay(const FrostbiteRconPacket &packet);
    void commandAdminRunNextRound(const FrostbiteRconPacket &packet);
    void commandAdminRestartRound(const FrostbiteRconPacket &packet);
    void commandAdminEndRound(const FrostbiteRconPacket &packet);
    void commandAdminRunNextLevel(const FrostbiteRconPacket &packet);
    void commandAdminRestartMap(const FrostbiteRconPacket &packet);
    void commandAdminCurrentLevel(const FrostbiteRconPacket &packet);
    void commandMapListNextLevelIndex(const FrostbiteRconPacket &packet);
    void commandAdminSupportedMaps(const FrostbiteRconPacket &packet);
    void commandAdminSetPlaylist(const FrostbiteRconPacket &packet);
    void commandAdminGetPlaylist(const FrostbiteRconPacket &packet);
    void commandAdminGetPlaylists(const FrostbiteRconPacket &packet);
    void commandAdminKickPlayer(const FrostbiteRconPacket &packet);
    void commandAdminListPlayers(const FrostbiteRconPacket &packet);
    void commandAdminMovePlayer(const FrostbiteRconPacket &packet);
    void commandAdminKillPlayer(const FrostbiteRconPacket &packet);
    void commandVarsTextChatModerationMode(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamTriggerCount(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamDetectionTime(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamCoolDownTime(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListLoad(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListSave(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListAdd(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListRemove(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListClear(const FrostbiteRconPacket &packet);
    void commandTextChatModerationListList(const FrostbiteRconPacket &packet);
    void commandBanListLoad(const FrostbiteRconPacket &packet);
    void commandBanListSave(const FrostbiteRconPacket &packet);
    void commandBanListAdd(const FrostbiteRconPacket &packet);
    void commandBanListRemove(const FrostbiteRconPacket &packet);
    void commandBanListClear(const FrostbiteRconPacket &packet);
    void commandBanListList(const FrostbiteRconPacket &packet);
    void commandReservedSlotsLoad(const FrostbiteRconPacket &packet);
    void commandReservedSlotsSave(const FrostbiteRconPacket &packet);
    void commandReservedSlotsAddPlayer(const FrostbiteRconPacket &packet);
    void commandReservedSlotsRemovePlayer(const FrostbiteRconPacket &packet);
    void commandReservedSlotsClear(const FrostbiteRconPacket &packet);
    void commandReservedSlotsList(const FrostbiteRconPacket &packet);
    void commandMapListLoad(const FrostbiteRconPacket &packet);
    void commandMapListSave(const FrostbiteRconPacket &packet);
    void commandMapListList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void commandMapListClear(const FrostbiteRconPacket &packet);
    void commandMapListRemove(const FrostbiteRconPacket &packet);
    void commandMapListAppend(const FrostbiteRconPacket &packet);
    void commandMaplistInsert(const FrostbiteRconPacket &packet);
    void commandVarsServerName(const FrostbiteRconPacket &packet);
    void commandVarsAdminPassword(const FrostbiteRconPacket &packet);
    void commandVarsGamePassword(const FrostbiteRconPacket &packet);
    void commandVarsPunkBuster(const FrostbiteRconPacket &packet);
    void commandVarsHardCore(const FrostbiteRconPacket &packet);
    void commandVarsRanked(const FrostbiteRconPacket &packet);
    void commandVarsRankLimit(const FrostbiteRconPacket &packet);
    void commandVarsTeamBalance(const FrostbiteRconPacket &packet);
    void commandVarsFriendlyFire(const FrostbiteRconPacket &packet);
    void commandVarsCurrentPlayerLimit(const FrostbiteRconPacket &packet);
    void commandVarsMaxPlayerLimit(const FrostbiteRconPacket &packet);
    void commandVarsPlayerLimit(const FrostbiteRconPacket &packet);
    void commandVarsBannerUrl(const FrostbiteRconPacket &packet);
    void commandVarsServerDescription(const FrostbiteRconPacket &packet);
    void commandVarsKillCam(const FrostbiteRconPacket &packet);
    void commandVarsMiniMap(const FrostbiteRconPacket &packet);
    void commandVarsCrossHair(const FrostbiteRconPacket &packet);
    void commandVars3dSpotting(const FrostbiteRconPacket &packet);
    void commandVarsMiniMapSpotting(const FrostbiteRconPacket &packet);
    void commandVarsThirdPersonVehicleCameras(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillCountForKick(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueForKick(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueIncrease(const FrostbiteRconPacket &packet);
    void commandVarsTeamKillValueDecreasePerSecond(const FrostbiteRconPacket &packet);
    void commandVarsIdleTimeout(const FrostbiteRconPacket &packet);
    void commandVarsProfanityFilter(const FrostbiteRconPacket &packet);
    void commandLevelVarsSet(const FrostbiteRconPacket &packet);
    void commandLevelVarsGet(const FrostbiteRconPacket &packet);
    void commandLevelVarsEvaluate(const FrostbiteRconPacket &packet);
    void commandLevelVarsClear(const FrostbiteRconPacket &packet);
    void commandLevelVarsList(const FrostbiteRconPacket &packet);
    void commandUnknown(const FrostbiteRconPacket &packet);

signals:
    void onLogMessage(const int &type, const QString &message);
    void onRefresh();
    void onLogEvent(const QString &event, const QString &message);
    void onIngameCommands(const QString &player, const QString &command);

    void onAuthenticated();

    // Event signals.
    void onPlayerJoin(const QString &player);
    void onPlayerAuthenticated(const QString &player, const QString &guid);
    void onPlayerLeave(const QString &player, const QString &info);
    void onPlayerSpawn(const QString &player, const QString &kit, const QStringList &weaponList);
    void onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChat(const QString &player, const QString &message, const QString &target);
    void onPlayerKicked(const QString &player, const QString &reason);
    void onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessage(const QString &message);
    void onPunkBusterVersion(const QString &version);
    void onServerLoadingLevel(const QString &levelName, const int &roundsPlayed, const int &roundsTotal);
    void onServerLevelStarted();
    void onServerRoundOver(const int &winningTeamId);
    void onServerRoundOverPlayers(const QString &playerInfo);
    void onServerRoundOverTeamScores(const QString &teamScores);

    // Command signals.
    void onLoginPlainTextCommand(const QString &response);
    void onLoginHashedCommand(const QByteArray &salt);
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
    void onUnknownCommand();

};

#endif // BFBC2COMMANDHANDLER_H
