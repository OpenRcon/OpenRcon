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

#include "Frostbite2Game.h"

Frostbite2Game::Frostbite2Game()
{

}

Frostbite2Game::~Frostbite2Game()
{

}

QIcon Frostbite2Game::getRankIcon(const int &rank)
{
    serverEntry

    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

void Frostbite2Game::listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset, QTreeWidget *treeWidget)
{
    if (playerSubset == All) {
        treeWidget->clear();

        QList<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        foreach (PlayerInfo player, playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setIcon(0, getRankIcon(player.rank));
            playerItem->setText(0, player.name);
            playerItem->setText(1, getSquadName(player.squadId));
            playerItem->setText(2, QString::number(player.kills));
            playerItem->setText(3, QString::number(player.deaths));
            playerItem->setText(4, QString::number(player.score));
            playerItem->setText(5, QString::number(player.ping));
            playerItem->setText(6, player.guid);
            playerItem->setData(0, Qt::UserRole, player.teamId);

            // Add player item and team id to lists.
            playerItems.append(playerItem);
            teamIds.insert(player.teamId);
        }

        foreach (int teamId, teamIds) {
            if (teamId > 0) { // Don't list team with id 0, as this is the neutrual team.
                QTreeWidgetItem *teamItem = new QTreeWidgetItem();
                teamItem->setText(0, levelDictionary->getTeam(teamId - 1));

                foreach (QTreeWidgetItem *playerItem, playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole)) {
                        teamItem->addChild(playerItem);
                    }
                }
            }
        }

        // Expand all player rows
        treeWidget->expandAll();

        // Sort players based on their score.
        treeWidget->sortItems(4, Qt::AscendingOrder);

        // Resize columns so that they fits the content.
        for (int i = 0; i < treeWidget->columnCount(); i++) {
            treeWidget->resizeColumnToContents(i);
        }
    }
}
