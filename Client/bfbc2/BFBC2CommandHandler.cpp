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

#include "FrostbiteConnection.h"
#include "BFBC2CommandHandler.h"

BFBC2CommandHandler::BFBC2CommandHandler(FrostbiteConnection *parent) : FrostbiteCommandHandler(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

bool BFBC2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BFBC2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "player.onJoin",                       &BFBC2CommandHandler::parsePlayerJoinEvent },
        { "player.onAuthenticated",              &BFBC2CommandHandler::parsePlayerAuthenticatedEvent },
        { "player.onLeave",                      &BFBC2CommandHandler::parsePlayerLeaveEvent },
        { "player.onSpawn",                      &BFBC2CommandHandler::parsePlayerSpawnEvent },
        { "player.onKill",                       &BFBC2CommandHandler::parsePlayerKillEvent },
        { "player.onChat",                       &BFBC2CommandHandler::parsePlayerChatEvent },
        { "player.onKicked",                     &BFBC2CommandHandler::parsePlayerKickedEvent },
        { "player.onSquadChange",                &BFBC2CommandHandler::parsePlayerSquadChangeEvent },
        { "player.onTeamChange",                 &BFBC2CommandHandler::parsePlayerTeamChangeEvent },
        { "punkBuster.onMessage",                &BFBC2CommandHandler::parsePunkBusterMessageEvent },
        { "punkBuster.onVersion",                &BFBC2CommandHandler::parsePunkBusterVersionEvent },
        { "server.onLoadingLevel",               &BFBC2CommandHandler::parseServerLoadingLevelEvent },
        { "server.onLevelStarted",               &BFBC2CommandHandler::parseServerLevelStartedEvent },
        { "server.onRoundOver",                  &BFBC2CommandHandler::parseServerRoundOverEvent },
        { "server.onRoundOverPlayers",           &BFBC2CommandHandler::parseServerRoundOverPlayersEvent },
        { "server.onRoundOverTeamScores",        &BFBC2CommandHandler::parseServerRoundOverTeamScoresEvent },

        /* Commands */
        // Misc
        { "listPlayers",                         &BFBC2CommandHandler::parseListPlayersCommand },
        { "eventsEnabled",                       nullptr /*&BFBC2CommandHandler::parseEventsEnabledCommand*/ },
        { "help",                                &BFBC2CommandHandler::parseHelpCommand },
        { "punkBuster.pb_sv_command",            nullptr /*&BFBC2CommandHandler::parsePunkBusterPbSvCommand*/ },
        { "serverInfo",                          &BFBC2CommandHandler::parseServerInfoCommand },

        // Admin
        { "admin.runscript",                     nullptr /*&BFBC2CommandHandler::parseAdminRunScriptCommand*/ },
        { "admin.yell",                          nullptr /*&BFBC2CommandHandler::parseAdminYellCommand*/ },
        { "admin.say",                           nullptr /*&BFBC2CommandHandler::parseAdminSayCommand*/ },
        { "admin.runNextRound",                  nullptr /*&BFBC2CommandHandler::parseAdminRunNextRoundCommand*/ },
        { "admin.restartRound",                  nullptr /*&BFBC2CommandHandler::parseAdminRestartRoundCommand*/ },
        { "admin.endRound",                      nullptr /*&BFBC2CommandHandler::parseAdminEndRoundCommand*/ },
        { "admin.runNextLevel",                  nullptr /*&BFBC2CommandHandler::parseAdminRunNextLevelCommand*/ },
        { "admin.restartMap",                    nullptr /*&BFBC2CommandHandler::parseAdminRestartMapCommand*/ },
        { "admin.currentLevel",                  nullptr /*&BFBC2CommandHandler::parseAdminCurrentLevelCommand*/ },
        { "admin.supportedMaps",                 nullptr /*&BFBC2CommandHandler::parseAdminSupportedMapsCommand*/ },
        { "admin.setPlaylist",                   nullptr /*&BFBC2CommandHandler::parseAdminSetPlaylistCommand*/ },
        { "admin.getPlaylist",                   nullptr /*&BFBC2CommandHandler::parseAdminGetPlaylistCommand*/ },
        { "admin.getPlaylists",                  nullptr /*&BFBC2CommandHandler::parseAdminGetPlaylistsCommand*/ },
        { "admin.kickPlayer",                    nullptr /*&BFBC2CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.listPlayers",                   &BFBC2CommandHandler::parseAdminListPlayersCommand },
        { "admin.movePlayer",                    nullptr /*&BFBC2CommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.killPlayer",                    nullptr /*&BFBC2CommandHandler::parseAdminKillPlayerCommand*/ },

        // TextChatModerationList
        { "textChatModerationList.load",         nullptr /*&BFBC2CommandHandler::parseTextChatModerationListLoadCommand*/ },
        { "textChatModerationList.save",         nullptr /*&BFBC2CommandHandler::parseTextChatModerationListSaveCommand*/ },
        { "textChatModerationList.add",          nullptr /*&BFBC2CommandHandler::parseTextChatModerationListAddCommand*/ },
        { "textChatModerationList.remove",       nullptr /*&BFBC2CommandHandler::parseTextChatModerationListRemoveCommand*/ },
        { "textChatModerationList.clear",        nullptr /*&BFBC2CommandHandler::parseTextChatModerationListClearCommand*/ },
        { "textChatModerationList.list",         nullptr /*&BFBC2CommandHandler::parseTextChatModerationListListCommand*/ },

        // BanList
        { "banList.load",                        nullptr /*&BFBC2CommandHandler::parseBanListLoadCommand*/ },
        { "banList.save",                        nullptr /*&BFBC2CommandHandler::parseBanListSaveCommand*/ },
        { "banList.add",                         nullptr /*&BFBC2CommandHandler::parseBanListAddCommand*/ },
        { "banList.remove",                      nullptr /*&BFBC2CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.clear",                       nullptr /*&BFBC2CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        &BFBC2CommandHandler::parseBanListListCommand },

        // Reserved Slots
        { "reservedSlots.load",                  nullptr /*&BFBC2CommandHandler::parseReservedSlotsLoadCommand*/ },
        { "reservedSlots.save",                  nullptr /*&BFBC2CommandHandler::parseReservedSlotsSaveCommand*/ },
        { "reservedSlots.addPlayer",             nullptr /*&BFBC2CommandHandler::parseReservedSlotsAddPlayerCommand*/ },
        { "reservedSlots.removePlayer",          nullptr /*&BFBC2CommandHandler::parseReservedSlotsRemovePlayerCommand*/ },
        { "reservedSlots.clear",                 nullptr /*&BFBC2CommandHandler::parseReservedSlotsClearCommand*/ },
        { "reservedSlots.list",                  &BFBC2CommandHandler::parseReservedSlotsListCommand },

        // MapList
        { "mapList.load",                        nullptr /*&BFBC2CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.save",                        nullptr /*&BFBC2CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.list",                        nullptr /*&BFBC2CommandHandler::parseMapListListCommand*/ },
        { "mapList.clear",                       nullptr /*&BFBC2CommandHandler::parseMapListClearCommand*/ },
        { "mapList.remove",                      nullptr /*&BFBC2CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.append",                      nullptr /*&BFBC2CommandHandler::parseMapListAppendCommand*/ },
        { "mapList.insert",                      nullptr /*&BFBC2CommandHandler::parseMaplistInsertCommand*/ },
        { "mapList.nextLevelIndex",              &BFBC2CommandHandler::parseMapListNextLevelIndexCommand },

        // Vars
        { "vars.textChatModerationMode",         &BFBC2CommandHandler::parseVarsTextChatModerationModeCommand },
        { "vars.textChatSpamTriggerCount",       &BFBC2CommandHandler::parseVarsTextChatSpamTriggerCountCommand },
        { "vars.textChatSpamDetectionTime",      &BFBC2CommandHandler::parseVarsTextChatSpamDetectionTimeCommand },
        { "vars.textChatSpamCoolDownTime",       &BFBC2CommandHandler::parseVarsTextChatSpamCoolDownTimeCommand },
        { "vars.serverName",                     &BFBC2CommandHandler::parseVarsServerNameCommand },
        { "vars.adminPassword",                  nullptr /*&BFBC2CommandHandler::parseVarsAdminPasswordCommand*/ },
        { "vars.gamePassword",                   nullptr /*&BFBC2CommandHandler::parseVarsGamePasswordCommand*/ },
        { "vars.punkBuster",                     nullptr /*&BFBC2CommandHandler::parseVarsPunkBusterCommand*/ },
        { "vars.hardCore",                       nullptr /*&BFBC2CommandHandler::parseVarsHardCoreCommand*/ },
        { "vars.ranked",                         nullptr /*&BFBC2CommandHandler::parseVarsRankedCommand*/ },
        { "vars.rankLimit",                      nullptr /*&BFBC2CommandHandler::parseVarsRankLimitCommand*/ },
        { "vars.teamBalance",                    nullptr /*&BFBC2CommandHandler::parseVarsTeamBalanceCommand*/ },
        { "vars.friendlyFire",                   nullptr /*&BFBC2CommandHandler::parseVarsFriendlyFireCommand*/ },
        { "vars.currentPlayerLimit",             nullptr /*&BFBC2CommandHandler::parseVarsCurrentPlayerLimitCommand*/ },
        { "vars.maxPlayerLimit",                 nullptr /*&BFBC2CommandHandler::parseVarsMaxPlayerLimitCommand*/ },
        { "vars.playerLimit",                    nullptr /*&BFBC2CommandHandler::parseVarsPlayerLimitCommand*/ },
        { "vars.bannerUrl",                      &BFBC2CommandHandler::parseVarsBannerUrlCommand },
        { "vars.serverDescription",              &BFBC2CommandHandler::parseVarsServerDescriptionCommand },
        { "vars.killCam",                        nullptr /*&BFBC2CommandHandler::parseVarsKillCamCommand*/ },
        { "vars.miniMap",                        nullptr /*&BFBC2CommandHandler::parseVarsMiniMapCommand*/ },
        { "vars.crossHair",                      nullptr /*&BFBC2CommandHandler::parseVarsCrossHairCommand*/ },
        { "vars.3dSpotting",                     nullptr /*&BFBC2CommandHandler::parseVars3dSpottingCommand*/ },
        { "vars.miniMapSpotting",                nullptr /*&BFBC2CommandHandler::parseVarsMiniMapSpottingCommand*/ },
        { "vars.thirdPersonVehicleCameras",      nullptr /*&BFBC2CommandHandler::parseVarsThirdPersonVehicleCamerasCommand*/ },
        { "vars.teamKillCountForKick",           nullptr /*&BFBC2CommandHandler::parseVarsTeamKillCountForKickCommand*/ },
        { "vars.teamKillValueForKick",           nullptr /*&BFBC2CommandHandler::parseVarsTeamKillValueForKickCommand*/ },
        { "vars.teamKillValueIncrease",          nullptr /*&BFBC2CommandHandler::parseVarsTeamKillValueIncreaseCommand*/ },
        { "vars.teamKillValueDecreasePerSecond", nullptr /*&BFBC2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand*/ },
        { "vars.idleTimeout",                    &BFBC2CommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.profanityFilter",                nullptr /*&BFBC2CommandHandler::parseVarsProfanityFilterCommand*/ },

        // LevelVars
        { "LevelVars.set",                       nullptr /*&BFBC2CommandHandler::parseLevelVarsSetCommand*/ },
        { "LevelVars.get",                       nullptr /*&BFBC2CommandHandler::parseLevelVarsGetCommand*/ },
        { "LevelVars.evaluate",                  nullptr /*&BFBC2CommandHandler::parseLevelVarsEvaluateCommand*/ },
        { "LevelVars.clear",                     nullptr /*&BFBC2CommandHandler::parseLevelVarsClearCommand*/ },
        { "LevelVars.list",                      nullptr /*&BFBC2CommandHandler::parseLevelVarsListCommand*/ },
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    } else {
        return FrostbiteCommandHandler::parse(request, packet, lastSentPacket);
    }
}

/* Events */
void BFBC2CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerJoinEvent(player));
}

void BFBC2CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerAuthenticatedEvent(player, guid));
}

void BFBC2CommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BFBC2CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit (onPlayerSpawnEvent(player, kit, weaponList));
}

void BFBC2CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = FrostbiteUtils::toBool(packet.getWord(4).getContent());

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BFBC2CommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BFBC2CommandHandler::parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit (onPlayerKickedEvent(player, reason));
}

void BFBC2CommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BFBC2CommandHandler::parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString version = packet.getWord(1).getContent();

    emit (onPunkBusterVersionEvent(version));
}

void BFBC2CommandHandler::parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = toInt(packet.getWord(2).getContent());
    int roundsTotal = toInt(packet.getWord(3).getContent());

    emit (onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2CommandHandler::parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    emit (onServerLevelStartedEvent());
}

void BFBC2CommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = toInt(packet.getWord(1).getContent());

    emit (onServerRoundOverEvent(winningTeamId));
}

void BFBC2CommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BFBC2CommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */

/* Misc */
void BFBC2CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Implement this.
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onListPlayersCommand());
    }
}

/*void BFBC2CommandHandler::parseEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList helpList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            helpList.append(packet.getWord(i).getContent());
        }

        emit (onHelpCommand(helpList));
    }
}

/*void BFBC2CommandHandler::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

/* Query */
void BFBC2CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList serverInfo;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            serverInfo.append(packet.getWord(i).getContent());
        }

        emit (onServerInfoCommand(serverInfo));
    }
}

// Admin commands.

/*void BFBC2CommandHandler::parseAdminRunScriptCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRestartMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        PlayerList playerList;
        unsigned int parameterCount = QString(packet.getWord(1).getContent()).toUInt();
        unsigned int playerCount = QString(packet.getWord(2 + parameterCount).getContent()).toUInt();

        for (unsigned int i = 0; i < playerCount; i++) {
            PlayerListItem player;

            for (unsigned int j = 0; j < parameterCount; j++) {
                player.insert(packet.getWord(2 + j).getContent(), packet.getWord(2 + parameterCount + 1 + i * parameterCount + j).getContent());
            }

            playerList.append(player);
        }

        emit (onAdminListPlayersCommand(playerList));
    }
}

/*void BFBC2CommandHandler::parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Text Chant Moderation List commands.

/*void BFBC2CommandHandler::parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Ban List commands.

/*void BFBC2CommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            banList.append(packet.getWord(i).getContent());
        }

        emit (onBanListListCommand(banList));
    }
}

// Reserved Slots commands.
/*void BFBC2CommandHandler::parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseReservedSlotsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList list;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListCommand(list));
    }
}

// Map List commands.

/*void BFBC2CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i = i + 2) {
                mapList << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }

            //emit(onMapListListRoundsCommand(mapList));
        } else {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i++) {
                mapList.append(packet.getWord(i).getContent());
            }

            emit (onMapListListCommand(mapList));
        }
    }

}

/*void BFBC2CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListAppendCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListInsertCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit (onMapListNextLevelIndexCommand(index));
    }
}

// Vars commands.

void BFBC2CommandHandler::parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit (onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2CommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

/*void BFBC2CommandHandler::parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsHardCoreCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsRankLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2CommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

/*void BFBC2CommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

void BFBC2CommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

/*void BFBC2CommandHandler::parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/

// Level Vars commands.
/*void BFBC2CommandHandler::parseLevelVarsSetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsGetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
}*/
