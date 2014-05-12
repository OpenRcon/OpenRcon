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

#include "FrostbiteGame.h"

class FrostbiteConnection;
class BF3CommandHandler;
class BF3LevelDictionary;

class BF3 : public FrostbiteGame {
    Q_OBJECT

public:
    BF3(ServerEntry *serverEntry);
    ~BF3();

protected:
    FrostbiteConnection *con;
    BF3CommandHandler *commandHandler;
    BF3LevelDictionary *levelDictionary;

    bool isAuthenticated();

private:
    bool authenticated;

private slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);

};

#endif // BF3_H
