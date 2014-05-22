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

#include <QCompleter>
#include <QDateTime>

#include "FrostbiteConnection.h"
#include "FrostbiteCommandHandler.h"

#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget),
    connection(connection),
    commandHandler(connection->getCommandHandler())
{
    ui->setupUi(this);

    QStringList commandList;
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

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_co->setCompleter(completer);

    /* Events */
    connect(connection, SIGNAL(onDataSentEvent(QString)), this, SLOT(onDataSentEvent(QString)));
    connect(connection, SIGNAL(onDataReceivedEvent(QString)), this, SLOT(onDataReceivedEvent(QString)));

    /* Commands */
    connect(commandHandler, SIGNAL(onPunkBusterMessageEvent(QString)), this, SLOT(onPunkBusterMessageEvent(QString)));

    /* User Interface */
    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));
}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;

    delete completer;
}

void ConsoleWidget::logConsole(int type, const QString &message)
{
    QString time = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

    switch (type) {
        case 0: // Server send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster con->send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
}

void ConsoleWidget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void ConsoleWidget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

void ConsoleWidget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(2, message);
}

void ConsoleWidget::pushButton_co_co_clicked()
{
    QString command = ui->lineEdit_co_co->text();
    ui->lineEdit_co_co->clear();

    connection->sendCommand(command);
}

void ConsoleWidget::pushButton_co_pb_clicked()
{
    QString command = ui->lineEdit_co_pb->text();
    ui->lineEdit_co_pb->clear();

    commandHandler->sendPunkBusterPbSvCommand(command);
}
