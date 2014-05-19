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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QTabWidget>
#include <QDebug>

#include "ConnectionManager.h"
#include "OpenRcon.h"
#include "GameEntry.h"
#include "Game.h"
#include "GameManager.h"
#include "ServerEntry.h"

QSet<ServerEntry *> ConnectionManager::connections;

void ConnectionManager::open(ServerEntry *serverEntry)
{
    if (!connections.contains(serverEntry)) {
        connections.insert(serverEntry);

        GameEntry gameEntry = GameManager::getGame(serverEntry->gameType);
        Game *gameObject = GameManager::getGameObject(serverEntry);
        QTabWidget *tabWidget = OpenRcon::getInstance()->getTabWidget();

        int index = tabWidget->addTab(gameObject, QIcon(gameEntry.icon), serverEntry->name);
        tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->host).arg(serverEntry->port));
        tabWidget->setCurrentIndex(index);
    } else {
        qDebug() << "Another connection to this server already exists.";
    }

    qDebug() << "Session count:" << connections.size();
}

void ConnectionManager::close(int index)
{
    QTabWidget *tabWidget = OpenRcon::getInstance()->getTabWidget();
    Game *game = dynamic_cast<Game *>(tabWidget->widget(index));
    ServerEntry *serverEntry = game->getServerEntry();

    if (connections.contains(serverEntry)) {
        connections.remove(serverEntry);
        tabWidget->removeTab(index);
        game->getConnection()->hostDisconnect();
    } else {
        qDebug() << "Specified connection is not open.";
    }
}
