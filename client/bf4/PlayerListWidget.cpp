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

#include <QApplication>
#include <QMenu>
#include <QAction>

#include "FrostbiteConnection.h"
#include "FrostbiteUtils.h"
#include "LevelEntry.h"
#include "PlayerInfo.h"
#include "PlayerSubset.h"

#include "PlayerListWidget.h"
#include "BF4CommandHandler.h"
#include "BF4LevelDictionary.h"

PlayerListWidget::PlayerListWidget(FrostbiteConnection *connection, QWidget *parent) :
    QTreeWidget(parent),
    connection(connection),
    commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
{
    setFrameShape(Shape::NoFrame);
    setContextMenuPolicy(Qt::CustomContextMenu);

    // Set the columns in headerItem.
    QTreeWidgetItem *item = headerItem();
    item->setText(0, tr("Name"));
    item->setText(1, tr("Squad"));
    item->setText(2, tr("Kills"));
    item->setText(3, tr("Deaths"));
    item->setText(4, tr("Score"));
    item->setText(5, tr("Ping"));
    item->setText(6, tr("GUID"));

    // Players
    clipboard = QApplication::clipboard();
    menu_pl_players = new QMenu(this);
    menu_pl_players_move = new QMenu(tr("Move"), menu_pl_players);
    action_pl_players_kill = new QAction(tr("Kill"), menu_pl_players);
    action_pl_players_kick = new QAction(tr("Kick"), menu_pl_players);
    action_pl_players_ban = new QAction(tr("Ban"), menu_pl_players);
    action_pl_players_reserveSlot = new QAction(tr("Reserve slot"), menu_pl_players);
    menu_pl_players_copyTo = new QMenu(tr("Copy"), menu_pl_players);
    action_pl_players_copyTo_name = new QAction(tr("Name"), menu_pl_players_copyTo);
    action_pl_players_copyTo_guid = new QAction(tr("GUID"), menu_pl_players_copyTo);

    menu_pl_players->addMenu(menu_pl_players_move);
    menu_pl_players->addAction(action_pl_players_kill);
    menu_pl_players->addAction(action_pl_players_kick);
    menu_pl_players->addAction(action_pl_players_ban);
    menu_pl_players->addAction(action_pl_players_reserveSlot);
    menu_pl_players->addMenu(menu_pl_players_copyTo);
    menu_pl_players_copyTo->addAction(action_pl_players_copyTo_name);
    menu_pl_players_copyTo->addAction(action_pl_players_copyTo_guid);

    /* Events */
    connect(commandHandler, SIGNAL(onPlayerAuthenticatedEvent(QString)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerDisconnectEvent(QString)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerJoinEvent(QString, QString)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerLeaveEvent(QString, QString)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerSpawnEvent(QString, int)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerKillEvent(QString, QString, QString, bool)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerSquadChangeEvent(QString, int, int)), this, SLOT(updatePlayerList()));
    connect(commandHandler, SIGNAL(onPlayerTeamChangeEvent(QString, int, int)), this, SLOT(updatePlayerList()));

    /* Commands */
    connect(commandHandler, SIGNAL(onLoginHashedCommand(bool)), this, SLOT(onLoginHashedCommand(bool)));
    connect(commandHandler, SIGNAL(onServerInfoCommand(BF4ServerInfo)), this, SLOT(onServerInfoCommand(BF4ServerInfo)));
    connect(commandHandler, SIGNAL(onAdminListPlayersCommand(QList<PlayerInfo>, PlayerSubset)), this, SLOT(onAdminListPlayersCommand(QList<PlayerInfo>, PlayerSubset)));

    /* User Interface */
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
    connect(action_pl_players_kill, SIGNAL(triggered()), this, SLOT(action_pl_players_kill_triggered()));
    connect(action_pl_players_kick, SIGNAL(triggered()), this, SLOT(action_pl_players_kick_triggered()));
    connect(action_pl_players_ban, SIGNAL(triggered()), this, SLOT(action_pl_players_ban_triggered()));
    connect(action_pl_players_reserveSlot, SIGNAL(triggered()), this, SLOT(action_pl_players_reserveSlot_triggered()));
    connect(action_pl_players_copyTo_name, SIGNAL(triggered()), this, SLOT(action_pl_players_copyTo_name_triggered()));
    connect(action_pl_players_copyTo_guid, SIGNAL(triggered()), this, SLOT(action_pl_players_copyTo_guid_triggered()));

    connect(menu_pl_players_move, SIGNAL(triggered(QAction*)), this, SLOT(menu_pl_players_move_triggered(QAction*)));
}

PlayerListWidget::~PlayerListWidget()
{

}

/* Events */

/* Commands */
void PlayerListWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        commandHandler->sendAdminListPlayersCommand(PlayerSubset::All);
    }
}

void PlayerListWidget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    currentLevel = BF4LevelDictionary::getLevel(serverInfo.currentMap);
}

void PlayerListWidget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        // Clear the QTreeWidget and item.
        clear();
        menu_pl_players_move->clear();

        // Create a list of all players as QTreeWidgetItem's.
        QSet<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        // Create player items and adding them to the list.
        for (PlayerInfo player : playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setData(0, Qt::UserRole, player.teamId);
            playerItem->setIcon(0, getRankIcon(player.rank));
            playerItem->setText(0, player.name);
            playerItem->setData(1, Qt::UserRole, player.squadId);
            playerItem->setText(1, FrostbiteUtils::getSquadName(player.squadId));
            playerItem->setText(2, QString::number(player.kills));
            playerItem->setText(3, QString::number(player.deaths));
            playerItem->setText(4, QString::number(player.score));
            playerItem->setText(5, QString::number(player.ping));
            playerItem->setText(6, player.guid);

            // Add player item and team id to lists.
            playerItems.insert(playerItem);
            teamIds.insert(player.teamId);
        }

        for (int teamId = 0; teamId <= 2; teamId++) {
            TeamEntry team = BF4LevelDictionary::getTeam(teamId == 0 ? 0 : currentLevel.teams.at(teamId - 1));

            // Add teams that contains players.
            if (teamIds.contains(teamId)) {
                QTreeWidgetItem *teamItem = new QTreeWidgetItem(this);
                teamItem->setIcon(0, team.image());
                teamItem->setText(0, team.name);

                for (QTreeWidgetItem *playerItem : playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole).toInt()) {
                        teamItem->addChild(playerItem);
                    }
                }
            }

            // Player cannot be moved to nutrual team.
            if (teamId > 0) {
                // Add the team to the menu_pl_players_move menu.
                action_pl_players_move_team = new QAction(team.image(), tr("Team %1").arg(team.name), menu_pl_players_move);
                action_pl_players_move_team->setData(teamId);

                menu_pl_players_move->addAction(action_pl_players_move_team);
            }
        }

        menu_pl_players_move->addSeparator();

        for (int squadId = 0; squadId <= 8; squadId++) {
            action_pl_players_move_squad = new QAction(tr("Squad %1").arg(FrostbiteUtils::getSquadName(squadId)), menu_pl_players_move);
            action_pl_players_move_squad->setData(squadId + 5);

            menu_pl_players_move->addAction(action_pl_players_move_squad);
        }

        // Expand all player rows
        expandAll();

        // Sort players based on their score.
        sortItems(4, Qt::AscendingOrder);

        // Resize columns so that they fits the content.
        for (int i = 0; i < this->columnCount(); i++) {
            resizeColumnToContents(i);
        }
    }
}

QIcon PlayerListWidget::getRankIcon(int rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

/* User Interface */
void PlayerListWidget::updatePlayerList()
{
    commandHandler->sendAdminListPlayersCommand(PlayerSubset::All);
}

void PlayerListWidget::customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = itemAt(pos);

    if (item && item->parent()) {
        menu_pl_players->exec(QCursor::pos());
    }
}

void PlayerListWidget::action_pl_players_kill_triggered()
{
    QString player = currentItem()->text(0);

    commandHandler->sendAdminKillPlayerCommand(player);
}

void PlayerListWidget::action_pl_players_kick_triggered()
{
    QString player = currentItem()->text(0);

    commandHandler->sendAdminKickPlayerCommand(player, "Kicked by admin.");
}

void PlayerListWidget::action_pl_players_ban_triggered()
{
    QString player = currentItem()->text(0);

    commandHandler->sendBanListAddCommand("perm", player, "Banned by admin.");
}

void PlayerListWidget::action_pl_players_reserveSlot_triggered()
{
    QString player = currentItem()->text(0);

    commandHandler->sendReservedSlotsListAddCommand(player);
}

void PlayerListWidget::action_pl_players_copyTo_name_triggered()
{
    clipboard->setText(currentItem()->text(0));
}

void PlayerListWidget::action_pl_players_copyTo_guid_triggered()
{
    clipboard->setText(currentItem()->text(6));
}

void PlayerListWidget::menu_pl_players_move_triggered(QAction *action)
{
    QTreeWidgetItem *item = currentItem();
    QString player = item->text(0);
    int value = action->data().toInt();
    int teamId, squadId;

    if (value <= 3) {
        teamId = value;
        squadId = item->data(1, Qt::UserRole).toInt();
    } else {
        teamId = item->data(0, Qt::UserRole).toInt();
        squadId = value - 5;
    }

    commandHandler->sendAdminMovePlayerCommand(player, teamId, squadId, true);
}
