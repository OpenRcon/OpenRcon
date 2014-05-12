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

#ifndef LEVELDICTIONARY_H
#define LEVELDICTIONARY_H

#include <QHash>

#include "LevelEntry.h"
#include "GameModeEntry.h"

class LevelDictionary
{
public:
    LevelDictionary();
    ~LevelDictionary();

    static LevelEntry getLevel(int index);
    static LevelEntry getLevel(const QString &level);
    static LevelEntry getLevel(int index, int gameModeIndex);
    static GameModeEntry getGameMode(int index);
    static GameModeEntry getGameMode(const QString &level);
    static QString getTeam(int index);

    static QList<LevelEntry> getLevels();
    static QList<LevelEntry> getLevels(int gameModeIndex);
    static QList<GameModeEntry> getGameModes();
    static QStringList getTeams();
    static QStringList getTeams(const LevelEntry &level);

    static QStringList getLevelNames();
    static QStringList getLevelNames(int gameModeIndex);
    static QStringList getGameModeNames();

protected:
    static QList<LevelEntry> levelList;
    static QList<GameModeEntry> gameModeList;
    static QStringList teamList;

    static QHash<int, int> levelMap;

};

#endif // LEVELDICTIONARY_H
