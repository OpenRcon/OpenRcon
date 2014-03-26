/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#include "BFBC2.h"

BFBC2::BFBC2(const QString &host, const int &port, const QString &password) : Game(host, port, password)
{
    con = new BFBC2Connection(this);
    con->hostConnect(host, port);

    gamemodes << "RUSH" << "CONQUEST" << "SQRUSH" << "SQDM";
    levelsObject = 0;

    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));

    connect(con->commandHandler, SIGNAL(onRefresh()), this, SLOT(slotRefreshCommands()));
    //connect(con->commandHandler, SIGNAL(onStartConnection()), this, SLOT(slotStartConnection()));
    //connect(con->commandHandler, SIGNAL(onAuthenticated()), this, SLOT(onAuthenticated()));

    // Events
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const QString&)), this, SLOT(slotEventOnSpawn(const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerChat(const QString&, const QString&)), this, SLOT(slotIngameCommands(const QString&, const QString&)));
}

BFBC2::~BFBC2()
{
    delete con;
    delete levelsObject;
}

void BFBC2::onConnected()
{
    if (!con->isAuthenticated()) {        
        con->sendCommand("\"login.hashed\"");
    }
}

void BFBC2::onLoginHashedCommand(const QByteArray &salt)
{
    if (!con->isAuthenticated()) {
        if (!password.isEmpty()) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toUtf8().constData());

            con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BFBC2::slotRefreshCommands()
{
    con->sendCommand(QString("\"serverInfo\""));
    con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    con->sendCommand(QString("\"mapList.list\""));
    con->sendCommand(QString("\"mapList.nextLevelIndex\""));
    con->sendCommand(QString("\"reservedSlots.list\""));
    con->sendCommand(QString("\"banList.list\""));
}

void BFBC2::slotIngameCommands(const QString &player, const QString &cmd)
{
    QStringList users;

    if (users.contains(player)) {
        QString stringCmd = cmd;
        QStringList cmdList;
        cmdList = stringCmd.replace("&quot;", "\"").split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "");

        QString command = cmdList.first();

        if (command == "!kill") {
            killPlayer(cmdList.at(1));
        } else if (command == "!kick") {
            kickPlayer(cmdList.at(1), 0);
        } else if (command == "!ban") {
            banPlayer("name", cmdList.at(1), "perm", "Banned by administrator.");
        } else if (command == "!unban") {
            unbanPlayer("name", cmdList.at(1));
        } else if (command == "!restartmap") {
            con->sendCommand("\"admin.restartMap\"");
        } else if (command == "!nextmap") {
            con->sendCommand("\"admin.runNextLevel\"");
        } else if (command == "!yell") {
            sendYellMessage(cmdList.at(1), "5", "all", 0, 0);
        } else if (command == "!say") {
            sendSayMessage(cmdList.at(1), "all", 0, 0);
        } else if (command == "!move") { // Not finished.
            //con->sendCommand(QString("admin.movePlayer %1").arg(value));
        }
    }
}

void BFBC2::slotCommandMapListListRounds(QStringList ml)
{
    mapListU = ml;
}

QString BFBC2::getMapName(const QString &mapPath, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelList *levelList = levelsObject->levels().at(gamemodeIndex);
        int mapIndex = levelList->mapPaths().indexOf(QRegExp(mapPath, Qt::CaseInsensitive));

        if (mapIndex != -1) {
            QString mapName = levelList->mapNames ().at(mapIndex);
            return mapName;
        }
    }

    return QString();
}

QString BFBC2::getMapImage(const QString &mapPath, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelList *levelList = levelsObject->levels().at(gamemodeIndex);
        int mapIndex = levelList->mapPaths().indexOf(QRegExp(mapPath, Qt::CaseInsensitive));

        if (mapIndex != -1) {
            QString mapImage = levelList->mapImages().at(mapIndex);
            return mapImage;
        }
    }

    return QString();
}

void BFBC2::sendSayMessage(const QString &msg, const QString &group, const QString &target1, const QString &target2)
{
    if (group == "all") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg, group));
    } else if (group == "team" || "player") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(msg, group, target1));
    } else if (group == "squad") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(msg, group, target1, target2));
    }
}

void BFBC2::sendYellMessage(const QString &msg, const QString &duration, const QString &group, const QString &target1, const QString &target2)
{
    if (group == "all") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(msg, duration, group));
    } else if (group == "team" || "player") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(msg, duration, group, target1));
    } else if (group == "squad") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\" \"%5\"").arg(msg, duration, group, target1, target2));
    }
}

void BFBC2::killPlayer(const QString &player)
{
    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BFBC2::kickPlayer(const QString &player, const QString &reason)
{
    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player).arg(reason));
}

void BFBC2::banPlayer(const QString &type, const QString &id, const QString &timeout, const QString &reason)
{
    // banList.add <id-type, id, timeout, reason> Add player/IP/GUID to ban list for a certain amount of time
    con->sendCommand(QString("\"banList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(type, id, timeout, reason));
}

void BFBC2::unbanPlayer(const QString &type, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(type, id));
}

void BFBC2::movePlayer(const QString &player, const QString &teamId, const QString &squadId, const QString &fk)
{
    if (!player.isEmpty()) {
        con->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player, teamId, squadId, fk));
    }
}

void BFBC2::reserveSlotForPlayer(const QString &player, const bool &action)
{
    if (player.isEmpty()) {
        if (action) {
            con->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
            // TODO: ui->listWidget_rs->addItem(new QListWidgetItem(player, ui->listWidget_rs));
        } else {
            con->sendCommand(QString("\"reservedSlots.removePlayer\" \"%1\"").arg(player));
            // TODO: Remove player from ui->listWidget_rs
        }
    }
}
