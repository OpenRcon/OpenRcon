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

#include "BFLevels.h"

BFLevels::BFLevels(QObject *parent) : QObject(parent)
{

}

BFLevels::~BFLevels()
{

}

LevelEntry BFLevels::getLevel(const int &index)
{
    return levelList.at(index);
}

LevelEntry BFLevels::getLevel(const QString &name)
{
    foreach (LevelEntry entry, levelList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return LevelEntry();
}

LevelEntry BFLevels::getLevel(const int &index, const int &gameModeIndex)
{
    return getLevels(gameModeIndex).at(index);
}

GameModeEntry BFLevels::getGameMode(const int &index)
{
    return gameModeList.at(index);
}

GameModeEntry BFLevels::getGameMode(const QString &name)
{
    foreach (GameModeEntry entry, gameModeList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return GameModeEntry();
}

QList<LevelEntry> BFLevels::getLevels()
{
    return levelList;
}

QList<LevelEntry> BFLevels::getLevels(const int &gameModeIndex)
{
    QList<LevelEntry> list;

    foreach (int index, levelMap.values(gameModeIndex)) {
        list.append(levelList.at(index));
    }

    return list;
}

QList<GameModeEntry> BFLevels::getGameModes()
{
    return gameModeList;
}

QStringList BFLevels::getLevelNames()
{
    QStringList list;

    foreach (LevelEntry entry, levelList) {
        list.append(entry.name);
    }

    return list;
}

QStringList BFLevels::getLevelNames(const int &gameModeIndex)
{
    QStringList list;

    foreach (LevelEntry entry, getLevels(gameModeIndex)) {
        list.append(entry.name);
    }

    return list;
}

QStringList BFLevels::getGameModeNames()
{
    QStringList list;

    foreach (GameModeEntry entry, gameModeList) {
        list.append(entry.name);
    }

    return list;
}
