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

#include "FrostbiteEventWidget.h"
#include "ui_FrostbiteEventWidget.h"

#include "BF4CommandHandler.h"
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

FrostbiteEventWidget::FrostbiteEventWidget(Frostbite2Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent),
    ui(new Ui::FrostbiteEventWidget)
{
    ui->setupUi(this);

    /* Connection */
    connect(getClient()->getConnection(),     &Connection::onConnected,                                    this, &FrostbiteEventWidget::onConnected);
    connect(getClient()->getConnection(),     &Connection::onDisconnected,                                 this, &FrostbiteEventWidget::onDisconnected);

    /* Client */
    connect(getClient(),                      &FrostbiteClient::onAuthenticated,                           this, &FrostbiteEventWidget::onAuthenticated);

    /* Events */
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerAuthenticatedEvent,       this, &FrostbiteEventWidget::onPlayerAuthenticatedEvent);

    BF4CommandHandler *bf4CommandHandler = dynamic_cast<BF4CommandHandler*>(getClient()->getCommandHandler());

    if (bf4CommandHandler) {
        connect(bf4CommandHandler,            &BF4CommandHandler::onPlayerDisconnectEvent,                 this, &FrostbiteEventWidget::onPlayerDisconnectEvent);
    }

    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerJoinEvent,                this, &FrostbiteEventWidget::onPlayerJoinEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerLeaveEvent,               this, &FrostbiteEventWidget::onPlayerLeaveEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerSpawnEvent,               this, &FrostbiteEventWidget::onPlayerSpawnEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerKillEvent,                this, &FrostbiteEventWidget::onPlayerKillEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerChatEvent,                this, &FrostbiteEventWidget::onPlayerChatEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerSquadChangeEvent,         this, &FrostbiteEventWidget::onPlayerSquadChangeEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerTeamChangeEvent,          this, &FrostbiteEventWidget::onPlayerTeamChangeEvent);

    Frostbite2CommandHandler *frostbite2CommandHandler = dynamic_cast<Frostbite2CommandHandler*>(getClient()->getCommandHandler());

    if (frostbite2CommandHandler) {
        connect(frostbite2CommandHandler, &Frostbite2CommandHandler::onServerMaxPlayerCountChangeEvent,    this, &FrostbiteEventWidget::onServerMaxPlayerCountChangeEvent);
        connect(frostbite2CommandHandler, &Frostbite2CommandHandler::onServerLevelLoadedEvent,             this, &FrostbiteEventWidget::onServerLevelLoadedEvent);
    }

    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverEvent,           this, &FrostbiteEventWidget::onServerRoundOverEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverPlayersEvent,    this, &FrostbiteEventWidget::onServerRoundOverPlayersEvent);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerRoundOverTeamScoresEvent, this, &FrostbiteEventWidget::onServerRoundOverTeamScoresEvent);
}

FrostbiteEventWidget::~FrostbiteEventWidget()
{
    delete ui;
}

void FrostbiteEventWidget::logEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(message));
    ui->tableWidget->resizeColumnsToContents();
}

/* Connection */
void FrostbiteEventWidget::onConnected(QAbstractSocket *socket)
{
    logEvent(tr("Connected"), tr("Connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
}

void FrostbiteEventWidget::onDisconnected()
{
    logEvent(tr("Disconnected"), tr("Disconnected."));
}

/* Client */
void FrostbiteEventWidget::onAuthenticated()
{
    logEvent(tr("Authenticated"), tr("Authenticated."));

    getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
}

/* Events */
void FrostbiteEventWidget::onPlayerAuthenticatedEvent(const QString &player)
{
    logEvent(tr("PlayerAuthenticated"), tr("Player %1 authenticated.").arg(player));
}

void FrostbiteEventWidget::onPlayerDisconnectEvent(const QString &player)
{
    logEvent(tr("PlayerDisconnect"), tr("Player %1 disconnected.").arg(player));
}

void FrostbiteEventWidget::onPlayerJoinEvent(const QString &player, const QString &guid)
{
    logEvent(tr("PlayerJoin"), tr("Player %1 joined the game (GUID: %2).").arg(player, guid));
}

void FrostbiteEventWidget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent(tr("PlayerLeave"), tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void FrostbiteEventWidget::onPlayerSpawnEvent(const QString &player, int teamId)
{
    logEvent(tr("PlayerSpawn"), tr("Player %1 spawned, and is on team %2.").arg(player).arg(BF4LevelDictionary::getTeam(teamId - 1).getName()));
}

void FrostbiteEventWidget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot)
{
    QString message;
    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    WeaponEntry weaponEntry;

    if (gameType == GameTypeEnum::BF3) {
        weaponEntry = BF3WeaponDictionary::getWeapon(weapon);
    } else if (gameType == GameTypeEnum::BF4) {
        weaponEntry = BF4WeaponDictionary::getWeapon(weapon);
    }

    if (killer != victim) {
        if (headshot) {
            message = tr("Player %1 shot player %2 in the head using %3.").arg(killer).arg(victim).arg(weaponEntry.getName());
        } else {
            message = tr("Player %1 killed player %2 with %3.").arg(killer).arg(victim).arg(weaponEntry.getName());
        }
    } else {
        message = tr("Player %1 commited sucide using %2.").arg(killer).arg(weapon);
    }

    logEvent(tr("PlayerKill"), message);
}

void FrostbiteEventWidget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    Q_UNUSED(target);

    logEvent(tr("PlayerChat"), QString("%1: %2").arg(sender).arg(message));
}

void FrostbiteEventWidget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent(tr("PlayerSquadChange"), tr("Player %1 changed squad to %2.").arg(player).arg(FrostbiteUtils::getSquadName(squadId)));
    }
}

void FrostbiteEventWidget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logEvent(tr("PlayerTeamChange"), tr("Player %1 changed team to %2.").arg(player).arg(teamId));
}

void FrostbiteEventWidget::onServerMaxPlayerCountChangeEvent()
{

}

void FrostbiteEventWidget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    LevelEntry level;
    GameModeEntry gameMode;

    if (gameType == GameTypeEnum::BF3) {
        level = BF3LevelDictionary::getLevel(levelName);
        gameMode = BF3LevelDictionary::getGameMode(gameModeName);
    } else if (gameType == GameTypeEnum::BF4) {
        level = BF4LevelDictionary::getLevel(levelName);
        gameMode = BF4LevelDictionary::getGameMode(gameModeName);
    }

    logEvent(tr("ServerLevelLoaded"), tr("Loading level %1 with gamemode %2.").arg(level.getName()).arg(gameMode.getName()));
}

void FrostbiteEventWidget::onServerRoundOverEvent(int winningTeamId)
{
    logEvent(tr("ServerRoundOver"), tr("The round has just ended, and %1 won.").arg(winningTeamId));
}

void FrostbiteEventWidget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logEvent(tr("ServerRoundOverPlayers"), tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void FrostbiteEventWidget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logEvent(tr("ServerRoundOverTeamScores"), tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores));
}
