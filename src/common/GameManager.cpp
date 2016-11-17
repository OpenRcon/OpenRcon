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

#include <QString>
#include <QList>

#include "GameManager.h"

#include "GameEntry.h"
#include "GameType.h"

QList<GameEntry> GameManager::gameList = {
    // Adds all games to the list.
    GameEntry(GameTypeEnum::BFBC2,     "BFBC2",     "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png",         48888),
    GameEntry(GameTypeEnum::BF3,       "BF3",       "Battlefield 3",              ":/bf3/icons/bf3.png",             47300),
    GameEntry(GameTypeEnum::BF4,       "BF4",       "Battlefield 4",              ":/bf4/icons/bf4.png",             47200)
};

bool GameManager::isGameSupported(int gameId)
{
    return gameId < gameList.length();
}

GameEntry GameManager::getGame(GameTypeEnum gameType)
{
    return getGame(toInt(gameType));
}

GameEntry GameManager::getGame(int gameId)
{
    if (gameId < gameList.length()) {
        return gameList.at(gameId);
    }

    return GameEntry();
}

GameEntry GameManager::getGame(const QString &gamePrefix)
{
    for (GameEntry entry : gameList) {
        if (entry.getPrefix() == gamePrefix) {
            return entry;
        }
    }

    return GameEntry();
}

QList<GameEntry> GameManager::getGames()
{
    return gameList;
}

int GameManager::toInt(GameTypeEnum gameType)
{
    return static_cast<int>(gameType);
}

GameTypeEnum GameManager::toGameType(int gameTypeId)
{
    return static_cast<GameTypeEnum>(gameTypeId);
}

GameTypeEnum GameManager::toGameType(const QString &gameType)
{
    return getGame(gameType).getGameType();
}
