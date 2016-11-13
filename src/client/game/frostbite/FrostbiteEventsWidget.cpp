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

#include <QString>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QAbstractSocket>
#include <QHostAddress>

#include "FrostbiteEventsWidget.h"
#include "ui_FrostbiteEventsWidget.h"

#include "BF4CommandHandler.h"
#include "PlayerSubset.h"
#include "WeaponEntry.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "BF4GameModeEntry.h"
#include "BF3WeaponDictionary.h"
#include "BF3LevelDictionary.h"
#include "BF4WeaponDictionary.h"
#include "BF4LevelDictionary.h"
#include "FrostbiteUtils.h"
#include "ServerEntry.h"
#include "GameType.h"
#include "Squad.h"

FrostbiteEventsWidget::FrostbiteEventsWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteEventsWidget)
{
    ui->setupUi(this);

    /* Connection */
    connect(getClient()->getConnection(),     &Connection::onConnected,                                    this, &FrostbiteEventsWidget::onConnected);
    connect(getClient()->getConnection(),     &Connection::onDisconnected,                                 this, &FrostbiteEventsWidget::onDisconnected);

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                                    this, &FrostbiteEventsWidget::onAuthenticated);

    /* Events */
    Frostbite2CommandHandler *frostbite2CommandHandler = dynamic_cast<Frostbite2CommandHandler*>(getClient()->getCommandHandler());

    if (frostbite2CommandHandler) {
        connect(frostbite2CommandHandler,     &FrostbiteCommandHandler::onPlayerAuthenticatedEvent,       this, &FrostbiteEventsWidget::onPlayerAuthenticatedEvent);
    }

    BF4CommandHandler *bf4CommandHandler = dynamic_cast<BF4CommandHandler*>(getClient()->getCommandHandler());

    if (bf4CommandHandler) {
        connect(bf4CommandHandler,            &BF4CommandHandler::onPlayerDisconnectEvent,                 this, &FrostbiteEventsWidget::onPlayerDisconnectEvent);
    }

    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerJoinEvent,                this, &FrostbiteEventsWidget::onPlayerJoinEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerLeaveEvent,               this, &FrostbiteEventsWidget::onPlayerLeaveEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerSpawnEvent,               this, &FrostbiteEventsWidget::onPlayerSpawnEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerKillEvent,                this, &FrostbiteEventsWidget::onPlayerKillEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerChatEvent,                this, &FrostbiteEventsWidget::onPlayerChatEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerSquadChangeEvent,         this, &FrostbiteEventsWidget::onPlayerSquadChangeEvent);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerTeamChangeEvent,          this, &FrostbiteEventsWidget::onPlayerTeamChangeEvent);

    if (frostbite2CommandHandler) {
        connect(frostbite2CommandHandler, &Frostbite2CommandHandler::onServerMaxPlayerCountChangeEvent,    this, &FrostbiteEventsWidget::onServerMaxPlayerCountChangeEvent);
        connect(frostbite2CommandHandler, &Frostbite2CommandHandler::onServerLevelLoadedEvent,             this, &FrostbiteEventsWidget::onServerLevelLoadedEvent);
    }

    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverEvent,           this, &FrostbiteEventsWidget::onServerRoundOverEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverPlayersEvent,    this, &FrostbiteEventsWidget::onServerRoundOverPlayersEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverTeamScoresEvent, this, &FrostbiteEventsWidget::onServerRoundOverTeamScoresEvent);
}

FrostbiteEventsWidget::~FrostbiteEventsWidget()
{
    delete ui;
}

void FrostbiteEventsWidget::logEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(message));
    ui->tableWidget->resizeColumnsToContents();
}

/* Connection */
void FrostbiteEventsWidget::onConnected(QAbstractSocket *socket)
{
    logEvent("Connected", tr("Connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
}

void FrostbiteEventsWidget::onDisconnected()
{
    logEvent("Disconnected", tr("Disconnected."));
}

/* Client */
void FrostbiteEventsWidget::onAuthenticated()
{
    logEvent("Authenticated", tr("Authenticated."));

    getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
}

/* Events */
void FrostbiteEventsWidget::onPlayerAuthenticatedEvent(const QString &player)
{
    logEvent("PlayerAuthenticated", tr("Player %1 authenticated.").arg(player));
}

void FrostbiteEventsWidget::onPlayerDisconnectEvent(const QString &player)
{
    logEvent("PlayerDisconnect", tr("Player %1 disconnected.").arg(player));
}

void FrostbiteEventsWidget::onPlayerJoinEvent(const QString &player, const QString &guid)
{
    logEvent("PlayerJoin", tr("Player %1 joined the game (GUID: %2).").arg(player, guid));
}

void FrostbiteEventsWidget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent("PlayerLeave", tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void FrostbiteEventsWidget::onPlayerSpawnEvent(const QString &player, int teamId)
{
    logEvent("PlayerSpawn", tr("Player %1 spawned, and is on team %2.").arg(player).arg(BF4LevelDictionary::getTeam(teamId - 1).getName()));
}

void FrostbiteEventsWidget::onPlayerKillEvent(const QString &killerPlayer, const QString &victimPlayer, const QString &weapon, bool headshot)
{
    QString message;
    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    WeaponEntry weaponEntry;

    switch (gameType) {
    case GameTypeEnum::BF3:
        weaponEntry = BF3WeaponDictionary::getWeapon(weapon);
        break;

    case GameTypeEnum::BF4:
        weaponEntry = BF4WeaponDictionary::getWeapon(weapon);
        break;

    default:
        break;
    }

    if (killerPlayer != victimPlayer) {
        if (headshot) {
            message = tr("Player %1 shot player %2 in the head using %3.").arg(killerPlayer).arg(victimPlayer).arg(weaponEntry.getName());
        } else {
            message = tr("Player %1 killed player %2 with %3.").arg(killerPlayer).arg(victimPlayer).arg(weaponEntry.getName());
        }
    } else {
        message = tr("Player %1 commited sucide using %2.").arg(killerPlayer).arg(weapon);
    }

    logEvent("PlayerKill", message);
}

void FrostbiteEventsWidget::onPlayerChatEvent(const QString &sender, const QString &message, const PlayerSubsetEnum &playerSubset)
{
    logEvent("PlayerChat", QString("[%1] %2: %3").arg(PlayerSubset::toString(playerSubset), sender, message));
}

void FrostbiteEventsWidget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent("PlayerSquadChange", tr("Player %1 changed squad to %2.").arg(player).arg(Squad::toString(squadId)));
    }
}

void FrostbiteEventsWidget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logEvent("PlayerTeamChange", tr("Player %1 changed team to %2.").arg(player).arg(teamId));
}

void FrostbiteEventsWidget::onServerMaxPlayerCountChangeEvent()
{

}

void FrostbiteEventsWidget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    LevelEntry level;
    GameModeEntry gameMode;

    switch (gameType) {
    case GameTypeEnum::BF3:
        level = BF3LevelDictionary::getLevel(levelName);
        gameMode = BF3LevelDictionary::getGameMode(gameModeName);
        break;

    case GameTypeEnum::BF4:
        level = BF4LevelDictionary::getLevel(levelName);
        gameMode = BF4LevelDictionary::getGameMode(gameModeName);
        break;

    default:
        break;
    }

    logEvent("ServerLevelLoaded", tr("Loading level %1 with gamemode %2.").arg(level.getName()).arg(gameMode.getName()));
}

void FrostbiteEventsWidget::onServerRoundOverEvent(int winningTeamId)
{
    logEvent("ServerRoundOver", tr("The round has just ended, and %1 won.").arg(winningTeamId));
}

void FrostbiteEventsWidget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logEvent("ServerRoundOverPlayers", tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void FrostbiteEventsWidget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logEvent("ServerRoundOverTeamScores", tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores)); // TODO: Check what this actually outputs.
}
