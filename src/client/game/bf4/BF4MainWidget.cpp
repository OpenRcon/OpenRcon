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

#include "BF4MainWidget.h"
#include "BF4Client.h"
#include "ui_Frostbite2MainWidget.h"

#include "PlayerListWidget.h"
#include "EventsWidget.h"
#include "ChatWidget.h"
#include "BF4OptionsWidget.h"
#include "BF4MapListWidget.h"
#include "BanListWidget.h"
#include "ReservedSlotsWidget.h"
#include "BF4SpectatorSlotsWidget.h"
#include "ConsoleWidget.h"

#include "BF4LevelDictionary.h"
#include "BF4ServerInfo.h"
#include "BF4GameModeEntry.h"
#include "TabWidget.h"
#include "FrostbiteUtils.h"
#include "Time.h"

BF4MainWidget::BF4MainWidget(ServerEntry *serverEntry, QWidget *parent) :
    Frostbite2MainWidget(new BF4Client(serverEntry, parent), parent)
{

    /* User Inferface */
    // Create tabs from widgets.
    playerListWidget = new PlayerListWidget(getClient(), this);
    optionsWidget = new BF4OptionsWidget(getClient(), this);
    mapListWidget = new BF4MapListWidget(getClient(), this);
    spectatorSlotsWidget = new BF4SpectatorSlotsWidget(getClient(), this);

    ui->tabWidget->insertTab(0, playerListWidget, QIcon(":/frostbite/icons/players.png"), tr("Players"));
    ui->tabWidget->insertTab(3, optionsWidget, QIcon(":/icons/options.png"), tr("Options"));
    ui->tabWidget->insertTab(4, mapListWidget, QIcon(":/frostbite/icons/map.png"), tr("Maplist"));
    ui->tabWidget->insertTab(5, spectatorSlotsWidget, QIcon(":/bf4/icons/spectator.png"), tr("Spectator Slots"));

    /* Connection */
    connect(client->getConnection(), &Connection::onConnected,                                     this, &BF4MainWidget::onConnected);
    connect(client->getConnection(), &Connection::onDisconnected,                                  this, &BF4MainWidget::onDisconnected);

    /* Events */

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const BF4ServerInfo&)>(&FrostbiteCommandHandler::onServerInfoCommand),
            this, &BF4MainWidget::onServerInfoCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,   this, &BF4MainWidget::onVarsAlwaysAllowSpectatorsCommand);

    /* User Interface */
}

BF4MainWidget::~BF4MainWidget()
{

}

void BF4MainWidget::setAuthenticated(bool auth)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), auth);
    ui->tabWidget->setCurrentIndex(0);

    startupCommands(auth);
}

void BF4MainWidget::startupCommands(bool auth)
{
    // Misc
    getClient()->getCommandHandler()->sendVersionCommand();
    getClient()->getCommandHandler()->sendServerInfoCommand();

    if (auth) {
        getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
    }
}

/* Connection */
void BF4MainWidget::onConnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), true);

    setAuthenticated(false);
}

void BF4MainWidget::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), false);

    setAuthenticated(false);
}

/* Events */

/* Commands */
// Misc
void BF4MainWidget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.getGameMode());
    roundTime = serverInfo.getRoundTime();
    upTime = serverInfo.getServerUpTime();
    updateRoundTime();
    updateUpTime();

    // Update the title of the this sessions tab.
    TabWidget *tabWidget = TabWidget::getInstance();
    tabWidget->setTabText(tabWidget->indexOf(this), serverInfo.getServerName());

    // Update the server information.
    ui->label_si_level->setPixmap(level.getIcon());
    ui->label_si_status->setText(QString("%1 - %2").arg(level.getName(), gameMode.getName()));
    ui->label_si_status->setToolTip(tr("<table>"
                                          "<tr>"
                                              "<td>External IP address and port:</td>"
                                              "<td>%1</td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td></td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td>Region:</td>"
                                              "<td>%4</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Country:</td>"
                                              "<td>%5</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Closest ping site:</td>"
                                              "<td>%6</td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td></td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td>Blaze player count:</td>"
                                              "<td>%7</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Blaze game stat:</td>"
                                              "<td>%8</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Punkbuster Server:</td>"
                                              "<td>%9</td>"
                                          "</tr>"
                                      "</table>").arg(serverInfo.getGameIpAndPort())
                                                 .arg(serverInfo.getRegion(),
                                                      serverInfo.getCountry(),
                                                      serverInfo.getClosestPingSite())
                                                 .arg(serverInfo.getBlazePlayerCount())
                                                 .arg(serverInfo.getBlazeGameState(),
                                                      serverInfo.getPunkBusterVersion()));

    ui->label_si_players->setText(tr("<b>Players</b>: %1 of %2").arg(serverInfo.getPlayerCount()).arg(serverInfo.getMaxPlayerCount()));
    ui->label_si_round->setText(tr("<b>Round</b>: %1 of %2").arg(serverInfo.getRoundsPlayed() + 1).arg(serverInfo.getRoundsTotal()));
}

// Admin

// FairFight

// Player

// Punkbuster

// Squad

// Variables
void BF4MainWidget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), enabled);
}

/* User Interface */
