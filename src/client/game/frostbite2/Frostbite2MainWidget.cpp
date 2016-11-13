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
#include "ui_FrostbiteMainWidget.h"

#include "FrostbiteEventsWidget.h"
#include "FrostbiteChatWidget.h"
#include "FrostbiteBanListWidget.h"
#include "Frostbite2ReservedSlotsWidget.h"
#include "FrostbiteConsoleWidget.h"
#include "Frostbite2ServerInfo.h"
#include "TabWidget.h"
#include "ServerEntry.h"
#include "GameType.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "BF4GameModeEntry.h"
#include "BF3LevelDictionary.h"
#include "BF4LevelDictionary.h"
#include "Time.h"

Frostbite2MainWidget::Frostbite2MainWidget(Frostbite2Client *client, QWidget *parent) :
    FrostbiteMainWidget(client, parent)
{
    /* User Inferface */

    // Create tabs from widgets.
    reservedSlotsWidget = new Frostbite2ReservedSlotsWidget(getClient(), this);
    ui->tabWidget->insertTab(3, reservedSlotsWidget, QIcon(":/frostbite/icons/reserved.png"), tr("Reserved Slots"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), false);
    ui->tabWidget->setCurrentIndex(0);

    /* Events */
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerLevelLoadedEvent,                             &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerMaxPlayerCountChangeEvent,                    &Frostbite2CommandHandler::sendServerInfoCommand);

    /* Commands */
    // Misc

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */
}

Frostbite2MainWidget::~Frostbite2MainWidget()
{

}

/* Connection */
void Frostbite2MainWidget::onConnected()
{

}

void Frostbite2MainWidget::onAuthenticated()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), true);
}

void Frostbite2MainWidget::onDisconnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), false);
}

/* Commands */
// Misc

// Admin

// FairFight

// Player

// Punkbuster

// Squad

// Variables

/* User Interface */
