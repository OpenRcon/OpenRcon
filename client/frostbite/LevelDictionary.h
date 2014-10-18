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
class GameModeLevelEntry;

template<int gameId, typename TeamEntryType, typename LevelEntryType, typename GameModeEntryType, typename GameModeLevelEntryType>
class LevelDictionary
{
public:
    LevelDictionary()
    {
        static_assert(std::is_base_of<TeamEntry, TeamEntryType>::value, "TeamEntryType must be a subclass of TeamEntry.");
        static_assert(std::is_base_of<LevelEntry, LevelEntryType>::value, "LevelEntryType must be a subclass of LevelEntry.");
        static_assert(std::is_base_of<GameModeEntry, GameModeEntryType>::value, "GameModeEntryType must be a subclass of GameModeEntry.");
        static_assert(std::is_base_of<GameModeLevelEntry, GameModeLevelEntryType>::value, "GameModeLevelEntryType must be a subclass of GameModeLevelEntry.");
    }

    static LevelEntryType getLevel(int index)
    {
        return levelList.at(index);
    }

    static LevelEntryType getLevel(const QString &level)
    {
        LevelEntryType empty;

        for (LevelEntryType entry : levelList) {
            if (entry.getEngineName() == level || entry.getName() == level) {
                return entry;
            }
        }

        return empty;
    }

    static LevelEntryType getLevel(int index, int gameModeIndex)
    {
        return getLevels(gameModeIndex).at(index);
    }

    static QList<LevelEntryType> getLevels()
    {
        return levelList;
    }

    static QList<LevelEntryType> getLevels(int gameModeIndex)
    {
        QList<LevelEntryType> list;

        for (GameModeLevelEntryType gameModeLevelEntry : levelMap) {
            if (gameModeLevelEntry.getGamemode() == gameModeIndex) {
                list.append(levelList.at(gameModeLevelEntry.getLevel()));
            }
        }

        return list;
    }

    static QStringList getLevelNames()
    {
        QStringList list;

        for (LevelEntryType entry : levelList) {
            list.append(entry.name);
        }

        return list;
    }

    static QStringList getLevelNames(int gameModeIndex)
    {
        QStringList list;

        for (LevelEntryType entry : getLevels(gameModeIndex)) {
            list.append(entry.getName());
        }

        return list;
    }

    static GameModeEntryType getGameMode(int index)
    {
        return getGameModes().at(index);
    }

    static GameModeEntryType getGameMode(const QString &gameMode)
    {
        GameModeEntryType empty;

        for (GameModeEntryType entry : gameModeList) {
            if (entry.getEngineName() == gameMode || entry.getName() == gameMode) {
                return entry;
            }
        }

        return empty;
    }

    static QList<GameModeEntryType> getGameModes()
    {
        return gameModeList;
    }

    static QStringList getGameModeNames()
    {
        QStringList list;

        for (GameModeEntryType entry : gameModeList) {
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

    static QList<TeamEntryType> getTeams(GameModeEntryType gameModeEntry, LevelEntryType levelEntry)
    {
        QList<TeamEntryType> list;

        for (GameModeLevelEntryType gameModeLevelEntry : levelMap) {
            if (gameModeLevelEntry.getGamemode() == gameModeList.indexOf(gameModeEntry) &&
                gameModeLevelEntry.getLevel() == levelList.indexOf(levelEntry)) {
                for (int i = 0; i < teamList.length(); i++) {
                    if (gameModeLevelEntry.getTeamList().contains(i)) {
                        list.append(teamList.at(i));
                    }
                }
            }
        }

        return list;
    }

private:
    static QList<TeamEntryType> teamList;
    static QString imagePath;
    static QList<LevelEntryType> levelList;
    static QList<GameModeEntryType> gameModeList;
    static QList<GameModeLevelEntry> levelMap;

};

#endif // LEVELDICTIONARY_H
