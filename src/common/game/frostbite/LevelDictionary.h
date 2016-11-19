/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#include <QMultiHash>

class QString;
template<class T>
class QList;
class QStringList;

enum class GameTypeEnum;
class TeamEntry;
class LevelEntry;
class GameModeEntry;

template<GameTypeEnum gameType, class TeamEntryType, class LevelEntryType, class GameModeEntryType>
class LevelDictionary
{
public:
    LevelDictionary() {
        static_assert(std::is_base_of<TeamEntry, TeamEntryType>::value, "TeamEntryType must be a subclass of TeamEntry.");
        static_assert(std::is_base_of<LevelEntry, LevelEntryType>::value, "LevelEntryType must be a subclass of LevelEntry.");
        static_assert(std::is_base_of<GameModeEntry, GameModeEntryType>::value, "GameModeEntryType must be a subclass of GameModeEntry.");
    }

    ~LevelDictionary();

    static const LevelEntryType &getLevel(int levelIndex) {
        static const LevelEntryType empty;

        if (levelIndex < levelList.length()) {
            return levelList.at(levelIndex);
        }

        return empty;
    }

    static const LevelEntryType &getLevel(const QString &levelName) {
        static const LevelEntryType empty;

        for (LevelEntryType &levelEntry : levelList) {
            if (levelName == levelEntry.getEngineName() || levelName == levelEntry.getName()) {
                return levelEntry;
            }
        }

        return empty;
    }

    static const LevelEntryType &getLevel(int levelIndex, int gameModeIndex) {
        static const LevelEntryType empty;

        if (levelIndex < getLevels(gameModeIndex).length()) {
            return getLevels(gameModeIndex).at(levelIndex);
        }

        return empty;
    }

    static const QList<LevelEntryType> &getLevels() {
        return levelList;
    }

    static const QList<LevelEntryType> &getLevels(int gameModeIndex) {
        static QList<LevelEntryType> list;

        for (int levelIndex : levelMap.values(gameModeIndex)) {
            list.append(levelList.at(levelIndex));
        }

        return list;
    }

    static const QStringList &getLevelNames() {
        static QStringList list;

        for (const LevelEntryType &levelEntry : levelList) {
            list.append(levelEntry.getName());
        }

        return list;
    }

    static const QStringList &getLevelNames(int gameModeIndex) {
        static QStringList list;

        for (LevelEntryType &levelEntry : getLevels(gameModeIndex)) {
            list.append(levelEntry.getName());
        }

        return list;
    }

    static const GameModeEntryType &getGameMode(int gameModeIndex) {
        static const GameModeEntryType empty;

        if (gameModeIndex < gameModeList.length()) {
            return gameModeList.at(gameModeIndex);
        }

        return empty;
    }

    static const GameModeEntryType &getGameMode(const QString &levelName) {
        static const GameModeEntryType empty;

        for (GameModeEntryType &gameModeEntry : gameModeList) {
            if (levelName == gameModeEntry.getEngineName() || levelName == gameModeEntry.getName()) {
                return gameModeEntry;
            }
        }

        return empty;
    }

    static const QList<GameModeEntryType> &getGameModes() {
        return gameModeList;
    }

    static const QStringList &getGameModeNames() {
        static QStringList list;

        for (GameModeEntryType &entry : gameModeList) {
            list.append(entry.getName());
        }

        return list;
    }

    static const TeamEntryType &getTeam(int teamIndex) {
        static const TeamEntryType empty;

        if (teamIndex < teamList.length()) {
            return teamList.at(teamIndex);
        }

        return empty;
    }

    static const QList<TeamEntryType> &getTeams() {
        return teamList;
    }

    static const QList<TeamEntryType> &getTeams(const QList<int> teamIdList) {
        static QList<TeamEntryType> teamList;

        for (int teamId : teamIdList) {
            teamList.append(getTeam(teamId));
        }

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
