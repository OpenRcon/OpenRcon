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

#include <QTimer>

#include <QMessageBox>

#include "BF4Widget.h"
#include "ui_BF4Widget.h"
#include "BF4Client.h"

#include "PlayerListWidget.h"
#include "EventsWidget.h"
#include "ChatWidget.h"
#include "BF4OptionsWidget.h"
#include "MapListWidget.h"
#include "BanListWidget.h"
#include "ReservedSlotsWidget.h"
#include "SpectatorSlotsWidget.h"
#include "ConsoleWidget.h"
#include "BF4LevelDictionary.h"
#include "BF4ServerInfo.h"
#include "BF4GameModeEntry.h"
#include "TabWidget.h"
#include "FrostbiteUtils.h"
#include "Time.h"

BF4Widget::BF4Widget(ServerEntry *serverEntry, QWidget *parent) :
    Frostbite2Widget(new BF4Client(serverEntry, parent), parent),
    ui(new Ui::BF4Widget)
{
    ui->setupUi(this);

    /* User Inferface */
    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    connect(timerServerInfoRoundTime, &QTimer::timeout, this, &BF4Widget::updateRoundTime);
    timerServerInfoRoundTime->start(1000);

    timerServerInfoUpTime = new QTimer(this);
    connect(timerServerInfoUpTime, &QTimer::timeout, this, &BF4Widget::updateUpTime);
    timerServerInfoUpTime->start(1000);

    commandList += {
        "login.plainText",
        "login.hashed",
        "serverInfo",
        "logout",
        "quit",
        "version",
        "currentLevel",
        "listPlayers",
        "admin.eventsEnabled",
        "admin.help",
        "admin.kickPlayer",
        "admin.killPlayer",
        "admin.listPlayers",
        "admin.movePlayer",
        "admin.password",
        "admin.say",
        "admin.shutDown",
        "admin.yell",
        "banList.add",
        "banList.clear",
        "banList.list",
        "banList.load",
        "banList.remove",
        "banList.save",
        "fairFight.activate",
        "fairfight.deactivate",
        "fairFight.isActive",
        "mapList.add",
        "mapList.availableMaps",
        "mapList.clear",
        "mapList.endRound",
        "mapList.getMapIndices",
        "mapList.getRounds",
        "mapList.list",
        "mapList.load",
        "mapList.remove",
        "mapList.restartRound",
        "mapList.runNextRound",
        "mapList.save",
        "mapList.setNextMapIndex",
        "player.idleDuration",
        "player.isAlive",
        "player.ping",
        "punkBuster.activate",
        "punkBuster.isActive",
        "punkBuster.pb_sv_command",
        "reservedSlotsList.add",
        "reservedSlotsList.aggressiveJoin",
        "reservedSlotsList.clear",
        "reservedSlotsList.list",
        "reservedSlotsList.load",
        "reservedSlotsList.remove",
        "reservedSlotsList.save",
        "spectatorList.add",
        "spectatorList.clear",
        "spectatorList.list",
        "spectatorList.remove",
        "spectatorList.save",
        "squad.leader",
        "squad.listActive",
        "squad.listPlayers",
        "squad.private",
        "vars.3dSpotting",
        "vars.3pCam",
        "vars.alwaysAllowSpectators",
        "vars.autoBalance",
        "vars.bulletDamage",
        "vars.commander",
        "vars.forceReloadWholeMags",
        "vars.friendlyFire",
        "vars.gameModeCounter",
        "vars.gamePassword",
        "vars.hitIndicatorsEnabled",
        "vars.hud",
        "vars.idleBanRounds",
        "vars.idleTimeout",
        "vars.killCam",
        "vars.maxPlayers",
        "vars.maxSpectators",
        "vars.miniMap",
        "vars.miniMapSpotting",
        "vars.mpExperience",
        "vars.nameTag",
        "vars.onlySquadLeaderSpawn",
        "vars.playerRespawnTime",
        "vars.preset",
        "vars.regenerateHealth",
        "vars.roundLockdownCountdown",
        "vars.roundRestartPlayerCount",
        "vars.roundStartPlayerCount",
        "vars.roundTimeLimit",
        "vars.roundWarmupTimeout",
        "vars.serverDescription",
        "vars.serverMessage",
        "vars.serverName",
        "vars.serverType",
        "vars.soldierHealth",
        "vars.teamFactionOverride",
        "vars.teamKillCountForKick",
        "vars.teamKillKickForBan",
        "vars.teamKillValueDecreasePerSecond",
        "vars.teamKillValueForKick",
        "vars.teamKillValueIncrease",
        "vars.unlockMode",
        "vars.vehicleSpawnAllowed",
        "vars.vehicleSpawnDelay",
        "vars.roundPlayersReadyBypassTimer",
        "vars.roundPlayersReadyMinCount",
        "vars.roundPlayersReadyPercent"
    };

    // Create tabs from widgets.
    playerListWidget = new PlayerListWidget(getClient(), this);
    eventsWidget = new EventsWidget(getClient(), this);
    chatWidget = new ChatWidget(getClient(), this);
    optionsWidget = new BF4OptionsWidget(getClient(), this);
    mapListWidget = new MapListWidget(getClient(), this);
    banListWidget = new BanListWidget(getClient(), this);
    reservedSlotsWidget = new ReservedSlotsWidget(getClient(), this);
    spectatorSlotsWidget = new SpectatorSlotsWidget(getClient(), this);
    consoleWidget = new ConsoleWidget(getClient(), commandList, this);

    ui->tabWidget->addTab(playerListWidget, QIcon(":/frostbite/icons/players.png"), tr("Players"));
    ui->tabWidget->addTab(eventsWidget, QIcon(":/frostbite/icons/events.png"), tr("Events"));
    ui->tabWidget->addTab(chatWidget, QIcon(":/frostbite/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(optionsWidget, QIcon(":/icons/options.png"), tr("Options"));
    ui->tabWidget->addTab(mapListWidget, QIcon(":/frostbite/icons/map.png"), tr("Maplist"));
    ui->tabWidget->addTab(banListWidget, QIcon(":/frostbite/icons/ban.png"), tr("Banlist"));
    ui->tabWidget->addTab(reservedSlotsWidget, QIcon(":/frostbite/icons/reserved.png"), tr("Reserved Slots"));
    ui->tabWidget->addTab(spectatorSlotsWidget, QIcon(":/bf4/icons/spectator.png"), tr("Spectator Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/frostbite/icons/console.png"), tr("Console"));

    /* Connection */
    connect(client->getConnection(), &Connection::onConnected,                          this, &BF4Widget::onConnected);
    connect(client->getConnection(), &Connection::onDisconnected,                       this, &BF4Widget::onDisconnected);

    /* Events */ 
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onServerLevelLoadedEvent,  this, &BF4Widget::onServerLevelLoadedEvent);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this, &BF4Widget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onVersionCommand,   this, &BF4Widget::onVersionCommand);
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const BF4ServerInfo&)>(&FrostbiteCommandHandler::onServerInfoCommand),
            this, &BF4Widget::onServerInfoCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables  
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,   this, &BF4Widget::onVarsAlwaysAllowSpectatorsCommand);

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_runNextRound_clicked);
}

BF4Widget::~BF4Widget()
{
    delete ui;
}

void BF4Widget::setAuthenticated(bool auth)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), auth);
    ui->tabWidget->setCurrentIndex(0);

    startupCommands(auth);
}

void BF4Widget::startupCommands(bool auth)
{
    // Misc
    getClient()->getCommandHandler()->sendVersionCommand();
    getClient()->getCommandHandler()->sendServerInfoCommand();

    if (auth) {
        getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
    }
}

/* Connection */
void BF4Widget::onConnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), true);

    setAuthenticated(false);
}

void BF4Widget::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);

    setAuthenticated(false);
}

/* Events */
void BF4Widget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(levelName);
    Q_UNUSED(gameModeName);
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    getClient()->getCommandHandler()->sendServerInfoCommand();
}

/* Commands */
// Misc
void BF4Widget::onLoginHashedCommand(bool auth)
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

void BF4Widget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText(tr("<b>Version</b>: %1").arg(getClient()->getVersionFromBuild(build)));
    ui->label_si_version->setToolTip(QString::number(build));
}

void BF4Widget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
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
void BF4Widget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), !enabled);
}

/* User Interface */
// ServerInfo
void BF4Widget::pushButton_si_restartRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Restart round"), tr("Are you sure you want to restart the round?"));

    if (ret == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRestartRoundCommand();
    }
}

void BF4Widget::pushButton_si_runNextRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (ret == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRunNextRoundCommand();
    }
}

void BF4Widget::updateRoundTime()
{ 
    ui->label_si_round->setToolTip(FrostbiteUtils::toString(FrostbiteUtils::getTimeFromSeconds(roundTime++)));
}

void BF4Widget::updateUpTime()
{
    ui->label_si_upTime->setText(tr("<b>Uptime:</b> %1").arg(FrostbiteUtils::toString(FrostbiteUtils::getTimeFromSeconds(upTime++))));
}
