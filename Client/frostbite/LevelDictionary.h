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

class LevelDictionary : public QObject
{
    Q_OBJECT

public:
    explicit LevelDictionary(QObject *parent = 0);
    explicit LevelDictionary(const QString &imagePath, QObject *parent = 0);
    ~LevelDictionary();

    LevelEntry getLevel(const int &index);
    LevelEntry getLevel(const QString &level);
    LevelEntry getLevel(const int &index, const int &gameModeIndex);
    GameModeEntry getGameMode(const int &index);
    GameModeEntry getGameMode(const QString &level);
    QString getTeam(const int &index);

    QList<LevelEntry> getLevels();
    QList<LevelEntry> getLevels(const int &gameModeIndex);
    QList<GameModeEntry> getGameModes();
    QStringList getTeams();
    QStringList getTeams(const LevelEntry &level);

    QStringList getLevelNames();
    QStringList getLevelNames(const int &gameModeIndex);
    QStringList getGameModeNames();

protected:
    QList<LevelEntry> levelList;
    QList<GameModeEntry> gameModeList;
    QStringList teamList;
    QHash<int, int> levelMap;
    QString imagePath;

};

#endif // LEVELDICTIONARY_H
