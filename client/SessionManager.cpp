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

#include "SessionManager.h"
#include "OpenRcon.h"
#include "ServerEntry.h"
#include "GameEntry.h"
#include "GameManager.h"
#include "Game.h"

SessionManager::SessionManager(QObject *parent) : QObject(parent)
{
    openRcon = dynamic_cast<OpenRcon *>(parent);
}

SessionManager::~SessionManager()
{

}

void SessionManager::open(ServerEntry *serverEntry)
{
    // Add ServerEntry to the list.
    if (!sessions.contains(serverEntry)) {
        sessions.insert(serverEntry);

        QTabWidget *tabWidget = openRcon->getTabWidget();
        GameEntry gameEntry = GameManager::getGame(serverEntry->gameType);
        Game *gameObject = GameManager::getGameObject(serverEntry);
        int index = tabWidget->addTab(gameObject, QIcon(gameEntry.icon), serverEntry->name);

        tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->host).arg(serverEntry->port));
        tabWidget->setCurrentIndex(index);

        emit (onServerConnected());
    } else {
        qDebug() << "Already connected to this server.";
    }
}
 void SessionManager::close(int index)
{
    QTabWidget *tabWidget = openRcon->getTabWidget();
    Game *game = dynamic_cast<Game *>(tabWidget->widget(index));
    ServerEntry *serverEntry = game->getServerEntry();

    tabWidget->removeTab(index);
    game->getConnection()->hostDisconnect();

    // Remove the ServerEntry from the list.
    if (sessions.remove(serverEntry)) {
        emit (onServerConnected());
    }
}

bool SessionManager::isConnected(ServerEntry *serverEntry)
{
    return sessions.contains(serverEntry);
}
