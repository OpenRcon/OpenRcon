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

#include "GameManager.h"
#include "ServerManager.h"

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Load the stored servers.
    readSettings();
}

ServerManager::~ServerManager()
{
    writeSettings();

    delete settings;
}

void ServerManager::readSettings()
{
    settings->beginGroup("ServerManager");
        int size = settings->beginReadArray("ServerEntries");

        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);

            ServerEntry *entry = new ServerEntry(
                GameManager::toGameType(settings->value("game").toInt()),
                settings->value("name").toString(),
                settings->value("host").toString(),
                settings->value("port").toInt(),
                settings->value("password").toString(),
                settings->value("autoconnect").toBool()
            );

            serverList.append(entry);
        }

        settings->endArray();
    settings->endGroup();
}

void ServerManager::writeSettings()
{
    settings->beginGroup("ServerManager");
        settings->remove("ServerEntries");

        int size = serverList.size();
        settings->beginWriteArray("ServerEntries");
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);

                ServerEntry *entry = serverList.at(i);
                settings->setValue("game", GameManager::toInt(entry->gameType));
                settings->setValue("name", entry->name);
                settings->setValue("host", entry->host);
                settings->setValue("port", entry->port);
                settings->setValue("password", entry->password);
                settings->setValue("autoconnect", entry->autoConnect);
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
    writeSettings();

    emit (onServerUpdated());
}

QList<ServerEntry *> ServerManager::getServers()
{
    return serverList;
}

QList<ServerEntry *> ServerManager::getServers(GameType gameType)
{
    QList<ServerEntry *> list;

    for (ServerEntry *entry : serverList) {
        if (entry->gameType == gameType) {
            list.append(entry);
        }
    }

    return list;
}

void ServerManager::addServer(ServerEntry *serverEntry)
{
    serverList.append(serverEntry);

    emit (onServerUpdated());
}

void ServerManager::removeServer(int index)
{
    serverList.removeAt(index);

    emit (onServerUpdated());
}

void ServerManager::removeServer(ServerEntry *serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}
