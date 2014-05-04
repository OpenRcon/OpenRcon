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

#include "BF3Widget.h"

BF3Widget::BF3Widget(ServerEntry *serverEntry) : BF3(serverEntry), ui(new Ui::BF3)
{
    ui->setupUi(this);

    /* Events */
    connect(con, SIGNAL(onDataSentEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));
    connect(con, SIGNAL(onDataReceivedEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));

    /* User Interface */

    // Console
    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));

    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));
}

BF3Widget::~BF3Widget()
{
    delete ui;
}

void BF3Widget::setAuthenticated(const bool &authenticated)
{
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ch), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ml), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_rs), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ss), authenticated);

    startupCommands(authenticated);
}

void BF3Widget::startupCommands(const bool &authenticated)
{
    // Misc
    con->sendVersionCommand();
    con->sendServerInfoCommand();

    if (authenticated) {
//        con->sendAdminEventsEnabledCommand(true);

        // Admins
//        con->sendAdminListPlayersCommand(All);

        // Banning

        // Maplist

        // Player

        // Punkbuster
//        con->sendPunkBusterIsActive();
//        con->sendPunkBusterPbSvCommand("pb_sv_plist");

        // Reserved Slots

        // Spectator list

        // Squad

        // Variables

    } else {
        timerPlayerList->stop();
        connect(timerPlayerList, SIGNAL(timeout()), this, SLOT(updatePlayerList()));
        timerPlayerList->start(1000);
    }
}

void BF3Widget::logConsole(const int &type, const QString &message)
{
    QString time = QTime::currentTime().toString();

    switch (type) {
        case 0: // Server send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
}

/* Connection */
void BF3Widget::onConnected()
{
    setAuthenticated(false);

//    logEvent("Connected", tr("Connected to %1:%2.").arg(con->tcpSocket->peerAddress().toString()).arg(con->tcpSocket->peerPort()));
}

void BF3Widget::onDisconnected()
{
//    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */
void BF3Widget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void BF3Widget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

/* Commands */

// Misc
void BF3Widget::onLoginHashedCommand(const bool &auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            con->hostDisconnect();
        }
    }
}

void BF3Widget::onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Admin
void BF3Widget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Banning

// FairFight

// Maplist

// Player

// Punkbuster

// Reserved Slots

// Spectator list

// Squad

// Variables

QIcon BF3Widget::getRankIcon(const int &rank)
{
    return QIcon(QString(":/bf3/ranks/rank_%1.png").arg(rank));
}

/* User Interface */

// Players
void BF3Widget::updatePlayerList()
{
    if (isAuthenticated()) {
//        con->sendAdminListPlayersCommand(All);
    } else {
        con->sendListPlayersCommand(PlayerSubset::All);
    }
}

void BF3Widget::listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        ui->treeWidget_pl_players->clear();

        QList<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        foreach (PlayerInfo player, playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setIcon(0, getRankIcon(player.rank));
            playerItem->setText(0, player.name);
            playerItem->setText(1, getSquadName(player.squadId));
            playerItem->setText(2, QString::number(player.kills));
            playerItem->setText(3, QString::number(player.deaths));
            playerItem->setText(4, QString::number(player.score));
            playerItem->setText(5, QString::number(player.ping));
            playerItem->setText(6, player.guid);
            playerItem->setData(0, Qt::UserRole, player.teamId);

            // Add player item and team id to lists.
            playerItems.append(playerItem);
            teamIds.insert(player.teamId);
        }

        foreach (int teamId, teamIds) {
            if (teamId > 0) { // Don't list team with id 0, as this is the neutrual team.
                QTreeWidgetItem *teamItem = new QTreeWidgetItem(ui->treeWidget_pl_players);
                teamItem->setText(0, levelDictionary->getTeam(teamId - 1));

                foreach (QTreeWidgetItem *playerItem, playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole)) {
                        teamItem->addChild(playerItem);
                    }
                }
            }
        }

        // Expand all player rows
        ui->treeWidget_pl_players->expandAll();

        // Sort players based on their score.
        ui->treeWidget_pl_players->sortItems(4, Qt::AscendingOrder);

        // Resize columns so that they fits the content.
        for (int i = 0; i < ui->treeWidget_pl_players->columnCount(); i++) {
            ui->treeWidget_pl_players->resizeColumnToContents(i);
        }
    }
}

// Console
void BF3Widget::pushButton_co_co_clicked()
{
    QString command = ui->lineEdit_co_co->text();
    ui->lineEdit_co_co->clear();

    con->sendCommand(command);
}

void BF3Widget::pushButton_co_pb_clicked()
{
    QString command = ui->lineEdit_co_pb->text();
    ui->lineEdit_co_pb->clear();

    con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}
