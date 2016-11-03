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

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class ServerEntry;
class Connection;
class CommandHandler;

class Client: public QObject
{
    Q_OBJECT

public:
    Client(ServerEntry *serverEntry, QObject *parent = nullptr);
    virtual ~Client();

    virtual Connection *getConnection() = 0;
    virtual CommandHandler *getCommandHandler() = 0;
    virtual void connectToHost() = 0;
    virtual void disconnectFromHost() = 0;

    ServerEntry *getServerEntry() const;
    bool isAuthenticated() const;
    void setAuthenticated(bool authenticated);

protected:
    ServerEntry *serverEntry;
    bool authenticated;

};

#endif // CLIENT_H
