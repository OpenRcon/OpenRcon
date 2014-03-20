/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#ifndef ORBFBC2COMMANDS_H
#define ORBFBC2COMMANDS_H

#include "ORBFBC2_global.h"

#include <QObject>
#include <QStringList>
#include <QString>

#include "ORBFBC2RconPacket.h"

class OR_BFBC2_EXPORT ORBFBC2Commands : QObject
{
    Q_OBJECT

public:
    explicit ORBFBC2Commands(const QString &command, const ORBFBC2RconPacket &packet, const ORBFBC2RconPacket &lastSentPacket);
    ~ORBFBC2Commands();

private:
    ORBFBC2RconPacket mPacket;
    ORBFBC2RconPacket mLastSentPacket;

    // Events
    void eventPlayerOnJoin();
    void eventPlayerOnAuthenticated();
    void eventPlayerOnLeave();
    void eventPlayerOnSpawn();
    void eventPlayerOnChat();
    void eventPlayerOnKicked();
    void eventPlayerOnSquadChange();
    void eventPlayerOnTeamChange();
    void eventPunkBusterOnMessage();
    void eventServerOnLoadingLevel();
    void eventServerOnLevelStarted();
    void eventServerOnRoundOver();
    void eventServerOnRoundOverPlayers();
    void eventServerOnRoundOverTeamScores();

    // Commands
    void commandLoginPlainText();
    void commandLoginHashed();
    void commandLogout();
    void commandQuit();
    void commandVersion();
    void commandListPlayers();
    void commandEventsEnabled();
    void commandHelp();
    void commandAdminRunScript();
    void commandPunkBusterPbSvCommand();
    void commandServerInfo();
    void commandAdminYell();
    void commandAdminSay();
    void commandAdminRunNextRound();
    void commandAdminRestartRound();
    void commandAdminEndRound();
    void commandAdminRunNextLevel();
    void commandAdminRestartMap();
    void commandAdminCurrentLevel();
    void commandMaplistNextLevelIndex();
    void commandAdminSupportedMaps();
    void commandAdminSetPlaylist();
    void commandAdminGetPlaylist();
    void commandAdminGetPlaylists();
    void commandAdminKickPlayer();
    void commandAdminListPlayers();
    void commandAdminMovePlayer();
    void commandAdminKillPlayer();
    void commandVarsTextChatModerationMode();
    void commandVarsTextChatSpamTriggerCount();
    void commandVarsTextChatSpamDetectionTime();
    void commandVarsTextChatSpamCoolDownTime();
    void commandTextCharModerationListLoad();
    void commandTextCharModerationListSave();
    void commandTextCharModerationListAdd();
    void commandTextCharModerationListRemove();
    void commandTextCharModerationListClear();
    void commandTextCharModerationListList();
    void commandBanListLoad();
    void commandBanListSave();
    void commandBanListAdd();
    void commandBanListRemove();
    void commandBanListClear();
    void commandBanListList();
    void commandReservedSlotsLoad();
    void commandReservedSlotsSave();
    void commandReservedSlotsAddPlayer();
    void commandReservedSlotsRemovePlayer();
    void commandReservedSlotsClear();
    void commandReservedSlotsList();
    void commandMapListLoad();
    void commandMapListSave();
    void commandMapListList();
    void commandMapListClear();
    void commandMapListRemove();
    void commandMapListAppend();
    void commandMapListInsert();
    void commandVarsServerName();
    void commandVarsAdminPassword();
    void commandVarsGamePassword();
    void commandVarsPunkBuster();
    void commandVarsRanked();
    void commandVarsRankLimit();
    void commandVarsTeamBalance();
    void commandVarsFriendlyFire();
    void commandVarsCurrentPlayerLimit();
    void commandVarsMaxPlayerLimit();
    void commandVarsPlayerLimit();
    void commandVarsBannerUrl();
    void commandVarsServerDescription();
    void commandVarsKillCam();
    void commandVarsMiniMap();
    void commandVarsCrossHair();
    void commandVars3dSpotting();
    void commandVarsMiniMapSpotting();
    void commandVarsThirdPersonVehicleCameras();
    void commandVarsTeamKillCountForKick();
    void commandVarsTeamKillValueForKick();
    void commandVarsTeamKillValueIncrease();
    void commandVarsTeamKillValueDecreasePerSecond();
    void commandVarsIdleTimeout();
    void commandVarsProfanityFilter();
    void commandLevelVarsSet();
    void commandLevelVarsGet();
    void commandLevelVarsEvaluate();
    void commandLevelVarsClear();
    void commandLevelVarsList();

signals:
    // Events
    void signalEventPlayerOnJoin();
    void signalEventPlayerOnAuthenticated();
    void signalEventPlayerOnLeave();
    void signalEventPlayerOnSpawn();
    void signalEventPlayerOnChat();
    void signalEventPlayerOnKicked();
    void signalEventPlayerOnSquadChange();
    void signalEventPlayerOnTeamChange();
    void signalEventPunkBusterOnMessage();
    void signalEventServerOnLoadingLevel();
    void signalEventServerOnLevelStarted();
    void signalEventServerOnRoundOver();
    void signalEventServerOnRoundOverPlayers();
    void signalEventServerOnRoundOverTeamScores();

    // Commands
    void signalCommandLoginPlainText();
    void signalCommandLoginHashed();
    void signalCommandLogout();
    void signalCommandQuit();
    void signalCommandVersion(QStringList packetList);
    void signalCommandListPlayers();
    void signalCommandEventsEnabled();
    void signalCommandHelp();
    void signalCommandAdminRunScript();
    void signalCommandPunkBusterPbSvCommand();
    void signalCommandServerInfo();
    void signalCommandAdminYell();
    void signalCommandAdminSay();
    void signalCommandAdminRunNextRound();
    void signalCommandAdminRestartRound();
    void signalCommandAdminEndRound();
    void signalCommandAdminRunNextLevel();
    void signalCommandAdminRestartMap();
    void signalCommandAdminCurrentLevel();
    void signalCommandMaplistNextLevelIndex();
    void signalCommandAdminSupportedMaps();
    void signalCommandAdminSetPlaylist();
    void signalCommandAdminGetPlaylist();
    void signalCommandAdminGetPlaylists();
    void signalCommandAdminKickPlayer();
    void signalCommandAdminListPlayers();
    void signalCommandAdminMovePlayer();
    void signalCommandAdminKillPlayer();
    void signalCommandVarsTextChatModerationMode();
    void signalCommandVarsTextChatSpamTriggerCount();
    void signalCommandVarsTextChatSpamDetectionTime();
    void signalCommandVarsTextChatSpamCoolDownTime();
    void signalCommandTextCharModerationListLoad();
    void signalCommandTextCharModerationListSave();
    void signalCommandTextCharModerationListAdd();
    void signalCommandTextCharModerationListRemove();
    void signalCommandTextCharModerationListClear();
    void signalCommandTextCharModerationListList();
    void signalCommandBanListLoad();
    void signalCommandBanListSave();
    void signalCommandBanListAdd();
    void signalCommandBanListRemove();
    void signalCommandBanListClear();
    void signalCommandBanListList();
    void signalCommandReservedSlotsLoad();
    void signalCommandReservedSlotsSave();
    void signalCommandReservedSlotsAddPlayer();
    void signalCommandReservedSlotsRemovePlayer();
    void signalCommandReservedSlotsClear();
    void signalCommandReservedSlotsList();
    void signalCommandMapListLoad();
    void signalCommandMapListSave();
    void signalCommandMapListList();
    void signalCommandMapListClear();
    void signalCommandMapListRemove();
    void signalCommandMapListAppend();
    void signalCommandMapListInsert();
    void signalCommandVarsServerName();
    void signalCommandVarsAdminPassword();
    void signalCommandVarsGamePassword();
    void signalCommandVarsPunkBuster();
    void signalCommandVarsRanked();
    void signalCommandVarsRankLimit();
    void signalCommandVarsTeamBalance();
    void signalCommandVarsFriendlyFire();
    void signalCommandVarsCurrentPlayerLimit();
    void signalCommandVarsMaxPlayerLimit();
    void signalCommandVarsPlayerLimit();
    void signalCommandVarsBannerUrl();
    void signalCommandVarsServerDescription();
    void signalCommandVarsKillCam();
    void signalCommandVarsMiniMap();
    void signalCommandVarsCrossHair();
    void signalCommandVars3dSpotting();
    void signalCommandVarsMiniMapSpotting();
    void signalCommandVarsThirdPersonVehicleCameras();
    void signalCommandVarsTeamKillCountForKick();
    void signalCommandVarsTeamKillValueForKick();
    void signalCommandVarsTeamKillValueIncrease();
    void signalCommandVarsTeamKillValueDecreasePerSecond();
    void signalCommandVarsIdleTimeout();
    void signalCommandVarsProfanityFilter();
    void signalCommandLevelVarsSet();
    void signalCommandLevelVarsGet();
    void signalCommandLevelVarsEvaluate();
    void signalCommandLevelVarsClear();
    void signalCommandLevelVarsList();

};

#endif // BFBC2COMMANDS_H
