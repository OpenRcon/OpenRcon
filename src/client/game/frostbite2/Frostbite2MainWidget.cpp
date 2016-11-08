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

#include "Frostbite2MainWidget.h"
#include "ui_Frostbite2MainWidget.h"

#include "EventsWidget.h"
#include "ChatWidget.h"
#include "BanListWidget.h"
#include "ReservedSlotsWidget.h"
#include "ConsoleWidget.h"
#include "Time.h"

Frostbite2MainWidget::Frostbite2MainWidget(Frostbite2Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent),
    ui(new Ui::Frostbite2MainWidget)
{
    ui->setupUi(this);

    /* User Inferface */
    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    timerServerInfoRoundTime->start(1000);

    timerServerInfoUpTime = new QTimer(this);
    timerServerInfoUpTime->start(1000);

    connect(timerServerInfoRoundTime, &QTimer::timeout, this, &Frostbite2MainWidget::updateRoundTime);
    connect(timerServerInfoUpTime,    &QTimer::timeout, this, &Frostbite2MainWidget::updateUpTime);

    // Create tabs from widgets.
    eventsWidget = new EventsWidget(getClient(), this);
    chatWidget = new ChatWidget(getClient(), this);
    banListWidget = new BanListWidget(getClient(), this);
    reservedSlotsWidget = new ReservedSlotsWidget(getClient(), this);
    consoleWidget = new ConsoleWidget(getClient(), commandList, this);

    ui->tabWidget->addTab(eventsWidget, QIcon(":/frostbite/icons/events.png"), tr("Events"));
    ui->tabWidget->addTab(chatWidget, QIcon(":/frostbite/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(banListWidget, QIcon(":/frostbite/icons/ban.png"), tr("Banlist"));
    ui->tabWidget->addTab(reservedSlotsWidget, QIcon(":/frostbite/icons/reserved.png"), tr("Reserved Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/frostbite/icons/console.png"), tr("Console"));

    /* Connection */
    connect(client->getConnection(), &Connection::onConnected,                                     this, &Frostbite2MainWidget::onConnected);
    connect(client->getConnection(), &Connection::onDisconnected,                                  this, &Frostbite2MainWidget::onDisconnected);

    /* Events */
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerJoinEvent,        &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerLeaveEvent,       &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerLevelLoadedEvent, &Frostbite2CommandHandler::sendServerInfoCommand);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this, &Frostbite2MainWidget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onVersionCommand,         this, &Frostbite2MainWidget::onVersionCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound, &QPushButton::clicked, this, &Frostbite2MainWidget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound, &QPushButton::clicked, this, &Frostbite2MainWidget::pushButton_si_runNextRound_clicked);
}

Frostbite2MainWidget::~Frostbite2MainWidget()
{
    delete ui;
}

void Frostbite2MainWidget::setAuthenticated(bool auth)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), auth);
    ui->tabWidget->setCurrentIndex(0);

    startupCommands(auth);
}

void Frostbite2MainWidget::startupCommands(bool auth)
{
    // Misc
    getClient()->getCommandHandler()->sendVersionCommand();
    getClient()->getCommandHandler()->sendServerInfoCommand();

    if (auth) {
        getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
    }
}

/* Connection */
void Frostbite2MainWidget::onConnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), true);

    setAuthenticated(false);
}

void Frostbite2MainWidget::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);

    setAuthenticated(false);
}

/* Events */

/* Commands */
// Misc
void Frostbite2MainWidget::onLoginHashedCommand(bool auth)
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

void Frostbite2MainWidget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText(tr("<b>Version</b>: %1").arg(getClient()->getVersionFromBuild(build)));
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
void Frostbite2MainWidget::pushButton_si_restartRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Restart round"), tr("Are you sure you want to restart the round?"));

    if (ret == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRestartRoundCommand();
    }
}

void Frostbite2MainWidget::pushButton_si_runNextRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (ret == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRunNextRoundCommand();
    }
}

void Frostbite2MainWidget::updateRoundTime()
{
    ui->label_si_round->setToolTip(Time::fromSeconds(roundTime++).toShortString());
}

void Frostbite2MainWidget::updateUpTime()
{
    ui->label_si_upTime->setText(tr("<b>Uptime:</b> %1").arg(Time::fromSeconds(upTime++).toShortString()));
}
