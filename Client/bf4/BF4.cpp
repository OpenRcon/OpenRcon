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

#include "BF4.h"

BF4::BF4(ServerEntry *serverEntry) : FrostbiteGame(serverEntry), authenticated(false)
{
    con = new BF4Connection(this);
    con->hostConnect(serverEntry->host, serverEntry->port);

    levelDictionary = new BF4LevelDictionary(this);

    versionMap.insert(70517, "OB-R2");
    versionMap.insert(72879, "OB-R3");
    versionMap.insert(77582, "OB-R4");
    versionMap.insert(87884, "R4");
    versionMap.insert(88031, "R5");
    versionMap.insert(88058, "R6");
    versionMap.insert(88472, "R7");
    versionMap.insert(89702, "R8");
    versionMap.insert(90165, "R9");
    versionMap.insert(90519, "R10");
    versionMap.insert(91697, "R11");
    versionMap.insert(93111, "R12");
    versionMap.insert(94318, "R13");
    versionMap.insert(95851, "R14");
    versionMap.insert(96245, "R15");
    versionMap.insert(97870, "R16");
    versionMap.insert(99392, "R17");
    versionMap.insert(101684, "R18");
    versionMap.insert(102560, "R19");
    versionMap.insert(103064, "R20");
    versionMap.insert(106318, "R21");
    versionMap.insert(106533, "R22");
    versionMap.insert(107145, "R23");
    versionMap.insert(107436, "R24");
    versionMap.insert(108751, "R25");
    versionMap.insert(109758, "R26");
    versionMap.insert(111118, "R27");
    versionMap.insert(112943, "R28");
    versionMap.insert(114240, "R29");
    versionMap.insert(115397, "R30");
    versionMap.insert(117719, "R31");
    versionMap.insert(120511, "R32");
    versionMap.insert(125871, "R33");

    commandList.append("login.plainText ");
    commandList.append("login.hashed");
    commandList.append("login.hashed ");
    commandList.append("serverInfo");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("currentLevel");
    commandList.append("listPlayers ");
    commandList.append("admin.eventsEnabled ");
    commandList.append("admin.help");
    commandList.append("admin.kickPlayer ");
    commandList.append("admin.killPlayer ");
    commandList.append("admin.listPlayers ");
    commandList.append("admin.movePlayer ");
    commandList.append("admin.password ");
    commandList.append("admin.say ");
    commandList.append("admin.shutDown ");
    commandList.append("admin.yell ");
    commandList.append("banList.add ");
    commandList.append("banList.clear");
    commandList.append("banList.list ");
    commandList.append("banList.load");
    commandList.append("banList.remove ");
    commandList.append("banList.save");
    commandList.append("fairFight.activate");
    commandList.append("fairfight.deactivate");
    commandList.append("fairFight.isActive");
    commandList.append("mapList.add ");
    commandList.append("mapList.availableMaps ");
    commandList.append("mapList.clear");
    commandList.append("mapList.endRound ");
    commandList.append("mapList.getMapIndices");
    commandList.append("mapList.getRounds");
    commandList.append("mapList.list ");
    commandList.append("mapList.load");
    commandList.append("mapList.remove ");
    commandList.append("mapList.restartRound");
    commandList.append("mapList.runNextRound");
    commandList.append("mapList.save");
    commandList.append("mapList.setNextMapIndex ");
    commandList.append("player.idleDuration ");
    commandList.append("player.isAlive ");
    commandList.append("player.ping ");
    commandList.append("punkBuster.activate");
    commandList.append("punkBuster.isActive");
    commandList.append("punkBuster.pb_sv_command ");
    commandList.append("reservedSlotsList.add ");
    commandList.append("reservedSlotsList.aggressiveJoin ");
    commandList.append("reservedSlotsList.clear");
    commandList.append("reservedSlotsList.list");
    commandList.append("reservedSlotsList.load");
    commandList.append("reservedSlotsList.remove ");
    commandList.append("reservedSlotsList.save");
    commandList.append("spectatorList.add ");
    commandList.append("spectatorList.clear");
    commandList.append("spectatorList.list");
    commandList.append("spectatorList.remove ");
    commandList.append("spectatorList.save");
    commandList.append("squad.leader ");
    commandList.append("squad.listActive ");
    commandList.append("squad.listPlayers ");
    commandList.append("squad.private ");
    commandList.append("vars.3dSpotting ");
    commandList.append("vars.3pCam ");
    commandList.append("vars.alwaysAllowSpectators ");
    commandList.append("vars.autoBalance ");
    commandList.append("vars.bulletDamage ");
    commandList.append("vars.commander ");
    commandList.append("vars.crossHair ");
    commandList.append("vars.forceReloadWholeMags ");
    commandList.append("vars.friendlyFire ");
    commandList.append("vars.gameModeCounter ");
    commandList.append("vars.gamePassword ");
    commandList.append("vars.hitIndicatorsEnabled ");
    commandList.append("vars.hud ");
    commandList.append("vars.idleBanRounds ");
    commandList.append("vars.idleTimeout ");
    commandList.append("vars.killCam ");
    commandList.append("vars.maxPlayers ");
    commandList.append("vars.maxSpectators ");
    commandList.append("vars.miniMap ");
    commandList.append("vars.miniMapSpotting ");
    commandList.append("vars.mpExperience ");
    commandList.append("vars.nameTag ");
    commandList.append("vars.onlySquadLeaderSpawn ");
    commandList.append("vars.playerRespawnTime ");
    commandList.append("vars.preset ");
    commandList.append("vars.regenerateHealth ");
    commandList.append("vars.roundLockdownCountdown ");
    commandList.append("vars.roundRestartPlayerCount ");
    commandList.append("vars.roundStartPlayerCount ");
    commandList.append("vars.roundTimeLimit ");
    commandList.append("vars.roundWarmupTimeout ");
    commandList.append("vars.serverDescription ");
    commandList.append("vars.serverMessage ");
    commandList.append("vars.serverName ");
    commandList.append("vars.serverType ");
    commandList.append("vars.soldierHealth ");
    commandList.append("vars.team1FactionOverride ");
    commandList.append("vars.team2FactionOverride ");
    commandList.append("vars.team3FactionOverride ");
    commandList.append("vars.team4FactionOverride ");
    commandList.append("vars.teamKillCountForKick ");
    commandList.append("vars.teamKillKickForBan ");
    commandList.append("vars.teamKillValueDecreasePerSecond ");
    commandList.append("vars.teamKillValueForKick ");
    commandList.append("vars.teamKillValueIncrease ");
    commandList.append("vars.unlockMode ");
    commandList.append("vars.vehicleSpawnAllowed ");
    commandList.append("vars.vehicleSpawnDelay ");

    // Connection
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(con->getCommandHandler(), SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));
    connect(con->getCommandHandler(), SIGNAL(onLoginHashedCommand(const bool&)), this, SLOT(onLoginHashedCommand(const bool&)));
    connect(con->getCommandHandler(), SIGNAL(onVersionCommand(const QString&, const int&)), this, SLOT(onVersionCommand(const QString&, const int&)));
}

BF4::~BF4()
{
    delete con;
    delete levelDictionary;
}

void BF4::onConnected()
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        sendLoginHashedCommand();
    }
}

void BF4::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        sendLoginHashedCommand(salt, serverEntry->password);
    }
}

void BF4::onLoginHashedCommand(const bool &auth)
{
    authenticated = auth;
}

void BF4::onVersionCommand(const QString &type, const int &build)
{
    Q_UNUSED(build);

    if (type != "BF4") {
        con->hostDisconnect();

        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

bool BF4::isAuthenticated()
{
    return authenticated;
}

/* Commands */

// Misc
void BF4::sendLoginPlainTextCommand(const QString &password)
{
    con->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void BF4::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        con->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BF4::sendServerInfoCommand()
{
    con->sendCommand("serverInfo");
}

void BF4::sendLogoutCommand()
{
    con->sendCommand("logout");
}

void BF4::sendQuitCommand()
{
    con->sendCommand("quit");
}

void BF4::sendVersionCommand()
{
    con->sendCommand("version");
}

void BF4::sendCurrentLevelCommand()
{
    con->sendCommand("currentLevel");
}

void BF4::sendListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == All) {
        con->sendCommand("\"listPlayers\" \"all\"");
    }
}

// Admin
void BF4::sendAdminEventsEnabledCommand(const bool &enabled)
{
    con->sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendAdminHelpCommand()
{
    con->sendCommand("admin.help");
}

void BF4::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void BF4::sendAdminKillPlayerCommand(const QString &player)
{
    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BF4::sendAdminListPlayersCommand(const PlayerSubset &playerSubset)
{
    if (playerSubset == All) {
        con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BF4::sendAdminMovePlayerCommand(const QString &player, const int &teamId, const int &squadId, const bool &forceKill)
{
    con->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId, squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void BF4::sendAdminPasswordCommand()
{
    con->sendCommand("admin.password");
}

void BF4::sendAdminPasswordCommand(const QString &password)
{
    con->sendCommand(QString("\"admin.password\" \"%1\"").arg(password));
}

void BF4::sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset)
{
    if (playerSubset == All) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(message));
    }
}

void BF4::sendAdminShutdownCommand()
{
    con->sendCommand("admin.shutDown");
}

void BF4::sendAdminShutdownCommand(const bool &graceful)
{
    con->sendCommand(QString("\"admin.shutDown\" \"%1\"").arg(FrostbiteUtils::toString(graceful)));
}

void BF4::sendAdminShutdownCommand(const bool &graceful, const int &seconds)
{
    con->sendCommand(QString("\"admin.shutDown\" \"%1\" \"%2\"").arg(FrostbiteUtils::toString(graceful)).arg(seconds));
}

void BF4::sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset)
{
    sendAdminYellCommand(message, 10, playerSubset);
}

void BF4::sendAdminYellCommand(const QString &message, const int &duration, const PlayerSubset &playerSubset)
{
    if (message.length() <= 256) {
        if (playerSubset == All) {
            con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
        }
    }
}

// Banning
void BF4::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    con->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void BF4::sendBanListAddCommand(const QString &idType, const QString &id, const int &timeout, const bool &useRounds, const QString &reason)
{
    QString timeoutType = useRounds ? "rounds" : "seconds";

    con->sendCommand(QString("banList.add %1 %2 %3 %4 %5").arg(idType, id, timeoutType).arg(FrostbiteUtils::toString(timeout), reason));
    sendBanListListCommand();
}

void BF4::sendBanListClearCommand()
{
    con->sendCommand("banList.clear");
}

void BF4::sendBanListListCommand(const int &index)
{
    if (index == 0) {
        con->sendCommand("banList.list");
    } else {
        con->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void BF4::sendBanListLoadCommand()
{
    con->sendCommand("banList.load");
}

void BF4::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void BF4::sendBanListSaveCommand()
{
    con->sendCommand("banList.save");
}

// FairFight
void BF4::sendFairFightActivateCommand()
{
    con->sendCommand("fairFight.activate");
}

void BF4::sendFairFightDeactivateCommand()
{
    con->sendCommand("fairfight.deactivate");
}

void BF4::sendFairFightIsActiveCommand()
{
    con->sendCommand("fairFight.isActive");
}

// Maplist
void BF4::sendMapListAdd(const QString &level, const QString &gameMode, const int &rounds, const int &offSet)
{
    con->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListList();
}

void BF4::sendMapListAvailableMaps(const QString &filter)
{
    con->sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void BF4::sendMapListClear()
{
    con->sendCommand("mapList.clear");
}

void BF4::sendMapListEndRound(const int &teamId)
{
    con->sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void BF4::sendMapListGetMapIndices()
{
    con->sendCommand("mapList.getMapIndices");
}

void BF4::sendMapListGetRounds()
{
    con->sendCommand("mapList.getRounds");
}

void BF4::sendMapListList(const int &index)
{
    if (index == 0) {
        con->sendCommand("mapList.list");
    } else {
        con->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void BF4::sendMapListLoad()
{
    con->sendCommand("mapList.load");
}

void BF4::sendMapListRemove(const int &index)
{
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
}

void BF4::sendMapListRestartRound()
{
    con->sendCommand("mapList.restartRound");
}

void BF4::sendMapListRunNextRound()
{
    con->sendCommand("mapList.runNextRound");
}

void BF4::sendMapListSave()
{
    con->sendCommand("mapList.save");
}

void BF4::sendMapListSetNextMapIndex(const int &index)
{
    con->sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

void BF4::sendPlayerIdleDuration(const QString &player)
{
    con->sendCommand(QString("\"player.idleDuration\" \"%1\"").arg(player));
}

void BF4::sendPlayerIsAlive(const QString &player)
{
    con->sendCommand(QString("\"player.isAlive\" \"%1\"").arg(player));
}

void BF4::sendPlayerPing(const QString &player)
{
    con->sendCommand(QString("\"player.ping\" \"%1\"").arg(player));
}

// PunkBuster
void BF4::sendPunkBusterActivate()
{
    con->sendCommand("punkBuster.activate");
}

void BF4::sendPunkBusterIsActive()
{
    con->sendCommand("punkBuster.isActive");
}

void BF4::sendPunkBusterPbSvCommand(const QString &command)
{
    con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}

// Reserved Slots
void BF4::sendReservedSlotsListAdd(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4::sendReservedSlotsListAggressiveJoin()
{
    con->sendCommand("reservedSlotsList.aggressiveJoin");
}

void BF4::sendReservedSlotsListAggressiveJoin(const bool &enabled)
{
    con->sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendReservedSlotsListClear()
{
    con->sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListList();
}

void BF4::sendReservedSlotsListList()
{
    con->sendCommand("reservedSlotsList.list");
}

void BF4::sendReservedSlotsListLoad()
{
    con->sendCommand("reservedSlotsList.load");
    sendReservedSlotsListList();
}

void BF4::sendReservedSlotsListRemove(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListList();
}

void BF4::sendReservedSlotsListSave()
{
    con->sendCommand("reservedSlotsList.save");
    sendReservedSlotsListList();
}

// Spectator list
void BF4::sendSpectatorListAdd(const QString &player)
{
    con->sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4::sendSpectatorListClear()
{
    con->sendCommand("spectatorList.clear");
    sendSpectatorListList();
}

void BF4::sendSpectatorListList(const int &index)
{
    if (index == 0) {
        con->sendCommand("spectatorList.list");
    } else {
        con->sendCommand(QString("\"spectatorList.list\" \"%1\"").arg(index));
    }
}

void BF4::sendSpectatorListRemove(const QString &player)
{
    con->sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
    sendSpectatorListList();
}

void BF4::sendSpectatorListSave()
{
    con->sendCommand("spectatorList.save");
    sendSpectatorListList();
}

// Squad
void BF4::sendSquadLeader(const int &teamId, const int &squadId, const QString &player)
{
    con->sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void BF4::sendSquadListActive(const int &teamId)
{
    con->sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void BF4::sendSquadListPlayers(const int &teamId, const int &squadId)
{
    con->sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void BF4::sendSquadPrivate(const int &teamId, const int &squadId, const bool &isPrivate)
{
    con->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}

// Variables
void BF4::sendVars3dSpotting()
{
    con->sendCommand("vars.3dSpotting");
}

void BF4::sendVars3dSpotting(const bool &enabled)
{
    con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVars3pCam()
{
    con->sendCommand("vars.3pCam");
}

void BF4::sendVars3pCam(const bool &enabled)
{
    con->sendCommand(QString("\"vars.3pCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsAlwaysAllowSpectators()
{
    con->sendCommand("vars.alwaysAllowSpectators");
}

void BF4::sendVarsAlwaysAllowSpectators(const bool &enabled)
{
    con->sendCommand(QString("\"vars.alwaysAllowSpectators\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsAutoBalance()
{
    con->sendCommand("vars.autoBalance");
}

void BF4::sendVarsAutoBalance(const bool &enabled)
{
    con->sendCommand(QString("\"vars.autoBalance\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsBulletDamage(const int &damage)
{
    if (damage == -1) {
        con->sendCommand("vars.bulletDamage");
    } else {
        con->sendCommand(QString("\"vars.bulletDamage\" \"%1\"").arg(damage));
    }
}

void BF4::sendVarsCommander()
{
    con->sendCommand("vars.commander");
}

void BF4::sendVarsCommander(const bool &enabled)
{
    con->sendCommand(QString("\"vars.commander\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsForceReloadWholeMags()
{
    con->sendCommand("vars.forceReloadWholeMags");
}

void BF4::sendVarsForceReloadWholeMags(const bool &enabled)
{
    con->sendCommand(QString("\"vars.forceReloadWholeMags\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsFriendlyFire()
{
    con->sendCommand("vars.friendlyFire");
}

void BF4::sendVarsFriendlyFire(const bool &enabled)
{
    con->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsGameModeCounter(const int &scale)
{
    if (scale == -1) {
        con->sendCommand("vars.gameModeCounter");
    } else {
        con->sendCommand(QString("\"vars.gameModeCounter\" \"%1\"").arg(scale));
    }
}

void BF4::sendVarsGamePassword(const QString &password)
{
    if (password == 0) {
        con->sendCommand("vars.gamePassword");
    } else {
        con->sendCommand(QString("\"vars.gamePassword\" \"%1\"").arg(password));
    }
}

void BF4::sendVarsHitIndicatorsEnabled()
{
    con->sendCommand("vars.hitIndicatorsEnabled");
}

void BF4::sendVarsHitIndicatorsEnabled(const bool &enabled)
{
    con->sendCommand(QString("\"vars.hitIndicatorsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsHud()
{
    con->sendCommand("vars.hud");
}

void BF4::sendVarsHud(const bool &enabled)
{
    con->sendCommand(QString("\"vars.hud\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsIdleBanRounds(const int &rounds)
{
    if (rounds == -1) {
        con->sendCommand("vars.idleBanRounds");
    } else {
        con->sendCommand(QString("\"vars.idleBanRounds\" \"%1\"").arg(rounds));
    }
}

void BF4::sendVarsIdleTimeout(const int &seconds)
{
    if (seconds == -1) {
        con->sendCommand("vars.idleTimeout");
    } else {
        con->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(seconds));
    }
}

void BF4::sendVarsKillCam()
{
    con->sendCommand("vars.killCam");
}

void BF4::sendVarsKillCam(const bool &enabled)
{
    con->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsMaxPlayers(const int &players)
{
    if (players == -1) {
        con->sendCommand("vars.maxPlayers");
    } else {
        con->sendCommand(QString("\"vars.maxPlayers\" \"%1\"").arg(players));
    }
}

void BF4::sendVarsMaxSpectators(const int &spectators)
{
    if (spectators == -1) {
        con->sendCommand("vars.maxSpectators");
    } else {
        con->sendCommand(QString("\"vars.maxSpectators\" \"%1\"").arg(spectators));
    }
}

void BF4::sendVarsMiniMap()
{
    con->sendCommand("vars.");
}

void BF4::sendVarsMiniMap(const bool &enabled)
{
    con->sendCommand(QString("\"vars.\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsMiniMapSpotting()
{
    con->sendCommand("vars.miniMap");
}

void BF4::sendVarsMiniMapSpotting(const bool &enabled)
{
    con->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsMpExperience(const QString &experience)
{
    if (experience == 0) {
        con->sendCommand("vars.mpExperience");
    } else {
        con->sendCommand(QString("\"vars.mpExperience\" \"%1\"").arg(experience));
    }
}

void BF4::sendVarsNameTag()
{
    con->sendCommand("vars.nameTag");
}

void BF4::sendVarsNameTag(const bool &enabled)
{
    con->sendCommand(QString("\"vars.nameTag\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsOnlySquadLeaderSpawn()
{
    con->sendCommand("vars.onlySquadLeaderSpawn");
}

void BF4::sendVarsOnlySquadLeaderSpawn(const bool &enabled)
{
    con->sendCommand(QString("\"vars.onlySquadLeaderSpawn\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsPlayerRespawnTime(const int &respawnTime)
{
    if (respawnTime == -1) {
        con->sendCommand("vars.playerRespawnTime");
    } else {
        con->sendCommand(QString("\"vars.playerRespawnTime\" \"%1\"").arg(respawnTime));
    }
}

void BF4::sendVarsPreset(const QString &serverPreset, const bool &lockPresetSetting)
{
    if (serverPreset == 0 && lockPresetSetting == 0) {
        con->sendCommand("vars.preset");
    } else {
        con->sendCommand(QString("\"vars.preset\" \"%1\" \"%2\"").arg(serverPreset, FrostbiteUtils::toString(lockPresetSetting)));
    }
}

void BF4::sendVarsRegenerateHealth()
{
    con->sendCommand("vars.regenerateHealth");
}

void BF4::sendVarsRegenerateHealth(const bool &enabled)
{
    con->sendCommand(QString("\"vars.regenerateHealth\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsRoundLockdownCountdown(const int &seconds)
{
    if (seconds == -1) {
        con->sendCommand("vars.roundLockdownCountdown");
    } else {
        con->sendCommand(QString("\"vars.roundLockdownCountdown\" \"%1\"").arg(seconds));
    }
}

void BF4::sendVarsRoundRestartPlayerCount(const int &players)
{
    if (players == -1) {
        con->sendCommand("vars.roundRestartPlayerCount");
    } else {
        con->sendCommand(QString("\"vars.roundRestartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4::sendVarsRoundStartPlayerCount(const int &players)
{
    if (players == -1) {
        con->sendCommand("vars.roundStartPlayerCount");
    } else {
        con->sendCommand(QString("\"vars.roundStartPlayerCount\" \"%1\"").arg(players));
    }
}

void BF4::sendVarsRoundTimeLimit(const int &percent)
{
    if (percent == -1) {
        con->sendCommand("vars.roundTimeLimit");
    } else {
        con->sendCommand(QString("\"vars.roundTimeLimit\" \"%1\"").arg(percent));
    }
}

void BF4::sendVarsRoundWarmupTimeout(const int &timeout)
{
    if (timeout == -1) {
        con->sendCommand("vars.roundWarmupTimeout");
    } else {
        con->sendCommand(QString("\"vars.roundWarmupTimeout\" \"%1\"").arg(timeout));
    }
}

void BF4::sendVarsServerDescription(const QString &description)
{
    if (description == 0) {
        con->sendCommand("vars.serverDescription");
    } else {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(description));
    }
}

void BF4::sendVarsServerMessage(const QString &message)
{
    if (message == 0) {
        con->sendCommand("vars.serverMessage");
    } else {
        con->sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(message));
    }
}

void BF4::sendVarsServerName(const QString &name)
{
    if (name == 0) {
        con->sendCommand("vars.serverName");
    } else {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(name));
    }
}

void BF4::sendVarsServerType(const QString &type)
{
    if (type == 0) {
        con->sendCommand("vars.serverType");
    } else {
        con->sendCommand(QString("\"vars.serverType\" \"%1\"").arg(type));
    }
}

void BF4::sendVarsSoldierHealth(const int &percent)
{
    if (percent == -1) {
        con->sendCommand("vars.soldierHealth");
    } else {
        con->sendCommand(QString("\"vars.soldierHealth\" \"%1\"").arg(percent));
    }
}

void BF4::sendVarsTeamFactionOverride(const int &teamId, const int &factionId)
{
    if (teamId == -1 && factionId == -1) {
        con->sendCommand("vars.teamFactionOverride");
    } else {
        con->sendCommand(QString("\"vars.teamFactionOverride\" \"%1\" \"%1\"").arg(teamId, factionId));
    }
}

void BF4::sendVarsTeamKillCountForKick(const int &count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillCountForKick");
    } else {
        con->sendCommand(QString("\"vars.teamKillCountForKick\" \"%1\"").arg(count));
    }
}

void BF4::sendVarsTeamKillKickForBan(const int &count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillKickForBan");
    } else {
        con->sendCommand(QString("\"vars.teamKillKickForBan\" \"%1\"").arg(count));
    }
}

void BF4::sendVarsTeamKillValueDecreasePerSecond(const int &count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueDecreasePerSecond");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueDecreasePerSecond\" \"%1\"").arg(count));
    }
}

void BF4::sendVarsTeamKillValueForKick(const int &count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueForKick");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueForKick\" \"%1\"").arg(count));
    }
}

void BF4::sendVarsTeamKillValueIncrease(const int &count)
{
    if (count == -1) {
        con->sendCommand("vars.teamKillValueIncrease");
    } else {
        con->sendCommand(QString("\"vars.teamKillValueIncrease\" \"%1\"").arg(count));
    }
}

void BF4::sendVarsTicketBleedRate(const int &percent)
{
    if (percent == -1) {
        con->sendCommand("vars.ticketBleedRate");
    } else {
        con->sendCommand(QString("\"vars.ticketBleedRate\" \"%1\"").arg(percent));
    }
}

void BF4::sendVarsUnlockMode(const QString &type)
{
    if (type == 0) {
        con->sendCommand("vars.unlockMode");
    } else {
        con->sendCommand(QString("\"vars.unlockMode\" \"%1\"").arg(type));
    }
}

void BF4::sendVarsVehicleSpawnAllowed()
{
    con->sendCommand("vars.vehicleSpawnAllowed");
}

void BF4::sendVarsVehicleSpawnAllowed(const bool &enabled)
{
    con->sendCommand(QString("\"vars.vehicleSpawnAllowed\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4::sendVarsVehicleSpawnDelay(const int &percent)
{
    if (percent == -1) {
        con->sendCommand("vars.vehicleSpawnDelay");
    } else {
        con->sendCommand(QString("\"vars.vehicleSpawnDelay\" \"%1\"").arg(percent));
    }
}
