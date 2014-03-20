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

#include "ORBFBC2Commands.h"

ORBFBC2Commands::ORBFBC2Commands(const QString &command, const ORBFBC2RconPacket &packet, const ORBFBC2RconPacket &lastSentPacket) : mPacket(packet), mLastSentPacket(lastSentPacket)
{
    // Commands
    if (command == "login.plainText") {
        commandLoginPlainText();
    } else if (command == "login.hashed") {
        commandLoginHashed();
    } else if (command == "logout") {
        commandLogout();
    } else if (command == "quit") {
        commandQuit();
    } else if (command == "version") {
        commandVersion();
    } else if (command == "listPlayers") {
        commandListPlayers();
    } else if (command == "eventsEnabled") {
        commandEventsEnabled();
    } else if (command == "help") {
        commandHelp();
    } else if (command == "admin.runScript") {
        commandAdminRunScript();
    } else if (command == "punkBuster.pb_sv_command") {
        commandPunkBusterPbSvCommand();
    } else if (command == "serverInfo") {
        commandServerInfo();
    } else if (command == "admin.yell") {
        commandAdminYell();
    } else if (command == "admin.say") {
        commandAdminSay();
    } else if (command == "admin.runNextRound") {
        commandAdminRunNextRound();
    } else if (command == "admin.restartRound") {
        commandAdminRestartRound();
    } else if (command == "admin.endRound") {
        commandAdminEndRound();
    } else if (command == "admin.runNextLevel") {
        commandAdminRunNextLevel();
    } else if (command == "admin.restartMap") {
        commandAdminRestartMap();
    } else if (command == "admin.currentLevel") {
        commandAdminCurrentLevel();
    } else if (command == "mapList.nextLevelIndex") {
        commandMaplistNextLevelIndex();
    } else if (command == "admin.supportedMaps") {
        commandAdminSupportedMaps();
    } else if (command == "admin.setPlaylist") {
        commandAdminSetPlaylist();
    } else if (command == "admin.getPlaylist") {
        commandAdminGetPlaylist();
    } else if (command == "admin.getPlaylists") {
        commandAdminGetPlaylists();
    } else if (command == "admin.kickPlayer") {
        commandAdminKickPlayer();
    } else if (command == "admin.listPlayers") {
        commandAdminListPlayers();
    } else if (command == "admin.movePlayer") {
        commandAdminMovePlayer();
    } else if (command == "admin.killPlayer") {
        commandAdminKillPlayer();
    } else if (command == "vars.textChatModerationMode") {
        commandVarsTextChatModerationMode();
    } else if (command == "vars.textChatSpamTriggerCount") {
        commandVarsTextChatSpamTriggerCount();
    } else if (command == "vars.textChatSpamDetectionTime") {
        commandVarsTextChatSpamDetectionTime();
    } else if (command == "vars.textChatSpamCoolDownTime") {
        commandVarsTextChatSpamCoolDownTime();
    } else if (command == "textChatModerationList.load") {
        commandTextCharModerationListLoad();
    } else if (command == "textChatModerationList.save") {
        commandTextCharModerationListSave();
    } else if (command == "textChatModerationList.add") {
        commandTextCharModerationListAdd();
    } else if (command == "textChatModerationList.remove") {
        commandTextCharModerationListRemove();
    } else if (command == "textChatModerationList.clear") {
        commandTextCharModerationListClear();
    } else if (command == "textChatModerationList.list") {
        commandTextCharModerationListList();
    } else if (command == "banList.load") {
        commandBanListLoad();
    } else if (command == "banList.save") {
        commandBanListSave();
    } else if (command == "banList.add") {
        commandBanListAdd();
    } else if (command == "banList.remove") {
        commandBanListRemove();
    } else if (command == "banList.clear") {
        commandBanListClear();
    } else if (command == "banList.list") {
        commandBanListList();
    } else if (command == "reservedSlots.load") {
        commandReservedSlotsLoad();
    } else if (command == "reservedSlots.save") {
        commandReservedSlotsSave();
    } else if (command == "reservedSlots.addPlayer") {
        commandReservedSlotsAddPlayer();
    } else if (command == "reservedSlots.removePlayer") {
        commandReservedSlotsRemovePlayer();
    } else if (command == "reservedSlots.clear") {
        commandReservedSlotsClear();
    } else if (command == "reservedSlots.list") {
        commandReservedSlotsList();
    } else if (command == "reservedSlots.load") {
        commandReservedSlotsLoad();
    } else if (command == "mapList.load") {
        commandMapListLoad();
    } else if (command == "mapList.save") {
        commandMapListSave();
    } else if (command == "mapList.list") {
        commandMapListList();
    } else if (command == "mapList.clear") {
        commandMapListClear();
    } else if (command == "mapList.remove") {
        commandMapListRemove();
    } else if (command == "mapList.append") {
        commandMapListAppend();
    } else if (command == "mapList.insert") {
        commandMapListInsert();
    } else if (command == "vars.serverName") {
        commandVarsServerName();
    } else if (command == "vars.adminPassword") {
        commandVarsAdminPassword();
    } else if (command == "vars.gamePassword") {
        commandVarsGamePassword();
    } else if (command == "vars.punkBuster") {
        commandVarsPunkBuster();
    } else if (command == "vars.ranked") {
        commandVarsRanked();
    } else if (command == "vars.rankLimit") {
        commandVarsRankLimit();
    } else if (command == "vars.teamBalance") {
        commandVarsTeamBalance();
    } else if (command == "vars.friendlyFire") {
        commandVarsFriendlyFire();
    } else if (command == "vars.currentPlayerLimit") {
        commandVarsCurrentPlayerLimit();
    } else if (command == "vars.maxPlayerLimit") {
        commandVarsMaxPlayerLimit();
    } else if (command == "vars.playerLimit") {
        commandVarsPlayerLimit();
    } else if (command == "vars.bannerUrl") {
        commandVarsBannerUrl();
    } else if (command == "vars.serverDescription") {
        commandVarsServerDescription();
    } else if (command == "vars.killCam") {
        commandVarsKillCam();
    } else if (command == "vars.miniMap") {
        commandVarsMiniMap();
    } else if (command == "vars.crossHair") {
        commandVarsCrossHair();
    } else if (command == "vars.3dSpotting") {
        commandVars3dSpotting();
    } else if (command == "vars.miniMapSpotting") {
        commandVarsMiniMapSpotting();
    } else if (command == "vars.thirdPersonVehicleCameras") {
        commandVarsThirdPersonVehicleCameras();
    } else if (command == "vars.teamKillCountForKick") {
        commandVarsTeamKillCountForKick();
    } else if (command == "vars.teamKillValueForKick") {
        commandVarsTeamKillValueForKick();
    } else if (command == "vars.teamKillValueIncrease") {
        commandVarsTeamKillValueIncrease();
    } else if (command == "vars.teamKillValueDecreasePerSecond") {
        commandVarsTeamKillValueDecreasePerSecond();
    } else if (command == "vars.idleTimeout") {
        commandVarsIdleTimeout();
    } else if (command == "vars.profanityFilter") {
        commandVarsProfanityFilter();
    } else if (command == "levelVars.set") {
        commandLevelVarsSet();
    } else if (command == "levelVars.get") {
        commandLevelVarsGet();
    } else if (command == "levelVars.evaluate") {
        commandLevelVarsEvaluate();
    } else if (command == "levelVars.clear") {
        commandLevelVarsClear();
    } else if (command == "levelVars.list") {
        commandLevelVarsList();
    } else if (command == "player.onJoin") {
        eventPlayerOnJoin();
    } else if (command == "player.onAuthenticated") {
        eventPlayerOnAuthenticated();
    } else if (command == "player.onLeave") {
        eventPlayerOnLeave();
    } else if (command == "player.onSpawn") {
        eventPlayerOnSpawn();
    } else if (command == "player.onChar") {
        eventPlayerOnChat();
    } else if (command == "player.onKicked") {
        eventPlayerOnKicked();
    } else if (command == "player.onSquadChange") {
        eventPlayerOnSquadChange();
    } else if (command == "player.onTeamChange") {
        eventPlayerOnTeamChange();
    } else if (command == "punkBuster.onMessage") {
        eventPunkBusterOnMessage();
    } else if (command == "server.onLoadingLevel") {
        eventServerOnLoadingLevel();
    } else if (command == "server.onLevelStarted") {
        eventServerOnLevelStarted();
    } else if (command == "server.onRoundOver") {
        eventServerOnRoundOver();
    } else if (command == "server.onRoundOverPlayers") {
        eventServerOnRoundOverPlayers();
    } else if (command == "server.onTeamScores") {
        eventServerOnRoundOverTeamScores();
    }
}

ORBFBC2Commands::~ORBFBC2Commands()
{

}

// Events
void ORBFBC2Commands::eventPlayerOnJoin()
{

}

void ORBFBC2Commands::eventPlayerOnAuthenticated()
{

}

void ORBFBC2Commands::eventPlayerOnLeave()
{

}

void ORBFBC2Commands::eventPlayerOnSpawn()
{

}


void ORBFBC2Commands::eventPlayerOnChat()
{

}

void ORBFBC2Commands::eventPlayerOnKicked()
{

}

void ORBFBC2Commands::eventPlayerOnSquadChange()
{

}

void ORBFBC2Commands::eventPlayerOnTeamChange()
{

}

void ORBFBC2Commands::eventPunkBusterOnMessage()
{

}

void ORBFBC2Commands::eventServerOnLoadingLevel()
{

}

void ORBFBC2Commands::eventServerOnLevelStarted()
{

}

void ORBFBC2Commands::eventServerOnRoundOver()
{

}

void ORBFBC2Commands::eventServerOnRoundOverPlayers()
{

}

void ORBFBC2Commands::eventServerOnRoundOverTeamScores()
{

}

// Commands
void ORBFBC2Commands::commandLoginPlainText()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK") {
        //emit(signalLogMessage("info", tr("You have successfully logged in.")));
        //emit(signalAuthenticated();
    } else if (response == "InvalidPassword") {
        //emit(signalLogMessage("error", tr("Invalid password.")));
    } else if (response == "PasswordNotSet") {
        //emit(signalLogMessage("error", tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        //emit(signalLogMessage("error", tr("Invalid arguments.")));
    }
}

void ORBFBC2Commands::commandLoginHashed()
{
    QString response(mPacket.getWord(0).getContent());

    if (mLastSentPacket.getWordCount() == 1) {
        if (response == "OK" && mPacket.getWordCount() == 2) {
            //emit(signalLogMessage("info", QString(tr("We got salt: %1")).arg(mPacket.getWord(1).getContent()));
            QByteArray loginSalt = QByteArray::fromHex(QByteArray(mPacket.getWord(1).getContent()));
            //emit(signalGotSalt(loginSalt);
        }
    } else if (mLastSentPacket.getWordCount() == 2) {
        QString response(mPacket.getWord(0).getContent());
        if (response == "OK") {
            //emit(signalLogMessage("info", tr("You have successfully logged in."));
            //emit(signalAuthenticated();
        } else if (response == "InvalidPasswordHash") {
            //emit(signalLogMessage("error", tr("Invalid password."));
        }
    }

    if (response == "PasswordNotSet") {
        //emit(signalLogMessage("error", tr("Password not set."));
    } else if (response == "InvalidArguments") {
        //emit(signalLogMessage("error", tr("Invalid arguments."));
    }
}

void ORBFBC2Commands::commandLogout()
{

}

void ORBFBC2Commands::commandQuit()
{

}

void ORBFBC2Commands::commandVersion()
{
    QStringList packetList;

    for (quint32 i = 0; i < mPacket.getWordCount(); i++) {
        packetList << mPacket.getWord(i).getContent();
    }

    emit(signalCommandVersion(packetList));

    /*

    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 0) {
        QString version;
        QString versionNumber = mPacket.getWord(2).getContent();

        QMap<QString, QString> versionMap;
        versionMap.insert("571287", "R21");
        versionMap.insert("581637", "R22");
        versionMap.insert("584642", "R23");
        versionMap.insert("593485", "R24");
        versionMap.insert("602833", "R25");
        versionMap.insert("609063", "R26");
        versionMap.insert("617877", "R27");
        versionMap.insert("621775", "R28");
        versionMap.insert("638140", "R30");

        if (versionMap.contains(versionNumber)) {
            version = versionMap[versionNumber];
        } else {
            version = versionNumber;
        }

        //emit(signalLogMessage("info", QString("<b>%1</b> server version: <b>%2</b>.").arg(mPacket.getWord(1).getContent(), version));
    } else if (response == "InvalidArguments") {
        //emit(signalLogMessage("error", tr("Invalid arguments."));
    }
    */
}

void ORBFBC2Commands::commandListPlayers()
{

}

void ORBFBC2Commands::commandEventsEnabled()
{

}

void ORBFBC2Commands::commandHelp()
{

}

void ORBFBC2Commands::commandAdminRunScript()
{

}

void ORBFBC2Commands::commandPunkBusterPbSvCommand()
{

}
void ORBFBC2Commands::commandServerInfo()
{

}
void ORBFBC2Commands::commandAdminYell()
{

}
void ORBFBC2Commands::commandAdminSay()
{

}
void ORBFBC2Commands::commandAdminRunNextRound()
{

}
void ORBFBC2Commands::commandAdminRestartRound()
{

}

void ORBFBC2Commands::commandAdminEndRound()
{

}

void ORBFBC2Commands::commandAdminRunNextLevel()
{

}

void ORBFBC2Commands::commandAdminRestartMap()
{

}

void ORBFBC2Commands::commandAdminCurrentLevel()
{

}

void ORBFBC2Commands::commandMaplistNextLevelIndex()
{

}

void ORBFBC2Commands::commandAdminSupportedMaps()
{

}

void ORBFBC2Commands::commandAdminSetPlaylist()
{

}

void ORBFBC2Commands::commandAdminGetPlaylist()
{

}

void ORBFBC2Commands::commandAdminGetPlaylists()
{

}

void ORBFBC2Commands::commandAdminKickPlayer()
{

}

void ORBFBC2Commands::commandAdminListPlayers()
{

}

void ORBFBC2Commands::commandAdminMovePlayer()
{

}

void ORBFBC2Commands::commandAdminKillPlayer()
{

}

void ORBFBC2Commands::commandVarsTextChatModerationMode()
{

}

void ORBFBC2Commands::commandVarsTextChatSpamTriggerCount()
{

}

void ORBFBC2Commands::commandVarsTextChatSpamDetectionTime()
{

}

void ORBFBC2Commands::commandVarsTextChatSpamCoolDownTime()
{

}

void ORBFBC2Commands::commandTextCharModerationListLoad()
{

}

void ORBFBC2Commands::commandTextCharModerationListSave()
{

}

void ORBFBC2Commands::commandTextCharModerationListAdd()
{

}

void ORBFBC2Commands::commandTextCharModerationListRemove()
{

}

void ORBFBC2Commands::commandTextCharModerationListClear()
{

}

void ORBFBC2Commands::commandTextCharModerationListList()
{

}

void ORBFBC2Commands::commandBanListLoad()
{

}

void ORBFBC2Commands::commandBanListSave()
{

}

void ORBFBC2Commands::commandBanListAdd()
{

}

void ORBFBC2Commands::commandBanListRemove()
{

}

void ORBFBC2Commands::commandBanListClear()
{

}

void ORBFBC2Commands::commandBanListList()
{

}

void ORBFBC2Commands::commandReservedSlotsLoad()
{

}

void ORBFBC2Commands::commandReservedSlotsSave()
{

}

void ORBFBC2Commands::commandReservedSlotsAddPlayer()
{

}

void ORBFBC2Commands::commandReservedSlotsRemovePlayer()
{

}

void ORBFBC2Commands::commandReservedSlotsClear()
{

}

void ORBFBC2Commands::commandReservedSlotsList()
{

}

void ORBFBC2Commands::commandMapListLoad()
{

}

void ORBFBC2Commands::commandMapListSave()
{

}

void ORBFBC2Commands::commandMapListList()
{

}

void ORBFBC2Commands::commandMapListClear()
{

}

void ORBFBC2Commands::commandMapListRemove()
{

}

void ORBFBC2Commands::commandMapListAppend()
{

}

void ORBFBC2Commands::commandMapListInsert()
{

}

void ORBFBC2Commands::commandVarsServerName()
{

}

void ORBFBC2Commands::commandVarsAdminPassword()
{

}

void ORBFBC2Commands::commandVarsGamePassword()
{

}

void ORBFBC2Commands::commandVarsPunkBuster()
{

}

void ORBFBC2Commands::commandVarsRanked()
{

}

void ORBFBC2Commands::commandVarsRankLimit()
{

}

void ORBFBC2Commands::commandVarsTeamBalance()
{

}

void ORBFBC2Commands::commandVarsFriendlyFire()
{

}

void ORBFBC2Commands::commandVarsCurrentPlayerLimit()
{

}

void ORBFBC2Commands::commandVarsMaxPlayerLimit()
{

}

void ORBFBC2Commands::commandVarsPlayerLimit()
{

}

void ORBFBC2Commands::commandVarsBannerUrl()
{

}

void ORBFBC2Commands::commandVarsServerDescription()
{

}

void ORBFBC2Commands::commandVarsKillCam()
{

}

void ORBFBC2Commands::commandVarsMiniMap()
{

}

void ORBFBC2Commands::commandVarsCrossHair()
{

}

void ORBFBC2Commands::commandVars3dSpotting()
{

}

void ORBFBC2Commands::commandVarsMiniMapSpotting()
{

}

void ORBFBC2Commands::commandVarsThirdPersonVehicleCameras()
{

}

void ORBFBC2Commands::commandVarsTeamKillCountForKick()
{

}

void ORBFBC2Commands::commandVarsTeamKillValueForKick()
{

}

void ORBFBC2Commands::commandVarsTeamKillValueIncrease()
{

}

void ORBFBC2Commands::commandVarsTeamKillValueDecreasePerSecond()
{

}

void ORBFBC2Commands::commandVarsIdleTimeout()
{

}

void ORBFBC2Commands::commandVarsProfanityFilter()
{

}

void ORBFBC2Commands::commandLevelVarsSet()
{

}

void ORBFBC2Commands::commandLevelVarsGet()
{

}

void ORBFBC2Commands::commandLevelVarsEvaluate()
{

}

void ORBFBC2Commands::commandLevelVarsClear()
{

}

void ORBFBC2Commands::commandLevelVarsList()
{

}
