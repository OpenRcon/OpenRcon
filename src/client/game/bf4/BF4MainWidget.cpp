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
#include "ui_FrostbiteMainWidget.h"

#include "BF4PlayerListWidget.h"
#include "FrostbiteEventsWidget.h"
#include "FrostbiteChatWidget.h"
#include "BF4OptionsWidget.h"
#include "BF4MapListWidget.h"
#include "FrostbiteBanListWidget.h"
#include "Frostbite2ReservedSlotsWidget.h"
#include "BF4SpectatorSlotsWidget.h"
#include "FrostbiteConsoleWidget.h"

#include "BF4ServerInfo.h"
#include "BF4LevelDictionary.h"
#include "BF4GameModeEntry.h"
#include "TabWidget.h"

BF4MainWidget::BF4MainWidget(ServerEntry *serverEntry, QWidget *parent) :
    Frostbite2MainWidget(new BF4Client(serverEntry, parent), parent)
{
    /* User Inferface */
    // Create tabs from widgets.
    playerListWidget = new BF4PlayerListWidget(getClient(), this);
    optionsWidget = new BF4OptionsWidget(getClient(), this);
    mapListWidget = new BF4MapListWidget(getClient(), this);
    spectatorSlotsWidget = new BF4SpectatorSlotsWidget(getClient(), this);

    ui->tabWidget->insertTab(0, playerListWidget, QIcon(":/frostbite/icons/players.png"), tr("Players"));
    ui->tabWidget->insertTab(3, optionsWidget, QIcon(":/icons/options.png"), tr("Options"));
    ui->tabWidget->insertTab(4, mapListWidget, QIcon(":/frostbite/icons/map.png"), tr("Maplist"));
    ui->tabWidget->insertTab(7, spectatorSlotsWidget, QIcon(":/bf4/icons/spectator.png"), tr("Spectator Slots"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), false);
    ui->tabWidget->setCurrentIndex(0);

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

/* Connection */
void BF4MainWidget::onConnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), true);
}

void BF4MainWidget::onAuthenticated()
{
    getClient()->getCommandHandler()->sendVarsAlwaysAllowSpectatorsCommand();

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), true);
}

void BF4MainWidget::onDisconnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);
}

/* Events */

/* Commands */
// Misc
void BF4MainWidget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    // Update the server information.
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
