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

BF4::BF4(const QString &host, const int &port, const QString &password) : BFBaseGame(host, port, password), authenticated(false)
{
    con = new BF4Connection(this);
    con->hostConnect(host, port);

    levels = new BF4Levels(this);

    commandList.append("login.plainText ");
    commandList.append("login.hashed");
    commandList.append("login.hashed ");
    commandList.append("serverinfo");
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
    connect(con->getCommandHandler(), SIGNAL(onVersionCommand(const QString&, const int&, const QString&)), this, SLOT(onVersionCommand(const QString&, const int&, const QString&)));
}

BF4::~BF4()
{
    delete con;
    delete levels;
}

void BF4::onConnected()
{
    if (!isAuthenticated()) {
        con->sendCommand("login.hashed");
    }
}

void BF4::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated()) {
        if (!password.isEmpty()) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BF4::onLoginHashedCommand(const bool &auth)
{
    authenticated = auth;
}

void BF4::onVersionCommand(const QString &type, const int &build, const QString &version)
{
    Q_UNUSED(build);
    Q_UNUSED(version);

    if (type != "BF4") {
        con->hostDisconnect();
        qDebug() << tr("Wrong server type, disconnecting...");
    }
}

bool BF4::isAuthenticated()
{
    return authenticated;
}

void BF4::sendSayMessage(const QString &msg, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg).arg(group));
    } else {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(msg));
    }
}

void BF4::sendYellMessage(const QString &message, const int &duration, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(group));
    } else {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
    }
}
