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

#include "ServerManager.h"

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Load the stored servers.
    loadServers();
}

ServerManager::~ServerManager()
{
    saveServers();

    delete settings;
}

void ServerManager::loadServers()
{
    settings->beginGroup("ServerManager");
        int size = settings->beginReadArray("Servers");

        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);

            ServerEntry *entry = new ServerEntry(
                settings->value("Game").toInt(),
                settings->value("Name").toString(),
                settings->value("Host").toString(),
                settings->value("Port").toInt(),
                settings->value("Password").toString(),
                settings->value("AutoConnect").toBool()
            );

            serverList.append(entry);
        }

        settings->endArray();
    settings->endGroup();
}

void ServerManager::saveServers()
{
    settings->beginGroup("ServerManager");
        settings->remove("Servers");

        int size = serverList.size();
        settings->beginWriteArray("Servers");
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);

                ServerEntry *entry = serverList.at(i);
                settings->setValue("Game", entry->game);
                settings->setValue("Name", entry->name);
                settings->setValue("Host", entry->host);
                settings->setValue("Port", entry->port);
                settings->setValue("Password", entry->password);
                settings->setValue("AutoConnect", entry->autoConnect);
            }
        settings->endArray();
    settings->endGroup();
}

ServerEntry* ServerManager::getServer(int index)
{
    return serverList.at(index);
}

ServerEntry* ServerManager::getServer(ServerEntry *serverEntry)
{
    return getServer(serverList.indexOf(serverEntry));
}

void ServerManager::setServers(const QList<ServerEntry *> &list)
{
    serverList.clear();
    serverList = list;

    emit (onServerUpdate());
}

QList<ServerEntry *> ServerManager::getServers()
{
    return serverList;
}

QList<ServerEntry *> ServerManager::getServers(int gameIndex)
{
    QList<ServerEntry *> list;

    for (ServerEntry *entry : serverList) {
        if (entry->game == gameIndex) {
            list.append(entry);
        }
    }

    return list;
}

void ServerManager::addServer(ServerEntry *serverEntry)
{
    serverList.append(serverEntry);

    emit (onServerUpdate());
}

void ServerManager::removeServer(int index)
{
    serverList.removeAt(index);

    emit (onServerUpdate());
}

void ServerManager::removeServer(ServerEntry *serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}
