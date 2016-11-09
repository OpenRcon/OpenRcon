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
#include <QClipboard>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QList>
#include <QPoint>

#include "BF4PlayerListWidget.h"
#include "Frostbite2Client.h"
#include "ServerEntry.h"
#include "FrostbiteUtils.h"
#include "Frostbite2ServerInfo.h"
#include "Player.h"
#include "PlayerSubset.h"
#include "BanIdType.h"
#include "BanType.h"
#include "TeamEntry.h"
#include "BF4LevelDictionary.h"
#include "BF4CommandHandler.h"

BF4PlayerListWidget::BF4PlayerListWidget(Frostbite2Client *client, QWidget *parent) :
    QTreeWidget(parent),
    client(client)
{
    setFrameShape(Shape::NoFrame);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropMode(DragDropMode::InternalMove);
    setSortingEnabled(true);

    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    connect(timer, &QTimer::timeout, this, &BF4PlayerListWidget::updatePlayerList);

    // Set the columns in headerItem.
    QTreeWidgetItem *headerItem = this->headerItem();
    headerItem->setText(0, tr("Name"));
    headerItem->setText(1, tr("Squad"));
    headerItem->setText(2, tr("Kills"));
    headerItem->setText(3, tr("Deaths"));
    headerItem->setText(4, tr("Score"));

    if (dynamic_cast<BF4CommandHandler*>(client->getCommandHandler())) {
        headerItem->setText(5, tr("Ping"));
    }

    headerItem->setText(6, tr("GUID"));
    headerItem->setText(7, tr("K/D"));

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

    /* Client */
    connect(client,                      &Client::onAuthenticated,                             this, &BF4PlayerListWidget::onAuthenticated);
    connect(client,                      &Client::onAuthenticated,                             this, &BF4PlayerListWidget::updatePlayerList);

    /* Events */
    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onPlayerAuthenticatedEvent, this, &BF4PlayerListWidget::updatePlayerList);

    BF4CommandHandler *bf4CommandHandler = dynamic_cast<BF4CommandHandler*>(client->getCommandHandler());

    if (bf4CommandHandler) {
        connect(bf4CommandHandler,       &BF4CommandHandler::onPlayerDisconnectEvent,          this, &BF4PlayerListWidget::updatePlayerList);
    }

    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onPlayerJoinEvent,          this, &BF4PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onPlayerLeaveEvent,         this, &BF4PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onPlayerSquadChangeEvent,   this, &BF4PlayerListWidget::updatePlayerList);
    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onPlayerTeamChangeEvent,    this, &BF4PlayerListWidget::updatePlayerList);

    /* Commands */
    connect(client->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const Frostbite2ServerInfo&)>(&Frostbite2CommandHandler::onServerInfoCommand),
            this, &BF4PlayerListWidget::onServerInfoCommand);
    connect(client->getCommandHandler(), &Frostbite2CommandHandler::onListPlayersCommand,      this, &BF4PlayerListWidget::onListPlayersCommand);
    connect(client->getCommandHandler(), &Frostbite2CommandHandler::onAdminListPlayersCommand, this, &BF4PlayerListWidget::onListPlayersCommand);

    /* User Interface */
    connect(this,                        &QTreeWidget::customContextMenuRequested,             this, &BF4PlayerListWidget::customContextMenuRequested);
    connect(action_player_kill,          &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_kill_triggered);
    connect(action_player_kick,          &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_kick_triggered);
    connect(action_player_ban,           &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_ban_triggered);
    connect(action_player_reserveSlot,   &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_reserveSlot_triggered);
    connect(action_player_copyTo_name,   &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_copyTo_name_triggered);
    connect(action_player_copyTo_guid,   &QAction::triggered,                                  this, &BF4PlayerListWidget::action_player_copyTo_guid_triggered);
    connect(menu_player_move,            &QMenu::triggered,                                    this, &BF4PlayerListWidget::menu_player_move_triggered);
}

BF4PlayerListWidget::~BF4PlayerListWidget()
{
    delete client;
}

void BF4PlayerListWidget::clear()
{
    menu_player_move->clear();

    QTreeWidget::clear();
}

void BF4PlayerListWidget::resizeColumnsToContents()
{
    // Resize columns so that they fits the content.
    for (int i = 0; i < columnCount(); i++) {
        resizeColumnToContents(i);
    }
}

void BF4PlayerListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QTreeWidgetItem *item = currentItem();

    if (item && item->parent()) {
        event->accept();
    }

    QTreeWidget::dragEnterEvent(event);
}

void BF4PlayerListWidget::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *parentItem = itemAt(event->pos());

    if (parentItem && !parentItem->parent()) {
        QTreeWidgetItem *item = currentItem();

        if (item && item->parent()) {
            // Get the player's name.
            QString playerName = item->text(0);

            // Get the teamId of the team we're moving to.
            int teamId = parentItem->data(0, Qt::UserRole).toInt();

            // Get the current squadId of the player.
            int squadId = item->data(1, Qt::UserRole).toInt();

            // Update the player's teamId with new teamId.
            item->setData(0, Qt::UserRole, teamId);

            client->getCommandHandler()->sendAdminMovePlayerCommand(playerName, teamId, squadId, true);
            event->accept();
        }
    }

    QTreeWidget::dropEvent(event);
}

/* Client */
void BF4PlayerListWidget::onAuthenticated()
{
    client->getCommandHandler()->sendAdminEventsEnabledCommand(true);
}

/* Commands */
void BF4PlayerListWidget::onServerInfoCommand(const Frostbite2ServerInfo &serverInfo)
{
    currentLevel = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
}

void BF4PlayerListWidget::onListPlayersCommand(const QList<Player> &playerList)
{
    // Clear the QTreeWidget and item.
    clear();

    // Create a list of all players as QTreeWidgetItem's.
    QSet<QTreeWidgetItem*> playerItemList;
    QSet<int> teamIdList;

    // Create player items and adding them to the list.
    for (Player player : playerList) {
        QTreeWidgetItem *playerItem = new QTreeWidgetItem();
        playerItem->setData(0, Qt::UserRole, player.getTeamId());
        playerItem->setIcon(0, FrostbiteUtils::getRankIcon(client->getServerEntry()->getGameType(), player.getRank()));
        playerItem->setText(0, player.getName());
        playerItem->setToolTip(0, tr("Rank %1").arg(player.getRank()));
        playerItem->setData(1, Qt::UserRole, player.getSquadId());
        playerItem->setText(1, FrostbiteUtils::getSquadName(player.getSquadId()));
        playerItem->setText(2, QString::number(player.getKills()));
        playerItem->setText(3, QString::number(player.getDeaths()));
        playerItem->setText(4, QString::number(player.getScore()));
        playerItem->setText(5, QString::number(player.getPing()));
        playerItem->setText(6, player.getGuid());
        playerItem->setText(7, QString::number(player.getDeaths() <= 0 ? (double) player.getKills() : (double) player.getKills() / (double) player.getDeaths(), 'f', 2));

        // Add player item and team id to lists.
        playerItemList.insert(playerItem);
        teamIdList.insert(player.getTeamId());
    }

    for (int teamId = 0; teamId <= 2; teamId++) {
        if (teamId > 0 || (teamId == 0 && teamIdList.contains(teamId))) {
            TeamEntry team = BF4LevelDictionary::getTeam(teamId != 0 ? currentLevel.getTeamList().at(teamId - 1) : 0);

            QTreeWidgetItem *teamItem = new QTreeWidgetItem(this);
            teamItem->setData(0, Qt::UserRole, teamId);
            teamItem->setIcon(0, team.getImage());
            teamItem->setText(0, team.getName());

            // Add players to the teamItem.
            for (QTreeWidgetItem *playerItem : playerItemList) {
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

    // Resize columns to content.
    resizeColumnsToContents();
}

/* User Interface */
void BF4PlayerListWidget::customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = itemAt(pos);

    if (item && item->parent()) {
        int teamIndex = item->data(0, Qt::UserRole).toInt() - 1;
        int squadIndex = item->data(1, Qt::UserRole).toInt() + topLevelItemCount() + 1;

        for (int index = 0; index < menu_player_move->actions().length(); index++) {
            QAction *action = menu_player_move->actions().at(index);

            // Reset actions so that they're not checked and is enabled.
            if (!action->isEnabled() && action->isChecked()) {
                action->setEnabled(true);
                action->setChecked(false);
            }

            // Set action checked and disabled if index matches squad or team.
            if (index == teamIndex || index == squadIndex) {
                action->setEnabled(false);
                action->setChecked(true);
            }
        }

        menu_player->exec(QCursor::pos());
    }
}

void BF4PlayerListWidget::action_player_kill_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendAdminKillPlayerCommand(player);
}

void BF4PlayerListWidget::action_player_kick_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendAdminKickPlayerCommand(player);
}

void BF4PlayerListWidget::action_player_ban_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendBanListAddCommand(BanIdTypeEnum::Name, player, BanTypeEnum::Perm);
}

void BF4PlayerListWidget::action_player_reserveSlot_triggered()
{
    QString player = currentItem()->text(0);

    client->getCommandHandler()->sendReservedSlotsListAddCommand(player);
}

void BF4PlayerListWidget::action_player_copyTo_name_triggered()
{
    clipboard->setText(currentItem()->text(0));
}

void BF4PlayerListWidget::action_player_copyTo_guid_triggered()
{
    clipboard->setText(currentItem()->text(6));
}

void BF4PlayerListWidget::menu_player_move_triggered(QAction *action)
{
    QTreeWidgetItem *item = currentItem();
    QString playerName = item->text(0);
    int index = action->data().toInt();
    int teamId, squadId;

    if (index <= 2) {
        qDebug() << "Index is: TeamId: " << index;
        teamId = index;
        squadId = item->data(1, Qt::UserRole).toInt();
    } else if (index >= 3) {
        qDebug() << "Index is: SquadId: " << index;

        teamId = item->data(0, Qt::UserRole).toInt();
        squadId = index - topLevelItemCount() - 3;
    }

    client->getCommandHandler()->sendAdminMovePlayerCommand(playerName, teamId, squadId, true);
}

void BF4PlayerListWidget::updatePlayerList()
{
    if (client->isAuthenticated()) {
        client->getCommandHandler()->sendAdminListPlayersCommand(PlayerSubsetEnum::All);
        client->getCommandHandler()->sendPunkBusterPbSvCommand("pb_sv_plist");
    } else {
        client->getCommandHandler()->sendListPlayersCommand(PlayerSubsetEnum::All);
    }
}
