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
#include "Frostbite2ServerInfo.h"
#include "BF3ServerInfo.h"
#include "BF4ServerInfo.h"
#include "PlayerInfo.h"
#include "BanListEntry.h"

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
        { "player.onAuthenticated",                 &Frostbite2CommandHandler::parsePlayerAuthenticatedEvent },
        { "player.onJoin",                          &Frostbite2CommandHandler::parsePlayerJoinEvent },
        { "player.onSpawn",                         &Frostbite2CommandHandler::parsePlayerSpawnEvent },
        { "player.onKill",                          &Frostbite2CommandHandler::parsePlayerKillEvent },
        { "server.onLevelLoaded",                   &Frostbite2CommandHandler::parseServerLevelLoadedEvent },

        /* Commands */
        // Misc
        { "login.plainText",                        &Frostbite2CommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",                           &Frostbite2CommandHandler::parseLoginHashedCommand },
        { "serverInfo",                             &Frostbite2CommandHandler::parseServerInfoCommand },
        { "logout",                                 &Frostbite2CommandHandler::parseLogoutCommand },
        { "quit",                                   &Frostbite2CommandHandler::parseQuitCommand },
        { "version",                                &Frostbite2CommandHandler::parseVersionCommand },
        { "currentLevel",                           &Frostbite2CommandHandler::parseCurrentLevelCommand },
        { "listPlayers",                            nullptr /*&Frostbite2CommandHandler::parseListPlayersCommand*/ },

        // Admin
        { "admin.eventsEnabled",                    &Frostbite2CommandHandler::parseAdminEventsEnabledCommand },
        { "admin.help",                             &Frostbite2CommandHandler::parseAdminHelpCommand },
        { "admin.kickPlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.listPlayers",                      nullptr /*&Frostbite2CommandHandler::parseAdminListPlayersCommand*/ },
        { "admin.movePlayer",                       nullptr /*&Frostbite2CommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.password",                         &Frostbite2CommandHandler::parseAdminPasswordCommand },
        { "admin.say",                              nullptr /*&Frostbite2CommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                             nullptr /*&Frostbite2CommandHandler::parseAdminYellCommand*/ },

        // Banning
        { "banList.add",                            nullptr /*&Frostbite2CommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                          nullptr /*&Frostbite2CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                           &Frostbite2CommandHandler::parseBanListListCommand },
        { "banList.load",                           nullptr /*&Frostbite2CommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                         nullptr /*&Frostbite2CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                           nullptr /*&Frostbite2CommandHandler::parseBanListSaveCommand*/ },

        // Maplist
        { "mapList.add",                            nullptr /*&Frostbite2CommandHandler::parseMapListAddCommand*/ },
        { "mapList.availableMaps",                  &Frostbite2CommandHandler::parseMapListAvailableMapsCommand },
        { "mapList.clear",                          nullptr /*&Frostbite2CommandHandler::parseMapListClearCommand*/ },
        { "mapList.endRound",                       nullptr /*&Frostbite2CommandHandler::parseMapListEndRoundCommand*/ },
        { "mapList.getMapIndices",                  &Frostbite2CommandHandler::parseMapListGetMapIndicesCommand },
        { "mapList.getRounds",                      &Frostbite2CommandHandler::parseMapListGetRoundsCommand },
        { "mapList.list",                           &Frostbite2CommandHandler::parseMapListListCommand },
        { "mapList.load",                           nullptr /*&Frostbite2CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                         nullptr /*&Frostbite2CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.restartRound",                   nullptr /*&Frostbite2CommandHandler::parseMapListRestartRoundCommand*/ },
        { "mapList.runNextRound",                   nullptr /*&Frostbite2CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.save",                           nullptr /*&Frostbite2CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.setNextMapIndex",                nullptr /*&Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand*/ },

        // Player
        { "player.idleDuration",                    &Frostbite2CommandHandler::parsePlayerIdleDurationCommand },
        { "player.isAlive",                         &Frostbite2CommandHandler::parsePlayerIsAliveCommand },
        { "player.ping",                            &Frostbite2CommandHandler::parsePlayerPingCommand },

        // Punkbuster
        { "punkBuster.activate",                    nullptr /*&Frostbite2CommandHandler::parsePunkBusterActivateCommand*/ },
        { "punkBuster.isActive",                    &Frostbite2CommandHandler::parsePunkBusterIsActiveCommand },
        { "punkBuster.pb_sv_command",               nullptr /*&Frostbite2CommandHandler::parsePunkBusterPbSvCommand*/ },

        // Reserved Slots
        { "reservedSlotsList.add",                  nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListAddCommand*/ },
        { "reservedSlotsList.aggressiveJoin",       &Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        { "reservedSlotsList.clear",                nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListClearCommand*/ },
        { "reservedSlotsList.list",                 &Frostbite2CommandHandler::parseReservedSlotsListListCommand },
        { "reservedSlotsList.load",                 nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListLoadCommand*/ },
        { "reservedSlotsList.remove",               nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        { "reservedSlotsList.save",                 nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListSaveCommand*/ },

        // Squad
        { "squad.leader",                           &Frostbite2CommandHandler::parseSquadLeaderCommand },
        { "squad.listActive",                       nullptr /*&Frostbite2CommandHandler::parseSquadListActiveCommand*/ },
        { "squad.listPlayers",                      &Frostbite2CommandHandler::parseSquadListPlayersCommand },
        { "squad.private",                          &Frostbite2CommandHandler::parseSquadPrivateCommand },

        // Variables
        { "vars.3dSpotting",                        &Frostbite2CommandHandler::parseVars3dSpottingCommand },
        { "vars.3pCam",                             &Frostbite2CommandHandler::parseVars3pCamCommand },
        { "vars.autoBalance",                       &Frostbite2CommandHandler::parseVarsAutoBalanceCommand },
        { "vars.bulletDamage",                      &Frostbite2CommandHandler::parseVarsBulletDamageCommand },
        { "vars.friendlyFire",                      &Frostbite2CommandHandler::parseVarsFriendlyFireCommand },
        { "vars.gameModeCounter",                   &Frostbite2CommandHandler::parseVarsGameModeCounterCommand },
        { "vars.gamePassword",                      &Frostbite2CommandHandler::parseVarsGamePasswordCommand },
        { "vars.hud",                               &Frostbite2CommandHandler::parseVarsHudCommand },
        { "vars.idleBanRounds",                     &Frostbite2CommandHandler::parseVarsIdleBanRoundsCommand },
        { "vars.idleTimeout",                       &Frostbite2CommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.killCam",                           &Frostbite2CommandHandler::parseVarsKillCamCommand },
        { "vars.maxPlayers",                        &Frostbite2CommandHandler::parseVarsMaxPlayersCommand },
        { "vars.miniMap",                           &Frostbite2CommandHandler::parseVarsMiniMapCommand },
        { "vars.miniMapSpotting",                   &Frostbite2CommandHandler::parseVarsMiniMapSpottingCommand },
        { "vars.nameTag",                           &Frostbite2CommandHandler::parseVarsNameTagCommand },
        { "vars.onlySquadLeaderSpawn",              &Frostbite2CommandHandler::parseVarsOnlySquadLeaderSpawnCommand },
        { "vars.playerRespawnTime",                 &Frostbite2CommandHandler::parseVarsPlayerRespawnTimeCommand },
        { "vars.regenerateHealth",                  &Frostbite2CommandHandler::parseVarsRegenerateHealthCommand },
        { "vars.roundLockdownCountdown",            &Frostbite2CommandHandler::parseVarsRoundLockdownCountdownCommand },
        { "vars.roundRestartPlayerCount",           &Frostbite2CommandHandler::parseVarsRoundRestartPlayerCountCommand },
        { "vars.roundStartPlayerCount",             &Frostbite2CommandHandler::parseVarsRoundStartPlayerCountCommand },
        { "vars.serverDescription",                 &Frostbite2CommandHandler::parseVarsServerDescriptionCommand },
        { "vars.serverMessage",                     &Frostbite2CommandHandler::parseVarsServerMessageCommand },
        { "vars.serverName",                        &Frostbite2CommandHandler::parseVarsServerNameCommand },
        { "vars.soldierHealth",                     &Frostbite2CommandHandler::parseVarsSoldierHealthCommand },
        { "vars.teamKillCountForKick",              &Frostbite2CommandHandler::parseVarsTeamKillCountForKickCommand },
        { "vars.teamKillKickForBan",                &Frostbite2CommandHandler::parseVarsTeamKillKickForBanCommand },
        { "vars.teamKillValueDecreasePerSecond",    &Frostbite2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },
        { "vars.teamKillValueForKick",              &Frostbite2CommandHandler::parseVarsTeamKillValueForKickCommand },
        { "vars.teamKillValueIncrease",             &Frostbite2CommandHandler::parseVarsTeamKillValueIncreaseCommand },
        { "vars.unlockMode",                        &Frostbite2CommandHandler::parseVarsUnlockModeCommand },
        { "vars.vehicleSpawnAllowed",               &Frostbite2CommandHandler::parseVarsVehicleSpawnAllowedCommand },
        { "vars.vehicleSpawnDelay",                 &Frostbite2CommandHandler::parseVarsVehicleSpawnDelayCommand },
        { "vars.gunMasterWeaponsPreset",            nullptr /*&Frostbite2CommandHandler::parseGunMasterWeaponsPresetCommand*/ }
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return false;
}

/* Send commands */
// Misc
void Frostbite2CommandHandler::sendLoginPlainTextCommand(const QString &password)
{
    connection->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void Frostbite2CommandHandler::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        connection->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            connection->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void Frostbite2CommandHandler::sendServerInfoCommand()
{
    connection->sendCommand("serverInfo");
}

void Frostbite2CommandHandler::sendLogoutCommand()
{
    connection->sendCommand("logout");
}

void Frostbite2CommandHandler::sendQuitCommand()
{
    connection->sendCommand("quit");
}

void Frostbite2CommandHandler::sendVersionCommand()
{
    //connection->sendCommand("version");
}

void Frostbite2CommandHandler::sendCurrentLevelCommand()
{
    connection->sendCommand("currentLevel");
}

// Admin
void Frostbite2CommandHandler::sendAdminEventsEnabledCommand(bool enabled)
{
    connection->sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendAdminHelpCommand()
{
    connection->sendCommand("admin.help");
}

void Frostbite2CommandHandler::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    connection->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void Frostbite2CommandHandler::sendAdminKillPlayerCommand(const QString &player)
{
    connection->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill)
{
    connection->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void Frostbite2CommandHandler::sendAdminPasswordCommand(const QString &password)
{
    if (password.isEmpty()) {
        connection->sendCommand("admin.password");
    } else {
        connection->sendCommand(QString("\"admin.password\" \"%1\"").arg(password));
    }
}

void Frostbite2CommandHandler::sendAdminSayCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (playerSubset == PlayerSubsetEnum::All) {
        connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(message, PlayerSubset::toString(playerSubset)));
    } else {
        connection->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(message, PlayerSubset::toString(playerSubset)).arg(parameter));
    }
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, const PlayerSubsetEnum &playerSubset, int parameter)
{
    sendAdminYellCommand(message, 10, playerSubset, parameter);
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, int duration, const PlayerSubsetEnum &playerSubset, int parameter)
{
    if (message.length() <= 256) {
        if (playerSubset == PlayerSubsetEnum::All) {
            connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset)));
        } else {
            connection->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(message).arg(duration).arg(PlayerSubset::toString(playerSubset)).arg(parameter));
        }
    }
}

// Banning
void Frostbite2CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    connection->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutString = useRounds ? "rounds" : "seconds";
    timeoutString += " " + QString::number(timeout);

    connection->sendCommand(QString("banList.add %1 %2 %3 %4").arg(idType, id, timeoutString, reason));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListClearCommand()
{
    connection->sendCommand("banList.clear");
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListListCommand(int index)
{
    if (index == 0) {
        connection->sendCommand("banList.list");
    } else {
        connection->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void Frostbite2CommandHandler::sendBanListLoadCommand()
{
    connection->sendCommand("banList.load");
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    connection->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListSaveCommand()
{
    connection->sendCommand("banList.save");
}

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

void Frostbite2CommandHandler::sendMapListClearCommand()
{
    connection->sendCommand("mapList.clear");
    sendMapListListCommand();
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

void Frostbite2CommandHandler::sendMapListListCommand(int index)
{
    if (index == 0) {
        connection->sendCommand("mapList.list");
    } else {
        connection->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void Frostbite2CommandHandler::sendMapListLoadCommand()
{
    connection->sendCommand("mapList.load");
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListRemoveCommand(int index)
{
    connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListRestartRoundCommand()
{
    connection->sendCommand("mapList.restartRound");
}

void Frostbite2CommandHandler::sendMapListRunNextRoundCommand()
{
    connection->sendCommand("mapList.runNextRound");
}

void Frostbite2CommandHandler::sendMapListSaveCommand()
{
    connection->sendCommand("mapList.save");
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

// PunkBuster
void Frostbite2CommandHandler::sendPunkBusterActivateCommand()
{
    connection->sendCommand("punkBuster.activate");
}

void Frostbite2CommandHandler::sendPunkBusterIsActiveCommand()
{
    connection->sendCommand("punkBuster.isActive");
}

void Frostbite2CommandHandler::sendPunkBusterPbSvCommand(const QString &command)
{
    if (!command.isEmpty()) {
        connection->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
    }
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

void Frostbite2CommandHandler::sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate)
{
    connection->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}

// Variables
void Frostbite2CommandHandler::sendVars3dSpottingCommand()
{
    connection->sendCommand("vars.3dSpotting");
}

void Frostbite2CommandHandler::sendVars3dSpottingCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

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
    if (damage == -1) {
        connection->sendCommand("vars.bulletDamage");
    } else {
        connection->sendCommand(QString("\"vars.bulletDamage\" \"%1\"").arg(damage));
    }
}

void Frostbite2CommandHandler::sendVarsFriendlyFireCommand()
{
    connection->sendCommand("vars.friendlyFire");
}

void Frostbite2CommandHandler::sendVarsFriendlyFireCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsGameModeCounterCommand(int scale)
{
    if (scale == -1) {
        connection->sendCommand("vars.gameModeCounter");
    } else {
        connection->sendCommand(QString("\"vars.gameModeCounter\" \"%1\"").arg(scale));
    }
}

void Frostbite2CommandHandler::sendVarsGamePasswordCommand(const QString &password)
{
    if (password == 0) {
        connection->sendCommand("vars.gamePassword");
    } else {
        connection->sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
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
    if (rounds == -1) {
        connection->sendCommand("vars.idleBanRounds");
    } else {
        connection->sendCommand(QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds));
    }
}

void Frostbite2CommandHandler::sendVarsIdleTimeoutCommand(int seconds)
{
    if (seconds == -1) {
        connection->sendCommand("vars.idleTimeout");
    } else {
        connection->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void Frostbite2CommandHandler::sendVarsKillCamCommand()
{
    connection->sendCommand("vars.killCam");
}

void Frostbite2CommandHandler::sendVarsKillCamCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsMaxPlayersCommand(int players)
{
    if (players == -1) {
        connection->sendCommand("vars.maxPlayers");
    } else {
        connection->sendCommand(QString("\"vars.maxPlayers\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsMiniMapCommand()
{
    connection->sendCommand("vars.miniMap");
}

void Frostbite2CommandHandler::sendVarsMiniMapCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendVarsMiniMapSpottingCommand()
{
    connection->sendCommand("vars.miniMapSpotting");
}

void Frostbite2CommandHandler::sendVarsMiniMapSpottingCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
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
    if (respawnTime == -1) {
        connection->sendCommand("vars.playerRespawnTime");
    } else {
        connection->sendCommand(QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime));
    }
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
    if (seconds == -1) {
        connection->sendCommand("vars.roundLockdownCountdown");
    } else {
        connection->sendCommand(QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds));
    }
}

void Frostbite2CommandHandler::sendVarsRoundRestartPlayerCountCommand(int players)
{
    if (players == -1) {
        connection->sendCommand("vars.roundRestartPlayerCount");
    } else {
        connection->sendCommand(QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsRoundStartPlayerCountCommand(int players)
{
    if (players == -1) {
        connection->sendCommand("vars.roundStartPlayerCount");
    } else {
        connection->sendCommand(QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players));
    }
}

void Frostbite2CommandHandler::sendVarsServerDescriptionCommand(const QString &description)
{
    if (description == 0) {
        connection->sendCommand("vars.serverDescription");
    } else {
        connection->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void Frostbite2CommandHandler::sendVarsServerMessageCommand(const QString &message)
{
    if (message == 0) {
        connection->sendCommand("vars.serverMessage");
    } else {
        connection->sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(message));
    }
}

void Frostbite2CommandHandler::sendVarsServerNameCommand(const QString &name)
{
    if (name == 0) {
        connection->sendCommand("vars.serverName");
    } else {
        connection->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void Frostbite2CommandHandler::sendVarsSoldierHealthCommand(int percent)
{
    if (percent == -1) {
        connection->sendCommand("vars.soldierHealth");
    } else {
        connection->sendCommand(QString("\"vars.soldierHealth\" \"%1\"").arg(percent));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillCountForKickCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillCountForKick");
    } else {
        connection->sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillKickForBanCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillKickForBan");
    } else {
        connection->sendCommand(QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueDecreasePerSecondCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueForKickCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueForKick");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsTeamKillValueIncreaseCommand(int count)
{
    if (count == -1) {
        connection->sendCommand("vars.teamKillValueIncrease");
    } else {
        connection->sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

void Frostbite2CommandHandler::sendVarsUnlockModeCommand(const QString &type)
{
    if (type == 0) {
        connection->sendCommand("vars.unlockMode");
    } else {
        connection->sendCommand(QString("\"vars.unlockMode\" \"%1\"").arg(type));
    }
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
    if (percent == -1) {
        connection->sendCommand("vars.vehicleSpawnDelay");
    } else {
        connection->sendCommand(QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent));
    }
}

QList<PlayerInfo> Frostbite2CommandHandler::parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();
    QList<PlayerInfo> playerList;

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int parameters = QString(packet.getWord(1).getContent()).toInt();
        int players = QString(packet.getWord(2 + parameters).getContent()).toInt();

        for (int i = 0; i < players; i++) {
            QStringList list;

            for (int j = 0; j < parameters; j++) {
                list.append(packet.getWord(2 + parameters + 1 + i * parameters + j).getContent());
            }

            QString name = list.at(0);
            QString guid = list.at(1);
            int teamId = FrostbiteUtils::toInt(list.at(2));
            int squadId = FrostbiteUtils::toInt(list.at(3));
            int kills = FrostbiteUtils::toInt(list.at(4));
            int deaths = FrostbiteUtils::toInt(list.at(5));
            int score = FrostbiteUtils::toInt(list.at(6));
            int rank = FrostbiteUtils::toInt(list.at(7));
            int ping = FrostbiteUtils::toInt(list.at(8));

            playerList.append(PlayerInfo(name, guid, teamId, squadId, kills, deaths, score, rank, ping));
        }
    }

    return playerList;
}

/* Parse events */
void Frostbite2CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void Frostbite2CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void Frostbite2CommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void Frostbite2CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

    emit (onPlayerSpawnEvent(player, teamId));
}

void Frostbite2CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void Frostbite2CommandHandler::parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString levelName = packet.getWord(1).getContent();
    QString gameModeName = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit (onServerLevelLoadedEvent(levelName, gameModeName, roundsPlayed, roundsTotal));
}

void Frostbite2CommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void Frostbite2CommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void Frostbite2CommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void Frostbite2CommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void Frostbite2CommandHandler::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

    emit (onServerMaxPlayerCountChangeEvent(count));
}

void Frostbite2CommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void Frostbite2CommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void Frostbite2CommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Parse commands */
// Misc
void Frostbite2CommandHandler::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(true));
    } else {
        emit (onLoginPlainTextCommand(false));
    }
}

void Frostbite2CommandHandler::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit (onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit (onLoginHashedCommand(true));
        } else { // if (response == "InvalidPasswordHash")
            emit (onLoginHashedCommand(false));
        }
    }
}

void Frostbite2CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();
        int playerCount = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int maxPlayerCount = FrostbiteUtils::toInt(packet.getWord(3).getContent());
        QString gamemode = packet.getWord(4).getContent();
        QString currentMap = packet.getWord(5).getContent();
        int roundsPlayed = FrostbiteUtils::toInt(packet.getWord(6).getContent());
        int roundsTotal = FrostbiteUtils::toInt(packet.getWord(7).getContent());

        // Parsing team scores.
        int entries = FrostbiteUtils::toInt(packet.getWord(8).getContent());
        int entriesIndex = 9 + entries;
        QList<int> scoreList;

        for (int i = 9; i <= entriesIndex; i++) {
            scoreList.append(FrostbiteUtils::toInt(packet.getWord(i).getContent()));
        }

        int targetScore = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 1).getContent());
        TeamScores scores(scoreList, targetScore);

        bool ranked = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 2).getContent());
        bool punkBuster = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 3).getContent());
        bool hasGamePassword = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 4).getContent());
        int serverUpTime = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 5).getContent());
        int roundTime = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 6).getContent());
        QString gameIpAndPort = packet.getWord(entriesIndex + 7).getContent();
        QString punkBusterVersion = packet.getWord(entriesIndex + 8).getContent();
        bool joinQueueEnabled = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 9).getContent());
        QString region = packet.getWord(entriesIndex + 10).getContent();
        QString closestPingSite = packet.getWord(entriesIndex + 11).getContent();
        QString country = packet.getWord(entriesIndex + 12).getContent();

        Frostbite2ServerInfo serverInfo(serverName,
                                        playerCount,
                                        maxPlayerCount,
                                        gamemode,
                                        currentMap,
                                        roundsPlayed,
                                        roundsTotal,
                                        scores,
                                        ranked,
                                        punkBuster,
                                        hasGamePassword,
                                        serverUpTime,
                                        roundTime,
                                        gameIpAndPort,
                                        punkBusterVersion,
                                        joinQueueEnabled,
                                        region,
                                        closestPingSite,
                                        country);

        emit (onServerInfoCommand(serverInfo));

        // BF3 Only.
        if (dynamic_cast<BF3CommandHandler*>(this)) {
            bool matchMakingEnabled = FrostbiteUtils::toBool(packet.getWord(entriesIndex + 13).getContent());

            BF3ServerInfo serverInfo(serverName,
                                     playerCount,
                                     maxPlayerCount,
                                     gamemode,
                                     currentMap,
                                     roundsPlayed,
                                     roundsTotal,
                                     scores,
                                     ranked,
                                     punkBuster,
                                     hasGamePassword,
                                     serverUpTime,
                                     roundTime,
                                     gameIpAndPort,
                                     punkBusterVersion,
                                     joinQueueEnabled,
                                     region,
                                     closestPingSite,
                                     country,
                                     matchMakingEnabled);

            emit (onServerInfoCommand(serverInfo));

        // BF4 Only.
        } else if (dynamic_cast<BF4CommandHandler*>(this)) {
            int blazePlayerCount = FrostbiteUtils::toInt(packet.getWord(entriesIndex + 13).getContent());
            QString blazeGameState = packet.getWord(entriesIndex + 14).getContent();

            BF4ServerInfo serverInfo(serverName,
                                     playerCount,
                                     maxPlayerCount,
                                     gamemode,
                                     currentMap,
                                     roundsPlayed,
                                     roundsTotal,
                                     scores,
                                     ranked,
                                     punkBuster,
                                     hasGamePassword,
                                     serverUpTime,
                                     roundTime,
                                     gameIpAndPort,
                                     punkBusterVersion,
                                     joinQueueEnabled,
                                     region,
                                     closestPingSite,
                                     country,
                                     blazePlayerCount,
                                     blazeGameState);

            emit (onServerInfoCommand(serverInfo));
        }
    }
}

void Frostbite2CommandHandler::parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand());
    }
}

void Frostbite2CommandHandler::parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand());
    }
}

void Frostbite2CommandHandler::parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void Frostbite2CommandHandler::parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString level = packet.getWord(1).getContent();

        emit (onCurrentLevelCommand(level));
    }
}

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
void Frostbite2CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QList<BanListEntry> banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            QString banIdType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = FrostbiteUtils::toInt(packet.getWord(i + 3).getContent());
            int rounds = FrostbiteUtils::toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(banIdType, id, banType, seconds, rounds, reason));
        }

        emit (onBanListListCommand(banList));
    }
}

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

void Frostbite2CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        MapList mapList;
        int maps = QString(packet.getWord(1).getContent()).toInt();
        int parameters = QString(packet.getWord(2).getContent()).toInt();

        for (int i = 0; i < maps; i++) {
            QString level;
            QString gameMode;
            int rounds = 0;

            for (int j = 0; j < parameters; j++) {
                QString data = packet.getWord(3 + (i * parameters) + j).getContent();

                switch (j) {
                    case 0:
                        level = data;
                        break;
                    case 1:
                        gameMode = data;
                        break;
                    case 2:
                        rounds = data.toInt();
                        break;
                }
            }

            mapList.append(MapListEntry(level, gameMode, rounds));
        }

        emit (onMapListListCommand(mapList));
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
void Frostbite2CommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3dSpottingCommand(enabled));
    }
}

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

void Frostbite2CommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
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

void Frostbite2CommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onVarsGamePasswordCommand(password));
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

void Frostbite2CommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(seconds));
    }
}

void Frostbite2CommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
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

void Frostbite2CommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapSpottingCommand(enabled));
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

void Frostbite2CommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(description));
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

void Frostbite2CommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(name));
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

void Frostbite2CommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillCountForKickCommand(count));
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

void Frostbite2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void Frostbite2CommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueForKickCommand(count));
    }
}

void Frostbite2CommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueIncreaseCommand(count));
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
