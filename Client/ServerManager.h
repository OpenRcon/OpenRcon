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

#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QSettings>

#include "Constants.h"

#include "ServerEntry.h"

using namespace Constants;

class ServerManager : public QObject
{
    Q_OBJECT

public:
    ServerManager(QObject *parent = nullptr);
    ~ServerManager();

    ServerEntry *getServer(int index);
    ServerEntry *getServer(ServerEntry *serverEntry);
    void setServers(const QList<ServerEntry *> &list);

    QList<ServerEntry *> getServers();
    QList<ServerEntry *> getServers(GameType gameType);

    void addServer(ServerEntry *serverEntry);
    void removeServer(int index);
    void removeServer(ServerEntry *serverEntry);

private:
    QSettings *settings;
    QList<ServerEntry *> serverList;

    void loadServers();
    void saveServers();

signals:
    void onServerUpdate();

};

#endif // SERVERMANAGER_H
