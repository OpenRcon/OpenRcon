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

#include "BF3MainWidget.h"
#include "ui_FrostbiteMainWidget.h"
#include "BF3Client.h"

#include "FrostbiteEventsWidget.h"
#include "FrostbiteChatWidget.h"
#include "FrostbiteBanListWidget.h"
#include "Frostbite2ReservedSlotsWidget.h"
#include "FrostbiteConsoleWidget.h"

#include "LevelEntry.h"
#include "BF3LevelDictionary.h"
#include "TeamScores.h"
#include "BF3ServerInfo.h"
#include "GameModeEntry.h"
#include "TabWidget.h"
#include "FrostbiteUtils.h"
#include "Time.h"

BF3MainWidget::BF3MainWidget(ServerEntry *serverEntry, QWidget *parent) :
    Frostbite2MainWidget(new BF3Client(serverEntry, parent), parent)
{
    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const BF3ServerInfo&)>(&FrostbiteCommandHandler::onServerInfoCommand),
            this, &BF3MainWidget::onServerInfoCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables
}

BF3MainWidget::~BF3MainWidget()
{

}

/* Commands */
// Misc
void BF3MainWidget::onServerInfoCommand(const BF3ServerInfo &serverInfo)
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
                                              "<td>Punkbuster Server:</td>"
                                              "<td>%9</td>"
                                          "</tr>"
                                      "</table>").arg(serverInfo.getGameIpAndPort())
                                                 .arg(serverInfo.getRegion(),
                                                      serverInfo.getCountry(),
                                                      serverInfo.getClosestPingSite())
                                                 .arg(serverInfo.getPunkBusterVersion()));
}

// Admin

// FairFight

// Player

// Punkbuster

// Squad

// Variables
