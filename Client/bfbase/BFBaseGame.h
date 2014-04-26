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

#ifndef BFBASEGAME_H
#define BFBASEGAME_H

#include "Game.h"

class BFBaseGame : public Game
{

public:
    explicit BFBaseGame(const QString &host, const int &port, const QString &password);
    ~BFBaseGame();

protected:
    QMap<int, QString> versionMap;
    QStringList commandList;

    enum PlayerSubset {
        All,
        Team,
        Squad,
        Player
    };

    enum Squad {
        Alpha,
        Bravo,
        Charlie,
        Delta,
        Echo,
        Foxtrot,
        Golf,
        Hotel
    };

    QString getVersionFromBuild(const int &build);
    QString getPlayerSubsetName(const int &playerSubset);
    QString getSquadName(const int &squadId);

};

#endif // BFBASEGAME_H
