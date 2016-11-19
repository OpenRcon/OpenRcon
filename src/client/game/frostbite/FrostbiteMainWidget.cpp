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

#include <QTimer>
#include <QMessageBox>

#include "FrostbiteMainWidget.h"
#include "ui_FrostbiteMainWidget.h"

#include "FrostbiteEventsWidget.h"
#include "FrostbiteChatWidget.h"
#include "FrostbiteBanListWidget.h"
#include "FrostbiteConsoleWidget.h"
#include "TeamScores.h"
#include "FrostbiteServerInfo.h"
#include "TabWidget.h"
#include "ServerEntry.h"
#include "GameType.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "BFBC2LevelEntry.h"
#include "BFBC2LevelDictionary.h"
#include "BF3LevelDictionary.h"
#include "BF4GameModeEntry.h"
#include "BF4LevelDictionary.h"
#include "Time.h"

#include "Frostbite2CommandHandler.h"

FrostbiteMainWidget::FrostbiteMainWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteMainWidget)
{
    ui->setupUi(this);

    /* User Inferface */
    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    timerServerInfoRoundTime->start(1000);

    timerServerInfoUpTime = new QTimer(this);
    timerServerInfoUpTime->start(1000);

    connect(timerServerInfoRoundTime, &QTimer::timeout, this, &FrostbiteMainWidget::updateRoundTime);
    connect(timerServerInfoUpTime,    &QTimer::timeout, this, &FrostbiteMainWidget::updateUpTime);

    // Create tabs from widgets.
    eventsWidget = new FrostbiteEventsWidget(getClient(), this);
    chatWidget = new FrostbiteChatWidget(getClient(), this);
    banListWidget = new FrostbiteBanListWidget(getClient(), this);
    consoleWidget = new FrostbiteConsoleWidget(getClient(), commandList, this);

    ui->tabWidget->addTab(eventsWidget, QIcon(":/frostbite/icons/events.png"), tr("Events"));
    ui->tabWidget->addTab(chatWidget, QIcon(":/frostbite/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(banListWidget, QIcon(":/frostbite/icons/ban.png"), tr("Banlist"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/frostbite/icons/console.png"), tr("Console"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);
    ui->tabWidget->setCurrentIndex(0);

    /* Connection */
    connect(getClient()->getConnection(),     &Connection::onConnected,                      this,                             &FrostbiteMainWidget::onConnected);
    connect(getClient()->getConnection(),     &Connection::onConnected,                      getClient()->getCommandHandler(), &FrostbiteCommandHandler::sendServerInfoCommand);
    connect(getClient()->getConnection(),     &Connection::onDisconnected,                   this,                             &FrostbiteMainWidget::onDisconnected);

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                      this,                             &FrostbiteMainWidget::onAuthenticated);

    /* Events */
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerJoinEvent,                                     &FrostbiteCommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerLeaveEvent,                                    &FrostbiteCommandHandler::sendServerInfoCommand);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this, &FrostbiteMainWidget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const FrostbiteServerInfo&)>(&FrostbiteCommandHandler::onServerInfoCommand),
            this, &FrostbiteMainWidget::onServerInfoCommand);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onVersionCommand,   this,                             &FrostbiteMainWidget::onVersionCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound,   &QPushButton::clicked,                         this,                             &FrostbiteMainWidget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound,   &QPushButton::clicked,                         this,                             &FrostbiteMainWidget::pushButton_si_runNextRound_clicked);
}

FrostbiteMainWidget::~FrostbiteMainWidget()
{
    delete ui;
    delete client;
}

/* Connection */
void FrostbiteMainWidget::onConnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), true);
}

void FrostbiteMainWidget::onAuthenticated()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), true);
}

void FrostbiteMainWidget::onDisconnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);
}

/* Commands */
// Misc
void FrostbiteMainWidget::onLoginHashedCommand(bool authenticated)
{
    if (!authenticated) {
        int result = QMessageBox::warning(0, tr("Error"), tr("Wrong password, make sure you typed in the right password and try again."));

        if (result) {
            client->getConnection()->hostDisconnect();
        }
    }
}

void FrostbiteMainWidget::onServerInfoCommand(const FrostbiteServerInfo &serverInfo)
{
    // Update the title of the this sessions tab.
    TabWidget *tabWidget = TabWidget::getInstance();
    tabWidget->setTabText(tabWidget->indexOf(this), serverInfo.getServerName());

    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    LevelEntry level;
    GameModeEntry gameMode;

    switch (gameType) {
    case GameTypeEnum::BFBC2:
        level = BFBC2LevelDictionary::getLevel(serverInfo.getCurrentMap());
        gameMode = BFBC2LevelDictionary::getGameMode(serverInfo.getGameMode());
        break;

    case GameTypeEnum::BF3:
        level = BF3LevelDictionary::getLevel(serverInfo.getCurrentMap());
        gameMode = BF3LevelDictionary::getGameMode(serverInfo.getGameMode());
        break;

    case GameTypeEnum::BF4:
        level = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
        gameMode = BF4LevelDictionary::getGameMode(serverInfo.getGameMode());
        break;

    default:
        break;
    }

    // Update the roundTime and serverUpTime.
    roundTime = serverInfo.getRoundTime();
    upTime = serverInfo.getServerUpTime();
    updateRoundTime();
    updateUpTime();

    // Update the server information.
    ui->label_si_level->setPixmap(level.getIcon());
    ui->label_si_status->setText(level.getName() + " - " + gameMode.getName());

    // Update the players and round information.
    int roundsPlayed = serverInfo.getRoundsPlayed();

    // Workaround for offset by increment roundPlayed by one for all other games than BFBC2.
    if (gameType != GameTypeEnum::BFBC2) {
        roundsPlayed++;
    }

    ui->label_si_players->setText("<b>" + tr("Players") + "</b>: " + tr("%1 of %2").arg(serverInfo.getPlayerCount()).arg(serverInfo.getMaxPlayerCount()));
    ui->label_si_round->setText("<b>" + tr("Round") + "</b>: " + tr("%1 of %2").arg(roundsPlayed).arg(serverInfo.getRoundsTotal()));
}

void FrostbiteMainWidget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText("<b>" + tr("Version") + "</b>: " + getClient()->getVersionFromBuild(build));
    ui->label_si_version->setToolTip(QString::number(build));
}

// Admin

// FairFight

// Player

// Punkbuster

// Squad

// Variables

/* User Interface */
// ServerInfo
void FrostbiteMainWidget::pushButton_si_restartRound_clicked()
{
    int result = QMessageBox::question(this, tr("Restart round"), tr("Are you sure you want to restart the round?"));

    if (result == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRestartRoundCommand();
    }
}

void FrostbiteMainWidget::pushButton_si_runNextRound_clicked()
{
    int result = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (result == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRunNextRoundCommand();
    }
}

void FrostbiteMainWidget::updateRoundTime()
{
    ui->label_si_round->setToolTip(Time::fromSeconds(roundTime++).toShortString());
}

void FrostbiteMainWidget::updateUpTime()
{
    ui->label_si_upTime->setText("<b>" + tr("Uptime") + "</b>: " + Time::fromSeconds(upTime++).toShortString());
}
