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

#ifndef BFBC2_H
#define BFBC2_H

#include <QTimer>
#include <QCryptographicHash>

#include "Constants.h"

#include "BFBaseGame.h"
#include "BFBC2Connection.h"
#include "BFBC2Levels.h"
#include "BFBC2Constants.h"

using namespace Constants;
using namespace BFBC2Constants;

class BFBC2 : public BFBaseGame
{
    Q_OBJECT

public:
    explicit BFBC2(const QString &host, const int &port, const QString &password);
    ~BFBC2();

    virtual Connection *getConnection() { return con; }

private:
    bool auth;

private slots: 
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand();

    void ingameCommands(const QString &player, const QString &cmd);

    void slotCommandMapListListRounds(QStringList ml);

protected:
    BFBC2Connection *con;
    BFBC2Levels *levels;

    QTimer *commandRefreshTimer;

    QString currentMod;
    QString currentGamemode;
    QStringList gamemodes;
    int nextLevelIndex;
    QStringList mapListU;

    bool isAuthenticated();

    void sendSayMessage(const QString &msg, const QString &group);
    void sendYellMessage(const QString &message, const int &duration, const QString &group);
    void killPlayer(const QString &player);
    void kickPlayer(const QString &player, const QString &reason);
    void banPlayer(const QString &type, const QString &id, const QString &timeout, const QString &reason);
    void unbanPlayer(const QString &type, const QString &id);
    void movePlayer(const QString &player, const QString &teamId, const QString &squadId, const QString &fk);

    QString getMapName(const QString &engineName, const QString &gamemode);
    QPixmap getMapImage(const QString &engineName, const QString &gamemode);
};

#endif // BFBC2_H
