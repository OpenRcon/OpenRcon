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

#ifndef FROSTBITEGAME_H
#define FROSTBITEGAME_H

#include "Game.h"

#include "TimeEntry.h"

class FrostbiteGame : public Game
{

public:
    FrostbiteGame(ServerEntry *serverEntry);
    ~FrostbiteGame();

protected:
    QMap<int, QString> versionMap;
    QStringList commandList;

    enum Squad {
        Unknown,
        Alpha,
        Bravo,
        Charlie,
        Delta,
        Echo,
        Foxtrot,
        Golf,
        Hotel
    };

    QString getVersionFromBuild(int build);
    TimeEntry getTimeFromSeconds(int elapsedSeconds);
    QString getSquadName(int squadId);

};

#endif // FROSTBITEGAME_H
