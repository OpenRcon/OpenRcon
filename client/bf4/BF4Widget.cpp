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
#include "BF4CommandHandler.h"
#include "BF4LevelDictionary.h"
#include "BF4ServerInfo.h"
#include "BF4GameModeEntry.h"
#include "FrostbiteUtils.h"
#include "Time.h"

#include "PlayerListWidget.h"
#include "EventsWidget.h"
#include "ChatWidget.h"
#include "OptionsWidget.h"
#include "MapListWidget.h"
#include "BanListWidget.h"
#include "ReservedSlotsWidget.h"
#include "SpectatorSlotsWidget.h"
#include "ConsoleWidget.h"

BF4Widget::BF4Widget(ServerEntry *serverEntry) : BF4(serverEntry), ui(new Ui::BF4Widget)
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

    // Create tabs from widgets.
    playerListWidget = new PlayerListWidget(m_connection, this);
    eventsWidget = new EventsWidget(m_connection, this);
    chatWidget = new ChatWidget(m_connection, this);
    optionsWidget = new OptionsWidget(m_connection, this);
    mapListWidget = new MapListWidget(m_connection, this);
    banListWidget = new BanListWidget(m_connection, this);
    reservedSlotsWidget = new ReservedSlotsWidget(m_connection, this);
    spectatorSlotsWidget = new SpectatorSlotsWidget(m_connection, this);
    consoleWidget = new ConsoleWidget(m_connection, commandList, this);

    ui->tabWidget->addTab(playerListWidget, QIcon(":/bf4/icons/players.png"), tr("Players"));
    ui->tabWidget->addTab(eventsWidget, QIcon(":/bf4/icons/events.png"), tr("Events"));
    ui->tabWidget->addTab(chatWidget, QIcon(":/bf4/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(optionsWidget, QIcon(":icons/options.png"), tr("Options"));
    ui->tabWidget->addTab(mapListWidget, tr("Maplist"));
    ui->tabWidget->addTab(banListWidget, tr("Banlist"));
    ui->tabWidget->addTab(reservedSlotsWidget, tr("Reserved Slots"));
    ui->tabWidget->addTab(spectatorSlotsWidget, tr("Spectator Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/icons/console.png"), tr("Console"));

    /* Connection */
    connect(m_connection, &Connection::onConnected,    this, &BF4Widget::onConnected);
    connect(m_connection, &Connection::onDisconnected, this, &BF4Widget::onDisconnected);

    /* Events */ 
    connect(m_commandHandler, &BF4CommandHandler::onServerLevelLoadedEvent, this, &BF4Widget::onServerLevelLoadedEvent);

    /* Commands */
    // Misc
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &BF4Widget::onLoginHashedCommand);
    connect(m_commandHandler, &FrostbiteCommandHandler::onVersionCommand,                                                           this, &BF4Widget::onVersionCommand);
    connect(m_commandHandler, &BF4CommandHandler::onServerInfoCommand,                                                              this, &BF4Widget::onServerInfoCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables  
    connect(m_commandHandler, &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,   this, &BF4Widget::onVarsAlwaysAllowSpectatorsCommand);

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_runNextRound_clicked);
}

BF4Widget::~BF4Widget()
{
    delete ui;

    delete playerListWidget;
    delete eventsWidget;
    delete chatWidget;
    delete optionsWidget;
    delete mapListWidget;
    delete banListWidget;
    delete reservedSlotsWidget;
    delete spectatorSlotsWidget;
    delete consoleWidget;
}

void BF4Widget::setAuthenticated(bool auth)
{
    authenticated = auth;

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(optionsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), auth);

    if (auth) {
        ui->tabWidget->setCurrentWidget(playerListWidget);
    }

    startupCommands(auth);
}

void BF4Widget::startupCommands(bool auth)
{
    // Misc
    m_commandHandler->sendVersionCommand();
    m_commandHandler->sendServerInfoCommand();

    if (auth) {
        m_commandHandler->sendAdminEventsEnabledCommand(true);
    }
}

/* Connection */
void BF4Widget::onConnected()
{
    setAuthenticated(false);
}

void BF4Widget::onDisconnected()
{
    setAuthenticated(false);
}

/* Events */
void BF4Widget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(levelName);
    Q_UNUSED(gameModeName);
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    m_commandHandler->sendServerInfoCommand();
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
            m_connection->hostDisconnect();
        }
    }
}

void BF4Widget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText(tr("<b>Version</b>: %1").arg(getVersionFromBuild(build)));
    ui->label_si_version->setToolTip(QString::number(build));
}

void BF4Widget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.currentMap);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.gameMode);
    roundTime = serverInfo.roundTime;
    upTime = serverInfo.serverUpTime;

    ui->label_si_level->setText(QString("<b>%1</b> - <b>%2</b>").arg(level.name).arg(gameMode.name));

    ui->label_si_level->setToolTip(tr("<table>"
                                          "<tr>"
                                              "<td>External IP address and port:</td>"
                                              "<td>%1</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Join queue enabled:</td>"
                                              "<td>%2</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Matchmaking enabled:</td>"
                                              "<td>%3</td>"
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
                                      "</table>").arg(serverInfo.gameIpAndPort)
                                                 .arg(FrostbiteUtils::toString(serverInfo.joinQueueEnabled),
                                                      FrostbiteUtils::toString(serverInfo.matchMakingEnabled),
                                                      serverInfo.region,
                                                      serverInfo.country,
                                                      serverInfo.closestPingSite)
                                                 .arg(serverInfo.blazePlayerCount)
                                                 .arg(serverInfo.blazeGameState,
                                                      serverInfo.punkBusterVersion));

    ui->label_si_players->setText(tr("<b>Players</b>: %1 of %2").arg(serverInfo.playerCount).arg(serverInfo.maxPlayerCount));
    ui->label_si_round->setText(tr("<b>Round</b>: %1 of %2").arg(serverInfo.roundsPlayed + 1).arg(serverInfo.roundsTotal));
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
        m_commandHandler->sendMapListRestartRoundCommand();
    }
}

void BF4Widget::pushButton_si_runNextRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (ret == QMessageBox::Yes) {
        m_commandHandler->sendMapListRunNextRoundCommand();
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
