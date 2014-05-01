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

#ifndef BF3_H
#define BF3_H

#include <QCryptographicHash>

#include "FrostbiteGame.h"
#include "BF3Connection.h"
#include "BF3LevelDictionary.h"

class BF3 : public FrostbiteGame
{
    Q_OBJECT

public:
    explicit BF3(ServerEntry *serverEntry);
    ~BF3();

    virtual Connection *getConnection() { return con; }

protected:
    BF3Connection *con;
    BF3LevelDictionary *levelDictionary;

    bool isAuthenticated();

    /* Commands */

    // Misc
    void sendLoginPlainTextCommand(const QString &password);
    void sendLoginHashedCommand(const QByteArray &salt = 0, const QString &password = 0);
    void sendServerInfoCommand();
    void sendLogoutCommand();
    void sendQuitCommand();
    void sendVersionCommand();
    void sendCurrentLevelCommand();
    void sendListPlayersCommand(const PlayerSubset &playerSubset);

private:
    bool authenticated;

private slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(const bool &auth);
    void onVersionCommand(const QString &type, const int &build);

};

#endif // BF3_H
