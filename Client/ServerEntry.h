/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#ifndef SERVERENTRY_H
#define SERVERENTRY_H

#include <QString>

struct ServerEntry {
    ServerEntry()
    {

    }

    ServerEntry(int game,
                const QString &name,
                const QString &host,
                int port,
                const QString &password) :
                game(game),
                name(name),
                host(host),
                port(port),
                password(password)
    {

    }

    int game;
    QString name;
    QString host;
    int port;
    QString password;

    bool operator == (const ServerEntry &e) const {
        return (game == e.game && name == e.name && host == e.host && port == e.port && password == e.password);
    }
};

// For use with QVariant
Q_DECLARE_METATYPE(ServerEntry*);

#endif // SERVERENTRY_H
