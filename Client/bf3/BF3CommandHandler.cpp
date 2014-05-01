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

#include "BF3CommandHandler.h"

BF3CommandHandler::BF3CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BF3CommandHandler::~BF3CommandHandler()
{

}

void BF3CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
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
    }
}

/* Commands */
void BF3CommandHandler::responseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

void BF3CommandHandler::responseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminHelpCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseLogoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseQuitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BF3CommandHandler::responseListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket)
}

void BF3CommandHandler::responseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePlayerIsAliveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePlayerPingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseSquadListActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseSquadListPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseSquadPrivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseSquadLeaderCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePunkBusterActivateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsePunkBusterPbSvCommandCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseBanListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListGetRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsServerMessageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsHudCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responsevars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsNameTagCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVars3pCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsBulletDamageCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsUnlockModeCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF3CommandHandler::responseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
