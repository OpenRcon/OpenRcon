/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#include <QMessageBox>

#include "BF3MainWidget.h"
#include "ui_Frostbite2MainWidget.h"
#include "BF3ServerInfo.h"
#include "PlayerInfo.h"
#include "PlayerSubset.h"
#include "TeamEntry.h"
#include "BF3LevelDictionary.h"
#include "FrostbiteUtils.h"

#include "ChatWidget.h"
#include "ReservedSlotsWidget.h"
#include "ConsoleWidget.h"

BF3MainWidget::BF3MainWidget(ServerEntry *serverEntry, QWidget *parent) :
    BF3Widget(new BF3Client(serverEntry, parent), parent),
    ui(new Ui::Frostbite2MainWidget)
{
    ui->setupUi(this);

    chatWidget = new ChatWidget(getClient(), this);
    reservedSlotsWidget = new ReservedSlotsWidget(getClient(), this);
    consoleWidget = new ConsoleWidget(getClient(), commandList, this);

    ui->tabWidget->addTab(chatWidget, QIcon(":/frostbite/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(reservedSlotsWidget, QIcon(":/frostbite/icons/reserved.png"), tr("Reserved Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/frostbite/icons/console.png"), tr("Console"));

    /* Connection */
    connect(getClient()->getConnection(), &Connection::onConnected,    this, &BF3MainWidget::onConnected);
    connect(getClient()->getConnection(), &Connection::onDisconnected, this, &BF3MainWidget::onDisconnected);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (Frostbite2CommandHandler::*)(bool)>(&Frostbite2CommandHandler::onLoginHashedCommand), this, &BF3MainWidget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), static_cast<void (Frostbite2CommandHandler::*)(const BF3ServerInfo&)>(&Frostbite2CommandHandler::onServerInfoCommand), this, &BF3MainWidget::onServerInfoCommand);

    /* User Interface */
}

BF3MainWidget::~BF3MainWidget()
{
    delete ui;
}

void BF3MainWidget::setAuthenticated(bool auth)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), auth);
    //ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), auth);
    //ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ml), auth);
    //ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), auth);

    if (auth) {
        ui->tabWidget->setCurrentIndex(0);
    }

    startupCommands(auth);
}

void BF3MainWidget::startupCommands(bool authenticated)
{
    // Misc
    getClient()->getCommandHandler()->sendVersionCommand();
    getClient()->getCommandHandler()->sendServerInfoCommand();

    if (authenticated) {
        getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);

        // Admins

        // Banning

        // Maplist

        // Player

        // Punkbuster

        // Squad

        // Variables
    } else {
        //client->getCommandHandler()->sendListPlayersCommand(PlayerSubsetType::All);
    }
}

/* Connection */
void BF3MainWidget::onConnected()
{
    setAuthenticated(false);

//    logEvent("Connected", tr("Connected to %1:%2.").arg(con->tcpSocket->peerAddress().toString()).arg(con->tcpSocket->peerPort()));
}

void BF3MainWidget::onDisconnected()
{
//    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */

/* Commands */

// Misc
void BF3MainWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            client->getConnection()->hostDisconnect();
        }
    }
}

void BF3MainWidget::onServerInfoCommand(const BF3ServerInfo &serverInfo)
{
    Q_UNUSED(serverInfo);
}

void BF3MainWidget::onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset)
{

}

// Admin
void BF3MainWidget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset)
{

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

QIcon BF3MainWidget::getRankIcon(int rank) const
{
    return QIcon(QString(":/bf3/ranks/rank_%1.png").arg(rank));
}

/* User Interface */

// Players
void BF3MainWidget::updatePlayerList()
{
    if (client->isAuthenticated()) {
//        commandHandler->sendAdminListPlayersCommand(PlayerSubset::All);
    } else {
        //client->getCommandHandler()->sendListPlayersCommand(PlayerSubsetType::All);
    }
}
