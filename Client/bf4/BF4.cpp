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

    commandList.append("login.plainText");
    commandList.append("login.hashed");
    commandList.append("serverInfo");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("currentLevel");
    commandList.append("listPlayers");
    commandList.append("admin.eventsEnabled");
    commandList.append("admin.help");
    commandList.append("admin.kickPlayer");
    commandList.append("admin.killPlayer");
    commandList.append("admin.listPlayers");
    commandList.append("admin.movePlayer");
    commandList.append("admin.password");
    commandList.append("admin.say");
    commandList.append("admin.shutDown");
    commandList.append("admin.yell");
    commandList.append("banList.add");
    commandList.append("banList.clear");
    commandList.append("banList.list");
    commandList.append("banList.load");
    commandList.append("banList.remove");
    commandList.append("banList.save");
    commandList.append("fairFight.activate");
    commandList.append("fairfight.deactivate");
    commandList.append("fairFight.isActive");
    commandList.append("mapList.add");
    commandList.append("mapList.availableMaps");
    commandList.append("mapList.clear");
    commandList.append("mapList.endRound");
    commandList.append("mapList.getMapIndices");
    commandList.append("mapList.getRounds");
    commandList.append("mapList.list");
    commandList.append("mapList.load");
    commandList.append("mapList.remove");
    commandList.append("mapList.restartRound");
    commandList.append("mapList.runNextRound");
    commandList.append("mapList.save");
    commandList.append("mapList.setNextMapIndex");
    commandList.append("player.idleDuration");
    commandList.append("player.isAlive");
    commandList.append("player.ping");
    commandList.append("punkBuster.activate");
    commandList.append("punkBuster.isActive");
    commandList.append("punkBuster.pb_sv_command");
    commandList.append("reservedSlotsList.add");
    commandList.append("reservedSlotsList.aggressiveJoin");
    commandList.append("reservedSlotsList.clear");
    commandList.append("reservedSlotsList.list");
    commandList.append("reservedSlotsList.load");
    commandList.append("reservedSlotsList.remove");
    commandList.append("reservedSlotsList.save");
    commandList.append("spectatorList.add");
    commandList.append("spectatorList.clear");
    commandList.append("spectatorList.list");
    commandList.append("spectatorList.remove");
    commandList.append("spectatorList.save");
    commandList.append("squad.leader");
    commandList.append("squad.listActive");
    commandList.append("squad.listPlayers");
    commandList.append("squad.private");
    commandList.append("vars.3dSpotting");
    commandList.append("vars.3pCam");
    commandList.append("vars.alwaysAllowSpectators");
    commandList.append("vars.autoBalance");
    commandList.append("vars.bulletDamage");
    commandList.append("vars.commander");
    commandList.append("vars.forceReloadWholeMags");
    commandList.append("vars.friendlyFire");
    commandList.append("vars.gameModeCounter");
    commandList.append("vars.gamePassword");
    commandList.append("vars.hitIndicatorsEnabled");
    commandList.append("vars.hud");
    commandList.append("vars.idleBanRounds");
    commandList.append("vars.idleTimeout");
    commandList.append("vars.killCam");
    commandList.append("vars.maxPlayers");
    commandList.append("vars.maxSpectators");
    commandList.append("vars.miniMap");
    commandList.append("vars.miniMapSpotting");
    commandList.append("vars.mpExperience");
    commandList.append("vars.nameTag");
    commandList.append("vars.onlySquadLeaderSpawn");
    commandList.append("vars.playerRespawnTime");
    commandList.append("vars.preset");
    commandList.append("vars.regenerateHealth");
    commandList.append("vars.roundLockdownCountdown");
    commandList.append("vars.roundRestartPlayerCount");
    commandList.append("vars.roundStartPlayerCount");
    commandList.append("vars.roundTimeLimit");
    commandList.append("vars.roundWarmupTimeout");
    commandList.append("vars.serverDescription");
    commandList.append("vars.serverMessage");
    commandList.append("vars.serverName");
    commandList.append("vars.serverType");
    commandList.append("vars.soldierHealth");
    commandList.append("vars.teamFactionOverride");
    commandList.append("vars.teamKillCountForKick");
    commandList.append("vars.teamKillKickForBan");
    commandList.append("vars.teamKillValueDecreasePerSecond");
    commandList.append("vars.teamKillValueForKick");
    commandList.append("vars.teamKillValueIncrease");
    commandList.append("vars.unlockMode");
    commandList.append("vars.vehicleSpawnAllowed");
    commandList.append("vars.vehicleSpawnDelay");

    // Connection
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(con, SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));
    connect(con, SIGNAL(onLoginHashedCommand(const bool&)), this, SLOT(onLoginHashedCommand(const bool&)));
    connect(con, SIGNAL(onVersionCommand(const QString&, const int&)), this, SLOT(onVersionCommand(const QString&, const int&)));
}

BF4::~BF4()
{
    delete con;
    delete levelDictionary;
}

void BF4::onConnected()
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        con->sendLoginHashedCommand();
    }
}

void BF4::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated() && !serverEntry->password.isEmpty()) {
        con->sendLoginHashedCommand(salt, serverEntry->password);
    }
}

void BF4::onLoginHashedCommand(bool auth)
{
    authenticated = auth;
}

void BF4::onVersionCommand(const QString &type, int build)
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
