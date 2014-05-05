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

#include "BF3Connection.h"

BF3Connection::BF3Connection(QObject *parent) : FrostbiteConnection(parent)
{

}

BF3Connection::~BF3Connection()
{

}

void BF3Connection::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse events.

    // Parse commands.
    if (request == "login.plainText") {
        parseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        parseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "serverinfo") {
        parseServerInfoCommand(packet);
    } else if (request == "admin.help") {
        parseAdminHelpCommand(packet);
    } else if (request == "logout") {
        parseLogoutCommand(packet);
    } else if (request == "quit") {
        parseQuitCommand(packet);
    } else if (request == "version") {
        parseVersionCommand(packet);
    } else if (request == "listPlayers") {
        parseListPlayersCommand(packet);
    } else if (request == "admin.eventsEnabled") {
        parseAdminEventsEnabledCommand(packet);
    } else if (request == "admin.password") {
        parseAdminPasswordCommand(packet);
    } else if (request == "admin.effectiveMaxPlayers") {
        parseAdminEffectiveMaxPlayersCommand(packet);
    } else if (request == "admin.say") {
        parseAdminSayCommand(packet);
    } else if (request == "admin.yell") {
        parseAdminYellCommand(packet);
    } else if (request == "admin.kickPlayer") {
        parseAdminKickPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        parseAdminListPlayersCommand(packet, lastSentPacket);
    } else if (request == "admin.movePlayer") {
        parseAdminMovePlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        parseAdminKillPlayerCommand(packet);
    } else if (request == "player.idleDuration") {
        parsePlayerIdleDurationCommand(packet);
    } else if (request == "player.isAlive") {
        parsePlayerIsAliveCommand(packet);
    } else if (request == "player.ping") {
        parsePlayerPingCommand(packet);
    } else if (request == "squad.listActive") {
        parseSquadListActiveCommand(packet);
    } else if (request == "squad.listPlayers") {
        parseSquadListPlayersCommand(packet);
    } else if (request == "squad.private") {
        parseSquadPrivateCommand(packet);
    } else if (request == "squad.leader") {
        parseSquadLeaderCommand(packet);
    } else if (request == "punkBuster.isActive") {
        parsePunkBusterIsActiveCommand(packet);
    } else if (request == "punkBuster.activate") {
        parsePunkBusterActivateCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        parsePunkBusterPbSvCommandCommand(packet);
    } else if (request == "banList.load") {
        parseBanListLoadCommand(packet);
    } else if (request == "banList.save") {
        parseBanListSaveCommand(packet);
    } else if (request == "banList.add") {
        parseBanListAddCommand(packet);
    } else if (request == "banList.remove") {
        parseBanListRemoveCommand(packet);
    } else if (request == "banList.clear") {
        parseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        parseBanListListCommand(packet);
    } else if (request == "reservedSlotsList.load") {
        parseReservedSlotsListLoadCommand(packet);
    } else if (request == "reservedSlotsList.save") {
        parseReservedSlotsListSaveCommand(packet);
    } else if (request == "reservedSlotsList.add") {
        parseReservedSlotsListAddCommand(packet);
    } else if (request == "reservedSlotsList.remove") {
        parseReservedSlotsListRemoveCommand(packet);
    } else if (request == "reservedSlotsList.clear") {
        parseReservedSlotsListClearCommand(packet);
    } else if (request == "reservedSlotsList.list") {
        parseReservedSlotsListListCommand(packet);
    } else if (request == "reservedSlotsList.aggressiveJoin") {
        parseReservedSlotsListAggressiveJoinCommand(packet);
    } else if (request == "mapList.load") {
        parseMapListLoadCommand(packet);
    } else if (request == "mapList.save") {
        parseMapListSaveCommand(packet);
    } else if (request == "mapList.add") {
        parseMapListAddCommand(packet);
    } else if (request == "mapList.remove") {
        parseMapListRemoveCommand(packet);
    } else if (request == "mapList.clear") {
        parseMapListClearCommand(packet);
    } else if (request == "mapList.list") {
        parseMapListListCommand(packet);
    } else if (request == "mapList.setNextMapIndex") {
        parseMapListSetNextMapIndexCommand(packet);
    } else if (request == "mapList.getMapIndices") {
        parseMapListGetMapIndicesCommand(packet);
    } else if (request == "mapList.getRounds") {
        parseMapListGetRoundsCommand(packet);
    } else if (request == "mapList.endRound") {
        parseMapListEndRoundCommand(packet);
    } else if (request == "mapList.runNextRound") {
        parseMapListRunNextRoundCommand(packet);
    } else if (request == "mapList.restartRound") {
        parseMapListRestartRoundCommand(packet);
    } else if (request == "mapList.availableMaps") {
        parseMapListAvailableMapsCommand(packet);
    } else if (request == "vars.ranked") {
        parseVarsRankedCommand(packet);
    } else if (request == "vars.serverName") {
        parseVarsServerNameCommand(packet);
    } else if (request == "vars.gamePassword") {
        parseVarsGamePasswordCommand(packet);
    } else if (request == "vars.autoBalance") {
        parseVarsAutoBalanceCommand(packet);
    } else if (request == "vars.roundStartPlayerCount") {
        parseVarsRoundStartPlayerCountCommand(packet);
    } else if (request == "vars.roundRestartPlayerCount") {
        parseVarsRoundRestartPlayerCountCommand(packet);
    } else if (request == "vars.roundLockdownCountdown") {
        parseVarsRoundLockdownCountdownCommand(packet);
    } else if (request == "vars.serverMessage") {
        parseVarsServerMessageCommand(packet);
    } else if (request == "vars.friendlyFire") {
        parseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.maxPlayers") {
        parseVarsMaxPlayersCommand(packet);
    } else if (request == "vars.serverDescription") {
        parseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.killCam") {
        parseVarsKillCamCommand(packet);
    } else if (request == "vars.miniMap") {
        parseVarsMiniMapCommand(packet);
    } else if (request == "vars.hud") {
        parseVarsHudCommand(packet);
    } else if (request == "vars.crossHair") {
        parseVarsCrossHairCommand(packet);
    } else if (request == "vars.3dSpotting") {
        parsevars3dSpottingCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        parseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.nameTag") {
        parseVarsNameTagCommand(packet);
    } else if (request == "vars.3pCam") {
        parseVars3pCamCommand(packet);
    } else if (request == "vars.regenerateHealth") {
        parseVarsRegenerateHealthCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        parseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        parseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        parseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        parseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.teamKillKickForBan") {
        parseVarsTeamKillKickForBanCommand(packet);
    } else if (request == "vars.idleTimeout") {
        parseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.idleBanRounds") {
        parseVarsIdleBanRoundsCommand(packet);
    } else if (request == "vars.vehicleSpawnAllowed") {
        parseVarsVehicleSpawnAllowedCommand(packet);
    } else if (request == "vars.vehicleSpawnDelay") {
        parseVarsVehicleSpawnDelayCommand(packet);
    } else if (request == "vars.soldierHealth") {
        parseVarsSoldierHealthCommand(packet);
    } else if (request == "vars.playerRespawnTime") {
        parseVarsPlayerRespawnTimeCommand(packet);
    } else if (request == "vars.playerManDownTime") {
        parseVarsPlayerManDownTimeCommand(packet);
    } else if (request == "vars.bulletDamage") {
        parseVarsBulletDamageCommand(packet);
    } else if (request == "vars.gameModeCounter") {
        parseVarsGameModeCounterCommand(packet);
    } else if (request == "vars.onlySquadLeaderSpawn") {
        parseVarsOnlySquadLeaderSpawnCommand(packet);
    } else if (request == "vars.unlockMode") {
        parseVarsUnlockModeCommand(packet);
    } else if (request == "vars.premiumStatus") {
        parseVarsPremiumStatusCommand(packet);
    } else if (request == "vars.bannerUrl") {
        parseVarsBannerUrlCommand(packet);
    } else if (request == "vars.roundsPerMap") {
        parseVarsRoundsPerMapCommand(packet);
    } else if (request == "vars.gunMasterWeaponsPreset") {
        parseVarsGunMasterWeaponsPresetCommand(packet);
    }
}

/* Send */

// Misc
void BF3Connection::sendLoginPlainTextCommand(const QString &password)
{
    sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void BF3Connection::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BF3Connection::sendServerInfoCommand()
{
    sendCommand("serverInfo");
}

void BF3Connection::sendLogoutCommand()
{
    sendCommand("logout");
}

void BF3Connection::sendQuitCommand()
{
    sendCommand("quit");
}

void BF3Connection::sendVersionCommand()
{
    sendCommand("version");
}

void BF3Connection::sendCurrentLevelCommand()
{
    sendCommand("currentLevel");
}

void BF3Connection::sendListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        sendCommand("\"listPlayers\" \"all\"");
    }
}

/* Parse */

// Events

// Commands
void BF3Connection::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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
        } else if (response == "InvalidPasswordHash") {
            emit (onLoginHashedCommand(false));
        }
    }
}

void BF3Connection::parseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF3Connection::parseListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket)
}

void BF3Connection::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseBanListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parsevars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
