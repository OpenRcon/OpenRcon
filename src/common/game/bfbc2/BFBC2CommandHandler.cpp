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
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BFBC2CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) :
    FrostbiteCommandHandler(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

bool BFBC2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BFBC2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */
        /*{ "player.onAuthenticated",                 &FrostbiteCommandHandler::parsePlayerAuthenticatedEvent },*/
        /*{ "player.onJoin",                          &FrostbiteCommandHandler::parsePlayerJoinEvent },*/
        /*{ "player.onLeave",                         &FrostbiteCommandHandler::parsePlayerLeaveEvent },*/
        /*{ "player.onSpawn",                         &FrostbiteCommandHandler::parsePlayerSpawnEvent },*/
        /*{ "player.onKill",                          &FrostbiteCommandHandler::parsePlayerKillEvent },*/
        /*{ "player.onChat",                          &FrostbiteCommandHandler::parsePlayerChatEvent },*/
        { "player.onKicked",                        &BFBC2CommandHandler::parsePlayerKickedEvent },
        /*{ "player.onSquadChange",                   &FrostbiteCommandHandler::parsePlayerSquadChangeEvent },*/
        /*{ "player.onTeamChange",                    &FrostbiteCommandHandler::parsePlayerTeamChangeEvent },*/
        /*{ "punkBuster.onMessage",                   &FrostbiteCommandHandler::parsePunkBusterMessageEvent },*/
        { "punkBuster.onVersion",                   &BFBC2CommandHandler::parsePunkBusterVersionEvent },
        { "server.onLoadingLevel",                  &BFBC2CommandHandler::parseServerLoadingLevelEvent },
        { "server.onLevelStarted",                  &BFBC2CommandHandler::parseServerLevelStartedEvent },
        /*{ "server.onRoundOver",                     &FrostbiteCommandHandler::parseServerRoundOverEvent },*/
        /*{ "server.onRoundOverPlayers",              &FrostbiteCommandHandler::parseServerRoundOverPlayersEvent },*/
        /*{ "server.onRoundOverTeamScores",           &FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent },*/

        /* Commands */
        // Misc
        /*{ "login.plainText",                        &FrostbiteCommandHandler::parseLoginPlainTextCommand },*/
        /*{ "login.hashed",                           &FrostbiteCommandHandler::parseLoginHashedCommand },*/
        /*{ "serverInfo",                             &FrostbiteCommandHandler::parseServerInfoCommand },*/
        /*{ "logout",                                 &FrostbiteCommandHandler::parseLogoutCommand },*/
        /*{ "quit",                                   &FrostbiteCommandHandler::parseQuitCommand },*/
        /*{ "version",                                &FrostbiteCommandHandler::parseVersionCommand },*/
        /*{ "listPlayers",                            &FrostbiteCommandHandler::parseListPlayersCommand },*/

        /// BFBC2 Only.
        //eventsEnabled
        //help

        // Admin
        /*{ "admin.kickPlayer",                       &FrostbiteCommandHandler::parseAdminKickPlayerCommand },*/
        /*{ "admin.killPlayer",                       &FrostbiteCommandHandler::parseAdminKillPlayerCommand },*/
        /*{ "admin.listPlayers",                      &FrostbiteCommandHandler::parseAdminListPlayersCommand },*/
        /*{ "admin.movePlayer",                       &FrostbiteCommandHandler::parseAdminMovePlayerCommand },*/
        /*{ "admin.say",                              &FrostbiteCommandHandler::parseAdminSayCommand },*/
        /*{ "admin.yell",                             &FrostbiteCommandHandler::parseAdminYellCommand },*/

        /// BFBC2 Only.
        //admin.runscript <filename>
        //admin.runNextRound
        //admin.restartRound
        //admin.endRound <teamID>
        //admin.currentLevel
        //admin.supportedMaps <play list>
        //admin.setPlaylist <name>
        //admin.getPlaylist
        //admin.getPlaylists

        // Banning
        /*{ "banList.add",                            &FrostbiteCommandHandler::parseBanListAddCommand },*/
        /*{ "banList.clear",                          &FrostbiteCommandHandler::parseBanListClearCommand },*/
        /*{ "banList.list",                           &FrostbiteCommandHandler::parseBanListListCommand },*/
        /*{ "banList.load",                           &FrostbiteCommandHandler::parseBanListLoadCommand },*/
        /*{ "banList.remove",                         &FrostbiteCommandHandler::parseBanListRemoveCommand },*/
        /*{ "banList.save",                           &FrostbiteCommandHandler::parseBanListSaveCommand },*/

        // Maplist
        /*{ "mapList.clear",                          &FrostbiteCommandHandler::parseMapListClearCommand },*/
        /*{ "mapList.list",                           &FrostbiteCommandHandler::parseMapListListCommand },*/
        /*{ "mapList.load",                           &FrostbiteCommandHandler::parseMapListLoadCommand },*/
        /*{ "mapList.remove",                         &FrostbiteCommandHandler::parseMapListRemoveCommand },*/
        /*{ "mapList.save",                           &FrostbiteCommandHandler::parseMapListSaveCommand },*/

        /// BFBC2 Only.
        //mapList.append <name, rounds>
        //mapList.insert <index, name, rounds>
        //mapList.nextLevelIndex [index: integer]

        // Punkbuster
        /*{ "punkBuster.pb_sv_command",               &FrostbiteCommandHandler::parsePunkBusterPbSvCommand },*/

        // Reserved Slots
        /// BFBC2 Only.
        //reservedSlots.load
        //reservedSlots.save
        //reservedSlots.addPlayer <name>
        //reservedSlots.removePlayer <name>
        //reservedSlots.clear
        //reservedSlots.list

        // Variables
        /*{ "vars.3dSpotting",                        &FrostbiteCommandHandler::parseVars3dSpottingCommand },*/
        /*{ "vars.friendlyFire",                      &FrostbiteCommandHandler::parseVarsFriendlyFireCommand },*/
        /*{ "vars.gamePassword",                      &FrostbiteCommandHandler::parseVarsGamePasswordCommand },*/
        /*{ "vars.idleTimeout",                       &FrostbiteCommandHandler::parseVarsIdleTimeoutCommand },*/
        /*{ "vars.killCam",                           &FrostbiteCommandHandler::parseVarsKillCamCommand },*/
        /*{ "vars.miniMap",                           &FrostbiteCommandHandler::parseVarsMiniMapCommand },*/
        /*{ "vars.miniMapSpotting",                   &FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand },*/
        /*{ "vars.serverDescription",                 &FrostbiteCommandHandler::parseVarsServerDescriptionCommand },*/
        /*{ "vars.serverName",                        &FrostbiteCommandHandler::parseVarsServerNameCommand },*/
        /*{ "vars.teamKillCountForKick",              &FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand },*/
        /*{ "vars.teamKillValueDecreasePerSecond",    &FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },*/
        /*{ "vars.teamKillValueForKick",              &FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand },*/
        /*{ "vars.teamKillValueIncrease",             &FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand }*/

        /// BFBC2 Only.
        //vars.adminPassword [password]
        //vars.punkBuster [enabled]
        //vars.hardCore
        //vars.ranked
        //vars.rankLimit [rank]
        //vars.teamBalance [enabled]
        //vars.currentPlayerLimit
        //vars.maxPlayerLimit
        //vars.playerLimit [nr of players]
        //vars.bannerUrl [url]
        //vars.crossHair [enabled]
        //vars.thirdPersonVehicleCameras [enabled]
        //vars.profanityFilter [enabled]
        //vars.textChatModerationMode [moderation mode]
        //vars.textChatSpamTriggerCount [count]
        //vars.textChatSpamDetectionTime [time]
        //vars.textChatSpamCoolDownTime [time]

        // Text Chat Moderation
        //textChatModerationList.load
        //textChatModerationList.save
        //textChatModerationList.add <moderationlevel> <name>
        //textChatModerationList.remove <name>
        //textChatModerationList.clear
        //textChatModerationList.list [startOffset]

        // Level Variables
        //levelVars.set <context> <var name> <value>
        //levelVars.get <context> <var name>
        //levelVars.evaluate <var name>
        //levelVars.clear <context> [var name]
        //levelVars.list <context> [var name]
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return FrostbiteCommandHandler::parse(request, packet, lastSentPacket);
}

/* Send commands */
// Misc
void BFBC2CommandHandler::sendEventsEnabledCommand()
{
    connection->sendCommand("eventsEnabled");
}

void BFBC2CommandHandler::sendEventsEnabledCommand(bool enabled)
{
    connection->sendCommand(QString("\"eventsEnabled\" \"%1\"").arg(enabled));
}

void BFBC2CommandHandler::sendHelpCommand()
{
    connection->sendCommand("help");
}

// Admin

// Banning

// Maplist

// Punkbuster

// Reserved Slots

// Variables

/* Parse events */
void BFBC2CommandHandler::parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit(onPlayerKickedEvent(player, reason));
}

void BFBC2CommandHandler::parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString version = packet.getWord(1).getContent();

    emit(onPunkBusterVersionEvent(version));
}

void BFBC2CommandHandler::parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int roundsTotal = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit(onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2CommandHandler::parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    emit(onServerLevelStartedEvent());
}

/* Parse commands */
// Misc

// Admin

// Banning

// Maplist

// Punkbuster

// Reserved Slots

// Variables
