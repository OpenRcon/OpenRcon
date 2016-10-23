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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QIcon>
#include <QString>
#include <QDebug>

#include "SessionManager.h"

#include "TabWidget.h"
#include "GameEntry.h"
#include "GameManager.h"
#include "GameWidget.h"
#include "ServerEntry.h"
#include "Connection.h"
#include "Client.h"

SessionManager *SessionManager::instance = nullptr;

SessionManager::SessionManager(QObject *parent) : QObject(parent)
{

}

SessionManager::~SessionManager()
{

}

SessionManager *SessionManager::getInstance(QObject *parent)
{
    if (!instance) {
        instance = new SessionManager(parent);
    }

    return instance;
}

void SessionManager::open(ServerEntry *serverEntry)
{
    // Add ServerEntry to the list.
    if (!sessions.contains(serverEntry)) {
        sessions.insert(serverEntry);

        TabWidget *tabWidget = TabWidget::getInstance();
        GameEntry gameEntry = GameManager::getGame(serverEntry->getGameType());
        GameWidget *gameWidget = GameManager::getGameWidget(serverEntry);
        //Client *client = gameWidget->getClient();
        int index = tabWidget->addTab(gameWidget, QIcon(gameEntry.getIcon()), serverEntry->getName());

        tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->getHost()).arg(serverEntry->getPort()));
        tabWidget->setCurrentIndex(index);
        //client->getConnection()->hostConnect(serverEntry);

        emit (onServerConnected());
    } else {
        qDebug() << "Already connected to this server.";
    }
}
 void SessionManager::close(int index)
{
    TabWidget *tabWidget = TabWidget::getInstance();
    GameWidget *gameWidget = dynamic_cast<GameWidget *>(tabWidget->widget(index));
    Client *client = gameWidget->getClient();

    tabWidget->removeTab(index);
    client->getConnection()->hostDisconnect();

    // Remove the ServerEntry from the list.
    if (sessions.remove(client->getServerEntry())) {
        emit (onServerDisconnected());
    }
}

bool SessionManager::isConnected(ServerEntry *serverEntry)
{
    return sessions.contains(serverEntry);
}
