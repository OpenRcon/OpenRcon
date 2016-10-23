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

#include "BF4Client.h"
#include "FrostbiteUtils.h"
#include "BF4ServerInfo.h"
#include "PlayerInfo.h"
#include "PlayerSubset.h"

#include "PlayerListWidget.h"
#include "TeamEntry.h"
#include "BF4LevelDictionary.h"

PlayerListWidget::PlayerListWidget(BF4Client *client, QWidget *game) :
    QTreeWidget(game),
    client(client)
{
    setFrameShape(Shape::NoFrame);
    setSortingEnabled(true);
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
    menu_player = new QMenu(this);
    menu_player_move = new QMenu(tr("Move to..."), menu_player);
    action_player_kill = new QAction(tr("Kill"), menu_player);
    action_player_kick = new QAction(tr("Kick"), menu_player);
    action_player_ban = new QAction(QIcon(":/frostbite/icons/ban.png"), tr("Ban"), menu_player);
    action_player_reserveSlot = new QAction(QIcon(":/frostbite/icons/reserved.png"), tr("Reserve slot"), menu_player);
    menu_player_copyTo = new QMenu(tr("Copy..."), menu_player);
    menu_player_copyTo->setIcon(QIcon(":/frostbite/icons/copy.png"));
    action_player_copyTo_name = new QAction(tr("Name"), menu_player_copyTo);
    action_player_copyTo_guid = new QAction(tr("GUID"), menu_player_copyTo);

    menu_player->addMenu(menu_player_move);
    menu_player->addAction(action_player_kill);
    menu_player->addAction(action_player_kick);
    menu_player->addAction(action_player_ban);
    menu_player->addAction(action_player_reserveSlot);
    menu_player->addMenu(menu_player_copyTo);
    menu_player_copyTo->addAction(action_player_copyTo_name);
    menu_player_copyTo->addAction(action_player_copyTo_guid);

    /* Events */
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerAuthenticatedEvent,  this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &BF4CommandHandler::onPlayerDisconnectEvent,            this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerJoinEvent,           this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerLeaveEvent,          this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerSpawnEvent,          this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerKillEvent,           this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerSquadChangeEvent,    this, &PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(),           &Frostbite2CommandHandler::onPlayerTeamChangeEvent,     this, &PlayerListWidget::updatePlayerList);

    /* Commands */
    connect(client->getCommandHandler(),           static_cast<void (Frostbite2CommandHandler::*)(bool)>(&Frostbite2CommandHandler::onLoginHashedCommand),
            this, &PlayerListWidget::onLoginHashedCommand);
    connect(client->getCommandHandler(),           &BF4CommandHandler::onServerInfoCommand,                this, &PlayerListWidget::onServerInfoCommand);
    connect(client->getCommandHandler(),           &BF4CommandHandler::onListPlayersCommand,               this, &PlayerListWidget::listPlayers);
    connect(client->getCommandHandler(),           &BF4CommandHandler::onAdminListPlayersCommand,          this, &PlayerListWidget::listPlayers);

    /* User Interface */
    connect(this,                       &QTreeWidget::customContextMenuRequested,               this, &PlayerListWidget::customContextMenuRequested);
    connect(action_player_kill,         &QAction::triggered,                                    this, &PlayerListWidget::action_player_kill_triggered);
    connect(action_player_kick,         &QAction::triggered,                                    this, &PlayerListWidget::action_player_kick_triggered);
    connect(action_player_ban,          &QAction::triggered,                                    this, &PlayerListWidget::action_player_ban_triggered);
    connect(action_player_reserveSlot,  &QAction::triggered,                                    this, &PlayerListWidget::action_player_reserveSlot_triggered);
    connect(action_player_copyTo_name,  &QAction::triggered,                                    this, &PlayerListWidget::action_player_copyTo_name_triggered);
    connect(action_player_copyTo_guid,  &QAction::triggered,                                    this, &PlayerListWidget::action_player_copyTo_guid_triggered);
    connect(menu_player_move,           &QMenu::triggered,                                      this, &PlayerListWidget::menu_player_move_triggered);
}

PlayerListWidget::~PlayerListWidget()
{

}

/* Events */

/* Commands */
void PlayerListWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        client->getCommandHandler()->sendAdminListPlayersCommand(PlayerSubsetType::All);
    }
}

void PlayerListWidget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    currentLevel = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
}

QIcon PlayerListWidget::getRankIcon(int rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

/* User Interface */
void PlayerListWidget::listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubsetType &playerSubsetType)
{
    if (playerSubsetType == PlayerSubsetType::All) {
        // Clear the QTreeWidget and item.
        clear();
        menu_player_move->clear();

        // Create a list of all players as QTreeWidgetItem's.
        QSet<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        // Create player items and adding them to the list.
        for (PlayerInfo player : playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setData(0, Qt::UserRole, player.getTeamId());
            playerItem->setIcon(0, getRankIcon(player.getRank()));
            playerItem->setText(0, player.getName());
            playerItem->setData(1, Qt::UserRole, player.getSquadId());
            playerItem->setText(1, FrostbiteUtils::getSquadName(player.getSquadId()));
            playerItem->setText(2, QString::number(player.getKills()));
            playerItem->setText(3, QString::number(player.getDeaths()));
            playerItem->setText(4, QString::number(player.getScore()));
            playerItem->setText(5, QString::number(player.getPing()));
            playerItem->setText(6, player.getGuid());

            // Add player item and team id to lists.
            playerItems.insert(playerItem);
            teamIds.insert(player.getTeamId());
        }

        for (int teamId = 0; teamId <= 2; teamId++) {
            if (teamId > 0 || (teamId == 0 && teamIds.contains(teamId))) {
                TeamEntry team = BF4LevelDictionary::getTeam(teamId == 0 ? 0 : currentLevel.getTeamList().at(teamId - 1));

                QTreeWidgetItem *teamItem = new QTreeWidgetItem(this);
                teamItem->setData(0, Qt::UserRole, teamId);
                teamItem->setIcon(0, team.getImage());
                teamItem->setText(0, team.getName());

                // Add players to the teamItem.
                for (QTreeWidgetItem *playerItem : playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole).toInt()) {
                        teamItem->addChild(playerItem);
                    }
                }

                // Add the team to the menu_player_move menu.
                action_player_move_team = new QAction(team.getImage(), tr("Team %1").arg(team.getName()), menu_player_move);
                action_player_move_team->setCheckable(true);
                action_player_move_team->setData(teamId);

                menu_player_move->addAction(action_player_move_team);
            }
        }

        menu_player_move->addSeparator();

        for (int squadId = 0; squadId <= 8; squadId++) {
            action_player_move_squad = new QAction(tr("Squad %1").arg(FrostbiteUtils::getSquadName(squadId)), menu_player_move);
            action_player_move_squad->setCheckable(true);
            action_player_move_squad->setData(squadId + 5);

            menu_player_move->addAction(action_player_move_squad);
        }

        // Expand all items.
        expandAll();

        // Resize columns so that they fits the content.
        for (int i = 0; i < columnCount(); i++) {
            resizeColumnToContents(i);
        }
    }
}

void PlayerListWidget::updatePlayerList()
{
    client->getCommandHandler()->sendAdminListPlayersCommand(PlayerSubsetType::All);
}

void PlayerListWidget::customContextMenuRequested(const QPoint &pos)
{
    // Check if we are authenticated.
    if (client->isAuthenticated()) {
        QTreeWidgetItem *item = itemAt(pos);

        if (item && item->parent()) {
            int teamIndex = item->data(0, Qt::UserRole).toInt();
            int squadIndex = item->data(1, Qt::UserRole).toInt() + topLevelItemCount() + 1;

            for (int index = 0; index < menu_player_move->actions().size(); index++) {
                QAction *action = menu_player_move->actions().at(index);

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

            menu_player->exec(QCursor::pos());
        }
    }
}

void PlayerListWidget::action_player_kill_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendAdminKillPlayerCommand(player);
}

void PlayerListWidget::action_player_kick_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendAdminKickPlayerCommand(player, "Kicked by admin.");
}

void PlayerListWidget::action_player_ban_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendBanListAddCommand("perm", player, "Banned by admin.");
}

void PlayerListWidget::action_player_reserveSlot_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendReservedSlotsListAddCommand(player);
}

void PlayerListWidget::action_player_copyTo_name_triggered()
{
    clipboard->setText(currentItem()->text(0));
}

void PlayerListWidget::action_player_copyTo_guid_triggered()
{
    clipboard->setText(currentItem()->text(6));
}

void PlayerListWidget::menu_player_move_triggered(QAction *action)
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

    client->getCommandHandler()->sendAdminMovePlayerCommand(player, teamId, squadId, true);
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

            client->getCommandHandler()->sendAdminMovePlayerCommand(player, teamId, squadId, true);
            QTreeWidget::dropEvent(event);
        }
    }

    event->ignore();
}
