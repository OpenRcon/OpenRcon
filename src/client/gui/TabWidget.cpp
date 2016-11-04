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

#include <QMenu>
#include <QTabBar>

#include "TabWidget.h"
#include "SessionManager.h"
#include "GameWidget.h"
#include "Client.h"
#include "Connection.h"

TabWidget *TabWidget::instance = nullptr;

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDocumentMode(true);
    setTabsClosable(true);
    setMovable(true);

    // Actions
    actionTabConnect = new QAction(tr("Connect"), this);
    actionTabDisconnect = new QAction(tr("Disconnect"), this);

    connect(actionTabConnect,    &QAction::triggered,                     this, &TabWidget::actionTabConnect_triggered);
    connect(actionTabDisconnect, &QAction::triggered,                     this, &TabWidget::actionTabDisconnect_triggered);

    // Menu
    menuTab = new QMenu(this);
    menuTab->addAction(actionTabConnect);
    menuTab->addAction(actionTabDisconnect);

    connect(this,                &QTabWidget::tabCloseRequested,          this, &TabWidget::tabCloseRequested);
    connect(this,                &QTabWidget::customContextMenuRequested, this, &TabWidget::customContextMenuRequested);
}

TabWidget::~TabWidget()
{

}

TabWidget *TabWidget::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new TabWidget(parent);
    }

    return instance;
}

void TabWidget::tabCloseRequested(int index)
{
    SessionManager *sessionManager = SessionManager::getInstance(this);
    sessionManager->closeSession(index);
}

void TabWidget::customContextMenuRequested(const QPoint &pos)
{
    if (tabBar()->tabAt(pos) >= 0) {
        Client *client = dynamic_cast<GameWidget*>(currentWidget())->getClient();
        actionTabConnect->setVisible(!client->getConnection()->isConnected());
        actionTabDisconnect->setVisible(client->getConnection()->isConnected());

        menuTab->exec(QCursor::pos());
    }
}

// Actions
void TabWidget::actionTabConnect_triggered()
{
    Client *client = dynamic_cast<GameWidget*>(currentWidget())->getClient();
    client->connectToHost();
}

void TabWidget::actionTabDisconnect_triggered()
{
    Client *client = dynamic_cast<GameWidget*>(currentWidget())->getClient();
    client->disconnectFromHost();
}
