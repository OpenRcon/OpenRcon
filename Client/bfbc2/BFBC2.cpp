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

#include "BFBC2.h"

BFBC2::BFBC2(const QString &host, const int &port, const QString &password) : BFBaseGame(host, port, password), auth(false)
{
    con = new BFBC2Connection(this);
    con->hostConnect(host, port);

    levels = new BFBC2Levels(this);

    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand()), this, SLOT(onLoginHashedCommand()));

    // Events
    connect(con->commandHandler, SIGNAL(onPlayerChat(const QString&, const QString&, const QString&)), this, SLOT(ingameCommands(const QString&, const QString&)));
}

BFBC2::~BFBC2()
{
    delete con;
    delete levels;
}

void BFBC2::onConnected()
{
    if (!isAuthenticated()) {
        con->sendCommand("login.hashed");
    }
}

void BFBC2::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated()) {
        if (!password.isEmpty()) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toUtf8().constData());

            con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void BFBC2::onLoginHashedCommand()
{
    auth = true;
}

bool BFBC2::isAuthenticated()
{
    return auth;
}

void BFBC2::ingameCommands(const QString &player, const QString &cmd)
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
            sendYellMessage(cmdList.at(1), 5, "all");
        } else if (command == "!say") {
            sendSayMessage(cmdList.at(1), "all");
        } else if (command == "!move") { // Not finished.
            //con->sendCommand(QString("admin.movePlayer %1").arg(value));
        }
    }
}

void BFBC2::slotCommandMapListListRounds(QStringList ml)
{
    mapListU = ml;
}

void BFBC2::sendSayMessage(const QString &msg, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg).arg(group));
    } else {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(msg));
    }
}

void BFBC2::sendYellMessage(const QString &message, const int &duration, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(group));
    } else {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
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

QString BFBC2::getMapName(const QString &engineName, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelEntry level = levels->getLevel(engineName); // TODO: Mind the gamemode?

        return level.name;
    }

    return QString();
}

QPixmap BFBC2::getMapImage(const QString &engineName, const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelEntry level = levels->getLevel(engineName); // TODO: Mind the gamemode?

        return level.image;
    }

    return QPixmap();
}
