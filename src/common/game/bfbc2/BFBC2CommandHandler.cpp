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
        { "player.onKicked",                        &BFBC2CommandHandler::parsePlayerKickedEvent },
        { "punkBuster.onVersion",                   &BFBC2CommandHandler::parsePunkBusterVersionEvent },
        { "server.onLoadingLevel",                  &BFBC2CommandHandler::parseServerLoadingLevelEvent },
        { "server.onLevelStarted",                  &BFBC2CommandHandler::parseServerLevelStartedEvent },

        /* Commands */
        /*{ "eventsEnabled",                        &FrostbiteCommandHandler::parseEventsEnabledCommand },*/
        /*{ "help",                                 &FrostbiteCommandHandler::parseHelpCommand },*/

        // Admin
        //admin.runscript <filename>
        /*{ "admin.runNextRound",                   &FrostbiteCommandHandler::parseAdminRunNextRoundCommand },*/
        /*{ "admin.restartRound",                   &FrostbiteCommandHandler::parseAdminRestartRoundCommand },*/
        /*{ "admin.endRound",                       &BFBC2CommandHandler::parseAdminEndRoundCommand },*/
        /*{ "admin.currentLevel",                   &FrostbiteCommandHandler::parseAdminCurrentLevelCommand },*/
        /*{ "admin.supportedMaps",                  &BFBC2CommandHandler::parseAdminSupportedMapsCommand },*/
        /*{ "admin.setPlaylist",                    &BFBC2CommandHandler::parseAdminSetPlaylistCommand },*/
        /*{ "admin.getPlaylist",                    &BFBC2CommandHandler::parseAdminGetPlaylistCommand },*/
        /*{ "admin.getPlaylists",                   &BFBC2CommandHandler::parseAdminGetPlaylistsCommand },*/

        // Maplist
        /*{ "mapList.append",                       &BFBC2CommandHandler::parseMapListAppendCommand },*/
        /*{ "mapList.insert",                       &BFBC2CommandHandler::parseMapListInsertCommand },*/
        /*{ "mapList.nextLevelIndex",               &BFBC2CommandHandler::parseMapListNextLevelIndexCommand },*/

        // Reserved Slots
        /*{ "reservedSlots.load",                   &BFBC2CommandHandler::parseReservedSlotsLoadCommand },*/
        /*{ "reservedSlots.save",                   &BFBC2CommandHandler::parseReservedSlotsSaveCommand },*/
        /*{ "reservedSlots.addPlayer",              &BFBC2CommandHandler::parseReservedSlotsAddPlayerCommand },*/
        /*{ "reservedSlots.removePlayer",           &BFBC2CommandHandler::parseReservedSlotsRemovePlayerCommand },*/
        /*{ "reservedSlots.clear",                  &BFBC2CommandHandler::parseReservedSlotsClearCommand },*/
        /*{ "reservedSlots.list",                   &BFBC2CommandHandler::parseReservedSlotsListCommand },*/

        // Variables
        /*{ "vars.adminPassword",                   &BFBC2CommandHandler::parseVarsAdminPasswordCommand },*/
        /*{ "vars.punkBuster",                      &BFBC2CommandHandler::parseVarsPunkBusterCommand },*/
        /*{ "vars.hardCore",                        &BFBC2CommandHandler::parseVarsHardCoreCommand },*/
        /*{ "vars.ranked",                          &BFBC2CommandHandler::parseVarsRankedCommand },*/
        /*{ "vars.rankLimit",                       &BFBC2CommandHandler::parseVarsRankLimitCommand },*/
        /*{ "vars.teamBalance",                     &BFBC2CommandHandler::parseVarsTeamBalanceCommand },*/
        /*{ "vars.currentPlayerLimit",              &BFBC2CommandHandler::parseVarsCurrentPlayerLimitCommand },*/
        /*{ "vars.maxPlayerLimit",                  &BFBC2CommandHandler::parseVarsMaxPlayerLimitCommand },*/
        /*{ "vars.playerLimit",                     &BFBC2CommandHandler::parseVarsPlayerLimitCommand },*/
        /*{ "vars.bannerUrl",                       &BFBC2CommandHandler::parseVarsBannerUrlCommand },*/
        /*{ "vars.crossHair",                       &BFBC2CommandHandler::parseVarsCrossHairCommand },*/
        /*{ "vars.thirdPersonVehicleCameras",       &BFBC2CommandHandler::parseVarsThirdPersonVehicleCamerasCommand },*/
        /*{ "vars.profanityFilter",                 &BFBC2CommandHandler::parseVarsProfanityFilterCommand },*/
        /*{ "vars.textChatModerationMode",          &BFBC2CommandHandler::parseVarsTextChatModerationModeCommand },*/
        /*{ "vars.textChatSpamTriggerCount",        &BFBC2CommandHandler::parseVarsTextChatSpamTriggerCountCommand },*/
        /*{ "vars.textChatSpamDetectionTime",       &BFBC2CommandHandler::parseVarsTextChatSpamDetectionTimeCommand },*/
        /*{ "vars.textChatSpamCoolDownTime",        &BFBC2CommandHandler::parseVarsTextChatSpamCoolDownTimeCommand },*/

        // Text Chat Moderation
        /*{ "textChatModerationList.load",          &BFBC2CommandHandler::parseTextChatModerationListLoadCommand },*/
        /*{ "textChatModerationList.save",          &BFBC2CommandHandler::parseTextChatModerationListSaveCommand },*/
        /*{ "textChatModerationList.add",           &BFBC2CommandHandler::parseTextChatModerationListAddCommand },*/
        /*{ "textChatModerationList.remove",        &BFBC2CommandHandler::parseTextChatModerationListRemoveCommand },*/
        /*{ "textChatModerationList.clear",         &BFBC2CommandHandler::parseTextChatModerationListClearCommand },*/
        /*{ "textChatModerationList.list",          &BFBC2CommandHandler::parseTextChatModerationListListCommand },*/

        // Level Variables
        /*{ "levelVars.set",                        &BFBC2CommandHandler::parseLevelVarsSetCommand },*/
        /*{ "levelVars.get",                        &BFBC2CommandHandler::parseLevelVarsGetCommand },*/
        /*{ "levelVars.evaluate",                   &BFBC2CommandHandler::parseLevelVarsEvaluateCommand },*/
        /*{ "levelVars.clear",                      &BFBC2CommandHandler::parseLevelVarsClearCommand },*/
        /*{ "levelVars.list",                       &BFBC2CommandHandler::parseLevelVarsListCommand },*/
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
void BFBC2CommandHandler::sendHelpCommand()
{
    connection->sendCommand("help");
}

// Admin

// Maplist

// Reserved Slots

// Variables

/* Parse events */
void BFBC2CommandHandler::parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() >= 1) {
        QString player = packet.getWord(1).getContent();
        QString reason = packet.getWord(2).getContent();

        emit (onPlayerKickedEvent(player, reason));
    }
}

void BFBC2CommandHandler::parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() >= 1) {
        QString version = packet.getWord(1).getContent();

        emit (onPunkBusterVersionEvent(version));
    }
}

void BFBC2CommandHandler::parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() >= 1) {
        QString levelName = packet.getWord(1).getContent();
        int roundsPlayed = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int roundsTotal = FrostbiteUtils::toInt(packet.getWord(3).getContent());

        emit (onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
    }
}

void BFBC2CommandHandler::parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() >= 1) {
        emit (onServerLevelStartedEvent());
    }
}

/* Parse commands */
// Misc

// Admin

// Maplist

// Reserved Slots

// Variables
