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

#include <QList>
#include <QMultiHash>
#include <QStringList>

class TeamEntry;
class LevelEntry;
class GameModeEntry;

typedef QList<TeamEntry> TeamList;
typedef QList<LevelEntry> LevelList;
typedef QList<GameModeEntry> GameModeList;

template<int gameId, typename TeamEntryType, typename LevelEntryType, typename GameModeEntryType>
class LevelDictionary
{
public:
    LevelDictionary()
    {
        static_assert(std::is_base_of<TeamEntry, TeamEntryType>::value, "TeamEntryType must be a subclass of TeamEntry.");
        static_assert(std::is_base_of<LevelEntry, LevelEntryType>::value, "LevelEntryType must be a subclass of LevelEntry.");
        static_assert(std::is_base_of<GameModeEntry, GameModeEntryType>::value, "GameModeEntryType must be a subclass of GameModeEntry.");
    }

    ~LevelDictionary();

    static const LevelEntryType &getLevel(int index)
    {
        return levelList.at(index);
    }

    static const LevelEntryType &getLevel(const QString &level)
    {
        static const LevelEntryType empty;

        for (LevelEntryType &entry : levelList) {
            if (entry.getEngineName() == level || entry.getName() == level) {
                return entry;
            }
        }

        return empty;
    }

    static const LevelEntryType &getLevel(int index, int gameModeIndex)
    {
        return getLevels(gameModeIndex).at(index);
    }

    static const QList<LevelEntryType> &getLevels()
    {
        return levelList;
    }

    static QList<LevelEntryType> getLevels(int gameModeIndex)
    {
        QList<LevelEntryType> list;

        for (int index : levelMap.values(gameModeIndex)) {
            list.append(levelList.at(index));
        }

        return list;
    }

    static QStringList getLevelNames()
    {
        QStringList list;

        for (const LevelEntryType &entry : levelList) {
            list.append(entry.name);
        }

        return list;
    }

    static QStringList getLevelNames(int gameModeIndex)
    {
        QStringList list;

        for (LevelEntryType &entry : getLevels(gameModeIndex)) {
            list.append(entry.getName());
        }

        return list;
    }

    static const GameModeEntryType &getGameMode(int index)
    {
        return getGameModes().at(index);
    }

    static const GameModeEntryType &getGameMode(const QString &level)
    {
        static const GameModeEntryType empty;

        for (GameModeEntryType &entry : gameModeList) {
            if (entry.getEngineName() == level || entry.getName() == level) {
                return entry;
            }
        }

        return empty;
    }

    static const QList<GameModeEntryType> &getGameModes()
    {
        return gameModeList;
    }

    static QStringList getGameModeNames()
    {
        QStringList list;

        for (GameModeEntryType &entry : gameModeList) {
            list.append(entry.getName());
        }

        return list;
    }

    static TeamEntryType getTeam(int index)
    {
        return teamList.at(index);
    }

    static QList<TeamEntryType> getTeams()
    {
        return teamList;
    }

private:
    static QList<TeamEntryType> teamList;
    static QString imagePath;
    static QList<LevelEntryType> levelList;
    static QList<GameModeEntryType> gameModeList;
    static QMultiHash<int, int> levelMap;

};

#endif // LEVELDICTIONARY_H
