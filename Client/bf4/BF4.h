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

#ifndef BF4_H
#define BF4_H

#include <QCryptographicHash>

#include "BFBaseGame.h"
#include "BF4Connection.h"
#include "BF4Levels.h"

class BF4 : public BFBaseGame {
    Q_OBJECT

public:
    explicit BF4(const QString &host, const int &port, const QString &password);
    ~BF4();

    virtual Connection *getConnection() { return con; }

protected:
    BF4Connection *con;
    BF4Levels *levels;

    bool isAuthenticated();

    void sendSayMessage(const QString &msg, const QString &group);
    void sendYellMessage(const QString &message, const int &duration, const QString &group);

private:
    bool authenticated;

private slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(const bool &auth);
    void onVersionCommand(const QString &type, const int &build, const QString &version);

};

#endif // BF4_H
