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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCryptographicHash>

#include "Frostbite2CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "BF3CommandHandler.h"
#include "BF4CommandHandler.h"
#include "PlayerSubset.h"
#include "TeamScores.h"
#include "BF3ServerInfo.h"
#include "BF4ServerInfo.h"
#include "BF4PlayerEntry.h"

Frostbite2CommandHandler::Frostbite2CommandHandler(QObject *parent) :
    FrostbiteCommandHandler(parent)
{

}

Frostbite2CommandHandler::~Frostbite2CommandHandler()
{

}

bool Frostbite2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (Frostbite2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */
        /*{ "player.onAuthenticated",               &FrostbiteCommandHandler::parsePlayerAuthenticatedEvent },*/
        /*{ "player.onJoin",                        &FrostbiteCommandHandler::parsePlayerJoinEvent },*/
        /*{ "player.onLeave",                       &FrostbiteCommandHandler::parsePlayerLeaveEvent },*/
        /*{ "player.onSpawn",                       &FrostbiteCommandHandler::parsePlayerSpawnEvent },*/
        /*{ "player.onKill",                        &FrostbiteCommandHandler::parsePlayerKillEvent },*/
        /*{ "player.onChat",                        &FrostbiteCommandHandler::parsePlayerChatEvent },*/
        /*{ "player.onSquadChange",                 &FrostbiteCommandHandler::parsePlayerSquadChangeEvent },*/
        /*{ "player.onTeamChange",                  &FrostbiteCommandHandler::parsePlayerTeamChangeEvent },*/
        /*{ "punkBuster.onMessage",                 &FrostbiteCommandHandler::parsePunkBusterMessageEvent },*/
        { "server.onMaxPlayerCountChange",          &Frostbite2CommandHandler::parseServerMaxPlayerCountChangeEvent },
        { "server.onLevelLoaded",                   &Frostbite2CommandHandler::parseServerLevelLoadedEvent },
        /*{ "server.onRoundOver",                   &FrostbiteCommandHandler::parseServerRoundOverEvent },*/
        /*{ "server.onRoundOverPlayers",            &FrostbiteCommandHandler::parseServerRoundOverPlayersEvent },*/
        /*{ "server.onRoundOverTeamScores",         &FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent },*/

        /* Commands */
        // Misc
        /*{ "login.plainText",                      &FrostbiteCommandHandler::parseLoginPlainTextCommand },*/
        /*{ "login.hashed",                         &FrostbiteCommandHandler::parseLoginHashedCommand },*/
        /*{ "serverInfo",                           &FrostbiteCommandHandler::parseServerInfoCommand },*/
        /*{ "logout",                               &FrostbiteCommandHandler::parseLogoutCommand },*/
        /*{ "quit",                                 &FrostbiteCommandHandler::parseQuitCommand },*/
        /*{ "version",                              &FrostbiteCommandHandler::parseVersionCommand },*/
        /*{ "currentLevel",                         &FrostbiteCommandHandler::parseCurrentLevelCommand },*/
        /*{ "listPlayers",                          &FrostbiteCommandHandler::parseListPlayersCommand },*/

        // Admin
        { "admin.eventsEnabled",                    &Frostbite2CommandHandler::parseAdminEventsEnabledCommand },
        { "admin.help",                             &Frostbite2CommandHandler::parseAdminHelpCommand },
        /*{ "admin.kickPlayer",                     &FrostbiteCommandHandler::parseAdminKickPlayerCommand },*/
        /*{ "admin.killPlayer",                     &FrostbiteCommandHandler::parseAdminKillPlayerCommand },*/
        /*{ "admin.listPlayers",                    &FrostbiteCommandHandler::parseAdminListPlayersCommand },*/
        /*{ "admin.movePlayer",                     &FrostbiteCommandHandler::parseAdminMovePlayerCommand },*/
        { "admin.password",                         &Frostbite2CommandHandler::parseAdminPasswordCommand },
        /*{ "admin.say",                            &FrostbiteCommandHandler::parseAdminSayCommand },*/
        /*{ "admin.yell",                           &FrostbiteCommandHandler::parseAdminYellCommand },*/

        // Banning
        /*{ "banList.add",                          &FrostbiteCommandHandler::parseBanListAddCommand },*/
        /*{ "banList.clear",                        &FrostbiteCommandHandler::parseBanListClearCommand },*/
        /*{ "banList.list",                         &FrostbiteCommandHandler::parseBanListListCommand },*/
        /*{ "banList.load",                         &FrostbiteCommandHandler::parseBanListLoadCommand },*/
        /*{ "banList.remove",                       &FrostbiteCommandHandler::parseBanListRemoveCommand },*/
        /*{ "banList.save",                         &FrostbiteCommandHandler::parseBanListSaveCommand },*/

        // Maplist
        /*{ "mapList.add",                          &Frostbite2CommandHandler::parseMapListAddCommand },*/
        { "mapList.availableMaps",                  &Frostbite2CommandHandler::parseMapListAvailableMapsCommand },
        /*{ "mapList.clear",                        &FrostbiteCommandHandler::parseMapListClearCommand },*/
        /*{ "mapList.endRound",                     &Frostbite2CommandHandler::parseMapListEndRoundCommand },*/
        { "mapList.getMapIndices",                  &Frostbite2CommandHandler::parseMapListGetMapIndicesCommand },
        { "mapList.getRounds",                      &Frostbite2CommandHandler::parseMapListGetRoundsCommand },
        /*{ "mapList.list",                         &FrostbiteCommandHandler::parseMapListListCommand },*/
        /*{ "mapList.load",                         &FrostbiteCommandHandler::parseMapListLoadCommand },*/
        /*{ "mapList.remove",                       &FrostbiteCommandHandler::parseMapListRemoveCommand },*/
        /*{ "mapList.restartRound",                 &Frostbite2CommandHandler::parseMapListRestartRoundCommand },*/
        /*{ "mapList.runNextRound",                 &Frostbite2CommandHandler::parseMapListRunNextRoundCommand },*/
        /*{ "mapList.save",                         &FrostbiteCommandHandler::parseMapListSaveCommand },*/
        /*{ "mapList.setNextMapIndex",              &Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand },*/

        // Player
        { "player.idleDuration",                    &Frostbite2CommandHandler::parsePlayerIdleDurationCommand },
        { "player.isAlive",                         &Frostbite2CommandHandler::parsePlayerIsAliveCommand },
        { "player.ping",                            &Frostbite2CommandHandler::parsePlayerPingCommand },

        // Punkbuster
        /*{ "punkBuster.activate",                  &Frostbite2CommandHandler::parsePunkBusterActivateCommand },*/
        { "punkBuster.isActive",                    &Frostbite2CommandHandler::parsePunkBusterIsActiveCommand },
        /*{ "punkBuster.pb_sv_command",             &FrostbiteCommandHandler::parsePunkBusterPbSvCommand },*/

        // Reserved Slots
        /*{ "reservedSlotsList.add",                &Frostbite2CommandHandler::parseReservedSlotsListAddCommand },*/
        { "reservedSlotsList.aggressiveJoin",       &Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        /*{ "reservedSlotsList.clear",              &Frostbite2CommandHandler::parseReservedSlotsListClearCommand },*/
        { "reservedSlotsList.list",                 &Frostbite2CommandHandler::parseReservedSlotsListListCommand },
        /*{ "reservedSlotsList.load",               &Frostbite2CommandHandler::parseReservedSlotsListLoadCommand },*/
        /*{ "reservedSlotsList.remove",             &Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand },*/
        /*{ "reservedSlotsList.save",               &Frostbite2CommandHandler::parseReservedSlotsListSaveCommand },*/

        // Squad
        { "squad.leader",                           &Frostbite2CommandHandler::parseSquadLeaderCommand },
        /*{ "squad.listActive",                     &Frostbite2CommandHandler::parseSquadListActiveCommand },*/
        { "squad.listPlayers",                      &Frostbite2CommandHandler::parseSquadListPlayersCommand },
        { "squad.private",                          &Frostbite2CommandHandler::parseSquadPrivateCommand },

        // Variables
        /*{ "vars.3dSpotting",                      &FrostbiteCommandHandler::parseVars3dSpottingCommand },*/
        { "vars.3pCam",                             &Frostbite2CommandHandler::parseVars3pCamCommand },
        { "vars.autoBalance",                       &Frostbite2CommandHandler::parseVarsAutoBalanceCommand },
        { "vars.bulletDamage",                      &Frostbite2CommandHandler::parseVarsBulletDamageCommand },
        /*{ "vars.friendlyFire",                    &FrostbiteCommandHandler::parseVarsFriendlyFireCommand },*/
        { "vars.gameModeCounter",                   &Frostbite2CommandHandler::parseVarsGameModeCounterCommand },
        /*{ "vars.gamePassword",                    &FrostbiteCommandHandler::parseVarsGamePasswordCommand },*/
        { "vars.hud",                               &Frostbite2CommandHandler::parseVarsHudCommand },
        { "vars.idleBanRounds",                     &Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand },
        /*{ "vars.idleTimeout",                     &FrostbiteCommandHandler::parseVarsIdleTimeoutCommand },*/
        /*{ "vars.killCam",                         &FrostbiteCommandHandler::parseVarsKillCamCommand },*/
        { "vars.maxPlayers",                        &Frostbite2CommandHandler::parseVarsMaxPlayersCommand },
        /*{ "vars.miniMap",                         &FrostbiteCommandHandler::parseVarsMiniMapCommand },*/
        /*{ "vars.miniMapSpotting",                 &FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand },*/
        { "vars.nameTag",                           &Frostbite2CommandHandler::parseVarsNameTagCommand },
        { "vars.onlySquadLeaderSpawn",              &Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand },
        { "vars.playerRespawnTime",                 &Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand },
        { "vars.regenerateHealth",                  &Frostbite2CommandHandler::parseVarsRegenerateHealthCommand },
        { "vars.roundLockdownCountdown",            &Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand },
        { "vars.roundRestartPlayerCount",           &Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand },
        { "vars.roundStartPlayerCount",             &Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand },
        /*{ "vars.serverDescription",               &FrostbiteCommandHandler::parseVarsServerDescriptionCommand },*/
        { "vars.serverMessage",                     &Frostbite2CommandHandler::parseVarsServerMessageCommand },
        /*{ "vars.serverName",                      &FrostbiteCommandHandler::parseVarsServerNameCommand },*/
        { "vars.soldierHealth",                     &Frostbite2CommandHandler::parseVarsSoldierHealthCommand },
        /*{ "vars.teamKillCountForKick",            &FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand },*/
        { "vars.teamKillKickForBan",                &Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand },
        /*{ "vars.teamKillValueDecreasePerSecond",  &FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },*/
        /*{ "vars.teamKillValueForKick",            &FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand },*/
        /*{ "vars.teamKillValueIncrease",           &FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand },*/
        { "vars.unlockMode",                        &Frostbite2CommandHandler::parseVarsUnlockModeCommand },
        { "vars.vehicleSpawnAllowed",               &Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand },
        { "vars.vehicleSpawnDelay",                 &Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand },
        /*{ "vars.gunMasterWeaponsPreset",          &Frostbite2CommandHandler::parseGunMasterWeaponsPresetCommand }*/
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
// Admin
void Frostbite2CommandHandler::sendAdminEventsEnabledCommand()
{
    connection->sendCommand("admin.eventsEnabled");
}

void Frostbite2CommandHandler::sendAdminEventsEnabledCommand(bool enabled)
{
    connection->sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendAdminHelpCommand()
{
    connection->sendCommand("admin.help");
}

void Frostbite2CommandHandler::sendAdminPasswordCommand(const QString &password)
{
    QString command;

    if (password.isEmpty()) {
        command = "admin.password";
    } else {
        command = QString("\"admin.password\" \"%1\"").arg(password);
    }

    connection->sendCommand(command);
}

// Banning

// Maplist
void Frostbite2CommandHandler::sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet)
{
    connection->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListAvailableMapsCommand(const QString &filter)
{
    connection->sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void Frostbite2CommandHandler::sendMapListEndRoundCommand(int teamId)
{
    connection->sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendMapListGetMapIndicesCommand()
{
    connection->sendCommand("mapList.getMapIndices");
}

void Frostbite2CommandHandler::sendMapListGetRoundsCommand()
{
    connection->sendCommand("mapList.getRounds");
}

void Frostbite2CommandHandler::sendMapListRestartRoundCommand()
{
    connection->sendCommand("mapList.restartRound");
}

void Frostbite2CommandHandler::sendMapListRunNextRoundCommand()
{
    connection->sendCommand("mapList.runNextRound");
}

void Frostbite2CommandHandler::sendMapListSetNextMapIndexCommand(int index)
{
    connection->sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

// Player
void Frostbite2CommandHandler::sendPlayerIdleDurationCommand(const QString &player)
{
    connection->sendCommand(QString("\"player.idleDuration\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerIsAliveCommand(const QString &player)
{
    connection->sendCommand(QString("\"player.isAlive\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerPingCommand(const QString &player)
{
    connection->sendCommand(QString("\"player.ping\" \"%1\"").arg(player));
}

// Punkbuster
void Frostbite2CommandHandler::sendPunkBusterActivateCommand()
{
    connection->sendCommand("punkBuster.activate");
}

void Frostbite2CommandHandler::sendPunkBusterIsActiveCommand()
{
    connection->sendCommand("punkBuster.isActive");
}

// Reserved Slots
void Frostbite2CommandHandler::sendReservedSlotsListAddCommand(const QString &player)
{
    connection->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand()
{
    connection->sendCommand("reservedSlotsList.aggressiveJoin");
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    connection->sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendReservedSlotsListClearCommand()
{
    connection->sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListListCommand()
{
    connection->sendCommand("reservedSlotsList.list");
}

void Frostbite2CommandHandler::sendReservedSlotsListLoadCommand()
{
    connection->sendCommand("reservedSlotsList.load");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListRemoveCommand(const QString &player)
{
    connection->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListSaveCommand()
{
    connection->sendCommand("reservedSlotsList.save");
    sendReservedSlotsListListCommand();
}

// Squad
void Frostbite2CommandHandler::sendSquadLeaderCommand()
{
    connection->sendCommand("squad.leader");
}

void Frostbite2CommandHandler::sendSquadLeaderCommand(int teamId, int squadId, const QString &player)
{
    connection->sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void Frostbite2CommandHandler::sendSquadListActiveCommand(int teamId)
{
    connection->sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendSquadListPlayersCommand(int teamId, int squadId)
{
    connection->sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void Frostbite2CommandHandler::sendSquadPrivateCommand()
{
    connection->sendCommand("squad.private");
}

void Frostbite2CommandHandler::sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate)
{
    connection->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}

// Variables
void Frostbite2CommandHandler::sendVars3pCamCommand()
{
    connection->sendCommand("vars.3pCam");
}

void Frostbite2CommandHandler::sendVars3pCamCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.3pCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsAutoBalanceCommand()
{
    connection->sendCommand("vars.autoBalance");
}

void Frostbite2CommandHandler::sendVarsAutoBalanceCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.autoBalance\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsBulletDamageCommand(int damage)
{
    QString command;

    if (damage < 0) {
        command = "vars.bulletDamage";
    } else {
        command = QString("\"vars.bulletDamage\" \"%1\"").arg(damage);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsGameModeCounterCommand(int scale)
{
    QString command;

    if (scale < 0) {
        command = "vars.gameModeCounter";
    } else {
        command = QString("\"vars.gameModeCounter\" \"%1\"").arg(scale);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsHudCommand()
{
    connection->sendCommand("vars.hud");
}

void Frostbite2CommandHandler::sendVarsHudCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.hud\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsIdleBanRoundsCommand(int rounds)
{
    QString command;

    if (rounds < 0) {
        command = "vars.idleBanRounds";
    } else {
        command = QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsMaxPlayersCommand(int players)
{
    QString command;

    if (players < 0) {
        command = "vars.maxPlayers";
    } else {
        command = QString("\"vars.maxPlayers\" \"%1\"").arg(players);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsNameTagCommand()
{
    connection->sendCommand("vars.nameTag");
}

void Frostbite2CommandHandler::sendVarsNameTagCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.nameTag\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsOnlySquadLeaderSpawnCommand()
{
    connection->sendCommand("vars.onlySquadLeaderSpawn");
}

void Frostbite2CommandHandler::sendVarsOnlySquadLeaderSpawnCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.onlySquadLeaderSpawn\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsPlayerRespawnTimeCommand(int respawnTime)
{
    QString command;

    if (respawnTime < 0) {
        command = "vars.playerRespawnTime";
    } else {
        command = QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsRegenerateHealthCommand()
{
    connection->sendCommand("vars.regenerateHealth");
}

void Frostbite2CommandHandler::sendVarsRegenerateHealthCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.regenerateHealth\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsRoundLockdownCountdownCommand(int seconds)
{
    QString command;

    if (seconds < 0) {
        command = "vars.roundLockdownCountdown";
    } else {
        command = QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsRoundRestartPlayerCountCommand(int players)
{
    QString command;

    if (players < 0) {
        command = "vars.roundRestartPlayerCount";
    } else {
        command = QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsRoundStartPlayerCountCommand(int players)
{
    QString command;

    if (players < 0) {
        command = "vars.roundStartPlayerCount";
    } else {
        command = QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsServerMessageCommand(const QString &message)
{
    QString command;

    if (message.isEmpty()) {
        command = "vars.serverMessage";
    } else {
        command = QString("\"vars.serverMessage\" \"%1\"").arg(message);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsSoldierHealthCommand(int percent)
{
    QString command;

    if (percent < 0) {
        command = "vars.soldierHealth";
    } else {
        command = QString("\"vars.soldierHealth\" \"%1\"").arg(percent);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsTeamKillKickForBanCommand(int count)
{
    QString command;

    if (count < 0) {
        command = "vars.teamKillKickForBan";
    } else {
        command = QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsUnlockModeCommand(const QString &type)
{
    QString command;

    if (type.isEmpty()) {
        command = "vars.unlockMode";
    } else {
        command = QString("\"vars.unlockMode\" \"%1\"").arg(type);
    }

    connection->sendCommand(command);
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnAllowedCommand()
{
    connection->sendCommand("vars.vehicleSpawnAllowed");
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnAllowedCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.vehicleSpawnAllowed\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsVehicleSpawnDelayCommand(int percent)
{
    QString command;

    if (percent < 0) {
        command = "vars.vehicleSpawnDelay";
    } else {
        command = QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent);
    }

    connection->sendCommand(command);
}

/* Parse events */
void Frostbite2CommandHandler::parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void Frostbite2CommandHandler::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

    emit (onServerMaxPlayerCountChangeEvent(count));
}

/* Parse commands */
// Admin
void Frostbite2CommandHandler::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onAdminEventsEnabledCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList commandList;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            commandList.append(packet.getWord(i).getContent());
        }

        emit (onAdminHelpCommand(commandList));
    }
}

void Frostbite2CommandHandler::parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onAdminPasswordCommand(password));
    }
}

// Banning

// Maplist
void Frostbite2CommandHandler::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString value = packet.getWord(1).getContent();
        QStringList list;

        for (unsigned int i = 2; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onMapListAvailableMapsCommand(value, list));
    }
}

void Frostbite2CommandHandler::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentMapIndex = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        int nextMapIndex = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onMapListGetMapIndicesCommand(currentMapIndex, nextMapIndex));
    }
}

void Frostbite2CommandHandler::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentRound = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        int totalRounds = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onMapListGetRoundsCommand(currentRound, totalRounds));
    }
}

// Player
void Frostbite2CommandHandler::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        float idleDuration = FrostbiteUtils::toFloat(packet.getWord(1).getContent());

        emit (onPlayerIdleDurationCommand(idleDuration));
    }
}

void Frostbite2CommandHandler::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool alive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPlayerIsAliveCommand(alive));
    }
}

void Frostbite2CommandHandler::parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString player = packet.getWord(1).getContent();
        int ping = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onPlayerPingCommand(player, ping));
    }
}

// Punkbuster
void Frostbite2CommandHandler::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool active = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(active));
    }
}

// Reserved Slots
void Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListListCommand(reservedSlotList));
    }
}

// Squad
void Frostbite2CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString player = packet.getWord(1).getContent();

        emit (onSquadLeaderCommand(player));
    }
}

void Frostbite2CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        QStringList playerList;

        for (int i = 2; i < playerCount; i++) {
            playerList.append(packet.getWord(i).getContent());
        }

        emit (onSquadListPlayersCommand(playerList));
    }
}

void Frostbite2CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isPrivate = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onSquadPrivateCommand(isPrivate));
    }
}

// Variables
void Frostbite2CommandHandler::parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3pCamCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAutoBalanceCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsBulletDamageCommand(percent));
    }
}

void Frostbite2CommandHandler::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsGameModeCounterCommand(percent));
    }
}

void Frostbite2CommandHandler::parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHudCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int rounds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsIdleBanRoundsCommand(rounds));
    }
}

void Frostbite2CommandHandler::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsMaxPlayersCommand(playerCount));
    }
}

void Frostbite2CommandHandler::parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsNameTagCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsOnlySquadLeaderSpawnCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int respawnTime = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerRespawnTimeCommand(respawnTime));
    }
}

void Frostbite2CommandHandler::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsRegenerateHealthCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundLockdownCountdownCommand(seconds));
    }
}

void Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int players = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundRestartPlayerCountCommand(players));
    }
}

void Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int players = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundStartPlayerCountCommand(players));
    }
}

void Frostbite2CommandHandler::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString message = packet.getWord(1).getContent();

        emit (onVarsServerMessageCommand(message));
    }
}

void Frostbite2CommandHandler::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int health = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsSoldierHealthCommand(health));
    }
}

void Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillKickForBanCommand(count));
    }
}

void Frostbite2CommandHandler::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsUnlockModeCommand(type));
    }
}

void Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnAllowedCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int delay = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsVehicleSpawnDelayCommand(delay));
    }
}
