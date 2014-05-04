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
    if (request == "") {

    }

    // Parse commands.
    if (request == "login.plainText") {
        responseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        responseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "serverinfo") {
        responseServerInfoCommand(packet);
    } else if (request == "admin.help") {
        responseAdminHelpCommand(packet);
    } else if (request == "logout") {
        responseLogoutCommand(packet);
    } else if (request == "quit") {
        responseQuitCommand(packet);
    } else if (request == "version") {
        responseVersionCommand(packet);
    } else if (request == "listPlayers") {
        responseListPlayersCommand(packet);
    } else if (request == "admin.eventsEnabled") {
        responseAdminEventsEnabledCommand(packet);
    } else if (request == "admin.password") {
        responseAdminPasswordCommand(packet);
    } else if (request == "admin.effectiveMaxPlayers") {
        responseAdminEffectiveMaxPlayersCommand(packet);
    } else if (request == "admin.say") {
        responseAdminSayCommand(packet);
    } else if (request == "admin.yell") {
        responseAdminYellCommand(packet);
    } else if (request == "admin.kickPlayer") {
        responseAdminKickPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        responseAdminListPlayersCommand(packet, lastSentPacket);
    } else if (request == "admin.movePlayer") {
        responseAdminMovePlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        responseAdminKillPlayerCommand(packet);
    } else if (request == "player.idleDuration") {
        responsePlayerIdleDurationCommand(packet);
    } else if (request == "player.isAlive") {
        responsePlayerIsAliveCommand(packet);
    } else if (request == "player.ping") {
        responsePlayerPingCommand(packet);
    } else if (request == "squad.listActive") {
        responseSquadListActiveCommand(packet);
    } else if (request == "squad.listPlayers") {
        responseSquadListPlayersCommand(packet);
    } else if (request == "squad.private") {
        responseSquadPrivateCommand(packet);
    } else if (request == "squad.leader") {
        responseSquadLeaderCommand(packet);
    } else if (request == "punkBuster.isActive") {
        responsePunkBusterIsActiveCommand(packet);
    } else if (request == "punkBuster.activate") {
        responsePunkBusterActivateCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        responsePunkBusterPbSvCommandCommand(packet);
    } else if (request == "banList.load") {
        responseBanListLoadCommand(packet);
    } else if (request == "banList.save") {
        responseBanListSaveCommand(packet);
    } else if (request == "banList.add") {
        responseBanListAddCommand(packet);
    } else if (request == "banList.remove") {
        responseBanListRemoveCommand(packet);
    } else if (request == "banList.clear") {
        responseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        responseBanListListCommand(packet);
    } else if (request == "reservedSlotsList.load") {
        responseReservedSlotsListLoadCommand(packet);
    } else if (request == "reservedSlotsList.save") {
        responseReservedSlotsListSaveCommand(packet);
    } else if (request == "reservedSlotsList.add") {
        responseReservedSlotsListAddCommand(packet);
    } else if (request == "reservedSlotsList.remove") {
        responseReservedSlotsListRemoveCommand(packet);
    } else if (request == "reservedSlotsList.clear") {
        responseReservedSlotsListClearCommand(packet);
    } else if (request == "reservedSlotsList.list") {
        responseReservedSlotsListListCommand(packet);
    } else if (request == "reservedSlotsList.aggressiveJoin") {
        responseReservedSlotsListAggressiveJoinCommand(packet);
    } else if (request == "mapList.load") {
        responseMapListLoadCommand(packet);
    } else if (request == "mapList.save") {
        responseMapListSaveCommand(packet);
    } else if (request == "mapList.add") {
        responseMapListAddCommand(packet);
    } else if (request == "mapList.remove") {
        responseMapListRemoveCommand(packet);
    } else if (request == "mapList.clear") {
        responseMapListClearCommand(packet);
    } else if (request == "mapList.list") {
        responseMapListListCommand(packet);
    } else if (request == "mapList.setNextMapIndex") {
        responseMapListSetNextMapIndexCommand(packet);
    } else if (request == "mapList.getMapIndices") {
        responseMapListGetMapIndicesCommand(packet);
    } else if (request == "mapList.getRounds") {
        responseMapListGetRoundsCommand(packet);
    } else if (request == "mapList.endRound") {
        responseMapListEndRoundCommand(packet);
    } else if (request == "mapList.runNextRound") {
        responseMapListRunNextRoundCommand(packet);
    } else if (request == "mapList.restartRound") {
        responseMapListRestartRoundCommand(packet);
    } else if (request == "mapList.availableMaps") {
        responseMapListAvailableMapsCommand(packet);
    } else if (request == "vars.ranked") {
        responseVarsRankedCommand(packet);
    } else if (request == "vars.serverName") {
        responseVarsServerNameCommand(packet);
    } else if (request == "vars.gamePassword") {
        responseVarsGamePasswordCommand(packet);
    } else if (request == "vars.autoBalance") {
        responseVarsAutoBalanceCommand(packet);
    } else if (request == "vars.roundStartPlayerCount") {
        responseVarsRoundStartPlayerCountCommand(packet);
    } else if (request == "vars.roundRestartPlayerCount") {
        responseVarsRoundRestartPlayerCountCommand(packet);
    } else if (request == "vars.roundLockdownCountdown") {
        responseVarsRoundLockdownCountdownCommand(packet);
    } else if (request == "vars.serverMessage") {
        responseVarsServerMessageCommand(packet);
    } else if (request == "vars.friendlyFire") {
        responseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.maxPlayers") {
        responseVarsMaxPlayersCommand(packet);
    } else if (request == "vars.serverDescription") {
        responseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.killCam") {
        responseVarsKillCamCommand(packet);
    } else if (request == "vars.miniMap") {
        responseVarsMiniMapCommand(packet);
    } else if (request == "vars.hud") {
        responseVarsHudCommand(packet);
    } else if (request == "vars.crossHair") {
        responseVarsCrossHairCommand(packet);
    } else if (request == "vars.3dSpotting") {
        responsevars3dSpottingCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        responseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.nameTag") {
        responseVarsNameTagCommand(packet);
    } else if (request == "vars.3pCam") {
        responseVars3pCamCommand(packet);
    } else if (request == "vars.regenerateHealth") {
        responseVarsRegenerateHealthCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        responseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        responseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        responseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        responseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.teamKillKickForBan") {
        responseVarsTeamKillKickForBanCommand(packet);
    } else if (request == "vars.idleTimeout") {
        responseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.idleBanRounds") {
        responseVarsIdleBanRoundsCommand(packet);
    } else if (request == "vars.vehicleSpawnAllowed") {
        responseVarsVehicleSpawnAllowedCommand(packet);
    } else if (request == "vars.vehicleSpawnDelay") {
        responseVarsVehicleSpawnDelayCommand(packet);
    } else if (request == "vars.soldierHealth") {
        responseVarsSoldierHealthCommand(packet);
    } else if (request == "vars.playerRespawnTime") {
        responseVarsPlayerRespawnTimeCommand(packet);
    } else if (request == "vars.playerManDownTime") {
        responseVarsPlayerManDownTimeCommand(packet);
    } else if (request == "vars.bulletDamage") {
        responseVarsBulletDamageCommand(packet);
    } else if (request == "vars.gameModeCounter") {
        responseVarsGameModeCounterCommand(packet);
    } else if (request == "vars.onlySquadLeaderSpawn") {
        responseVarsOnlySquadLeaderSpawnCommand(packet);
    } else if (request == "vars.unlockMode") {
        responseVarsUnlockModeCommand(packet);
    } else if (request == "vars.premiumStatus") {
        responseVarsPremiumStatusCommand(packet);
    } else if (request == "vars.bannerUrl") {
        responseVarsBannerUrlCommand(packet);
    } else if (request == "vars.roundsPerMap") {
        responseVarsRoundsPerMapCommand(packet);
    } else if (request == "vars.gunMasterWeaponsPreset") {
        responseVarsGunMasterWeaponsPresetCommand(packet);
    } else {
        responseUnknownCommand();
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
void BF3Connection::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

void BF3Connection::responseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF3Connection::responseListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket)
}

void BF3Connection::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseBanListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responsevars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3Connection::responseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
