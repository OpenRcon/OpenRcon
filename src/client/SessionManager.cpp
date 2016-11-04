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

SessionManager::SessionManager(QObject *parent) :
    QObject(parent)
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

void SessionManager::openSession(ServerEntry *serverEntry)
{
    // Add ServerEntry to the list.
    if (!sessions.contains(serverEntry)) {
        sessions.insert(serverEntry);

        TabWidget *tabWidget = TabWidget::getInstance();
        GameEntry gameEntry = GameManager::getGame(serverEntry->getGameType());
        GameWidget *gameWidget = GameManager::getGameWidget(serverEntry);

        int index = tabWidget->addTab(gameWidget, QIcon(gameEntry.getIcon()), serverEntry->getName());
        tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->getHost()).arg(serverEntry->getPort()));
        tabWidget->setCurrentIndex(index);

        emit(onSessionOpened());
    } else {
        qDebug() << tr("Already connected to this server.");
    }
}

void SessionManager::closeSession(GameWidget *gameWidget)
{
    int index = TabWidget::getInstance()->indexOf(gameWidget);

    closeSession(gameWidget, index);
}

void SessionManager::closeSession(int index)
{
    GameWidget *gameWidget = dynamic_cast<GameWidget*>(TabWidget::getInstance()->widget(index));

    closeSession(gameWidget, index);
}

void SessionManager::closeSession(GameWidget *gameWidget, int index)
{
    TabWidget *tabWidget = TabWidget::getInstance();
    Client *client = gameWidget->getClient();
    ServerEntry *serverEntry = client->getServerEntry();

    tabWidget->removeTab(index);
    client->getConnection()->hostDisconnect();

    // Remove the ServerEntry from the list.
    if (sessions.remove(serverEntry)) {
        emit(onSessionClosed());
    } else {
        qDebug() << tr("This session does not exist.");
    }

    delete gameWidget;
}

bool SessionManager::isSessionConnected(ServerEntry *serverEntry) const
{
    return sessions.contains(serverEntry);
}
