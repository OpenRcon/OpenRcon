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
#include "ServerEntry.h"
#include "GameType.h"

#include "BF3MainWidget.h"
#include "BF4MainWidget.h"

QList<GameEntry> GameManager::gameList = {
    // Adds all games to the list.
    GameEntry(GameType::BFBC2,     "BFBC2",     "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png",         48888),
    GameEntry(GameType::BF3,       "BF3",       "Battlefield 3",              ":/bf3/icons/bf3.png",             47300),
    GameEntry(GameType::BF4,       "BF4",       "Battlefield 4",              ":/bf4/icons/bf4.png",             47200)
};

GameEntry GameManager::getGame(GameType gameType)
{
    return getGame(toInt(gameType));
}

GameEntry GameManager::getGame(int index)
{
    return gameList.at(index);
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

GameWidget *GameManager::getGameWidget(ServerEntry *serverEntry)
{
    GameType gameType = serverEntry->getGameType();
    GameWidget *gameWidget = nullptr;

    switch (gameType) {
    case GameType::BFBC2:
        //gameWidget = new BFBC2Widget(serverEntry);
        gameWidget = nullptr;
        break;

    case GameType::BF3:
        gameWidget = new BF3MainWidget(serverEntry);
        break;

    case GameType::BF4:
        gameWidget = new BF4MainWidget(serverEntry);
        break;

    default:
        qDebug() << tr("Unknown game requested, id was: %1.").arg(toInt(gameType));
        break;
    }

    return gameWidget;
}

int GameManager::toInt(GameType gameType)
{
    return static_cast<int>(gameType);
}

GameType GameManager::toGameType(int gameType)
{
    return static_cast<GameType>(gameType);
}

GameType GameManager::toGameType(const QString &gameType)
{
    return getGame(gameType).getGameType();
}
