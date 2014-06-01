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

#include <QClipboard>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

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
    setDragDropMode(DragDropMode::InternalMove);

    // Set the columns in headerItem.
    QTreeWidgetItem *headerItem = this->headerItem();
    headerItem->setText(0, tr("Name"));
    headerItem->setText(1, tr("Squad"));
    headerItem->setText(2, tr("Kills"));
    headerItem->setText(3, tr("Deaths"));
    headerItem->setText(4, tr("Score"));
    headerItem->setText(5, tr("Ping"));
    headerItem->setText(6, tr("GUID"));

    // Players
    clipboard = QApplication::clipboard();
    menu_pl_players = new QMenu(this);
    menu_pl_players_move = new QMenu(tr("Move to..."), menu_pl_players);
    action_pl_players_kill = new QAction(tr("Kill"), menu_pl_players);
    action_pl_players_kick = new QAction(tr("Kick"), menu_pl_players);
    action_pl_players_ban = new QAction(tr("Ban"), menu_pl_players);
    action_pl_players_reserveSlot = new QAction(tr("Reserve slot"), menu_pl_players);
    menu_pl_players_copyTo = new QMenu(tr("Copy..."), menu_pl_players);
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
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerAuthenticatedEvent, this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &BF4CommandHandler::onPlayerDisconnectEvent,    this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerJoinEvent,          this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerLeaveEvent,         this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSpawnEvent,         this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerKillEvent,          this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSquadChangeEvent,   this, &PlayerListWidget::updatePlayerList);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerTeamChangeEvent,    this, &PlayerListWidget::updatePlayerList);

    /* Commands */
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &PlayerListWidget::onLoginHashedCommand);
    connect(commandHandler, &BF4CommandHandler::onServerInfoCommand,                                                              this, &PlayerListWidget::onServerInfoCommand);
    connect(commandHandler, &BF4CommandHandler::onAdminListPlayersCommand,                                                        this, &PlayerListWidget::onAdminListPlayersCommand);

    /* User Interface */
    connect(this,                          &QTreeWidget::customContextMenuRequested, this, &PlayerListWidget::customContextMenuRequested);
    connect(action_pl_players_kill,        &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_kill_triggered);
    connect(action_pl_players_kick,        &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_kick_triggered);
    connect(action_pl_players_ban,         &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_ban_triggered);
    connect(action_pl_players_reserveSlot, &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_reserveSlot_triggered);
    connect(action_pl_players_copyTo_name, &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_copyTo_name_triggered);
    connect(action_pl_players_copyTo_guid, &QAction::triggered,                      this, &PlayerListWidget::action_pl_players_copyTo_guid_triggered);
    connect(menu_pl_players_move,          &QMenu::triggered,                        this, &PlayerListWidget::menu_pl_players_move_triggered);
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

            // Add teams items.
            if (teamId > 0 || (teamId == 0 && teamIds.contains(teamId))) {
                QTreeWidgetItem *teamItem = new QTreeWidgetItem(this);
                teamItem->setData(0, Qt::UserRole, teamId);
                teamItem->setIcon(0, team.image());
                teamItem->setText(0, team.name);

                // Add players to the teamItem.
                for (QTreeWidgetItem *playerItem : playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole).toInt()) {
                        teamItem->addChild(playerItem);
                    }
                }

                // Add the team to the menu_pl_players_move menu.
                action_pl_players_move_team = new QAction(team.image(), tr("Team %1").arg(team.name), menu_pl_players_move);
                action_pl_players_move_team->setCheckable(true);
                action_pl_players_move_team->setData(teamId);

                menu_pl_players_move->addAction(action_pl_players_move_team);
            }
        }

        menu_pl_players_move->addSeparator();

        for (int squadId = 0; squadId <= 8; squadId++) {
            action_pl_players_move_squad = new QAction(tr("Squad %1").arg(FrostbiteUtils::getSquadName(squadId)), menu_pl_players_move);
            action_pl_players_move_squad->setCheckable(true);
            action_pl_players_move_squad->setData(squadId + 5);

            menu_pl_players_move->addAction(action_pl_players_move_squad);
        }

        // Expand all items.
        expandAll();

        // Resize columns so that they fits the content.
        for (int i = 0; i < columnCount(); i++) {
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
        int teamIndex = item->data(0, Qt::UserRole).toInt();
        int squadIndex = item->data(1, Qt::UserRole).toInt() + topLevelItemCount() + 1;

        for (int index = 0; index < menu_pl_players_move->actions().size(); index++) {
            QAction *action = menu_pl_players_move->actions().at(index);

            // Reset actions so that they're not checked and is enabled.
            if (!action->isEnabled() && action->isChecked()) {
                action->setEnabled(true);
                action->setChecked(false);
            }

            // Set action checked and disabled if index matches squad or team.
            if (index == teamIndex ||
                index == squadIndex) {
                action->setEnabled(false);
                action->setChecked(true);
            }
        }

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

void PlayerListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (currentItem()->parent()) {
        event->accept();
    }
}

void PlayerListWidget::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *currentItem = this->currentItem();

    if (currentItem && currentItem->parent()) {
        QTreeWidgetItem *pointItem = itemAt(event->pos());

        if (pointItem && !pointItem->parent()) {
            QString player = currentItem->text(0);
            int teamId = pointItem->data(0, Qt::UserRole).toInt();
            int squadId = currentItem->data(1, Qt::UserRole).toInt();

            commandHandler->sendAdminMovePlayerCommand(player, teamId, squadId, true);
            QTreeWidget::dropEvent(event);
        }
    }

    event->ignore();
}
