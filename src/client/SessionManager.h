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

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QSet>

class ServerEntry;
class GameWidget;

class SessionManager : public QObject
{
    Q_OBJECT

public:
    SessionManager(QObject *parent = nullptr);
    ~SessionManager();

    static SessionManager *getInstance(QObject *parent = nullptr);

    void openSession(ServerEntry *serverEntry);
    void closeSession(GameWidget *gameWidget);
    void closeSession(int index);
    void closeSession(GameWidget *gameWidget, int index);
    bool isSessionConnected(ServerEntry *serverEntry);

private:
    static SessionManager *instance;

    QSet<ServerEntry*> sessions;

signals:
    void onSessionOpened();
    void onSessionClosed();

};

#endif // SESSIONMANAGER_H
