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

#include "GameManager.h"

#include "Game.h"
#include "BFBC2Widget.h"
#include "BF3Widget.h"
#include "BF4Widget.h"
#include "MinecraftWidget.h"

QList<GameEntry> GameManager::gameList = {
    // Adds all games to the list.
    GameEntry(GameType::BFBC2, "BFBC2", "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png", 48888),
    GameEntry(GameType::BF3, "BF3", "Battlefield 3", ":/bf3/icons/bf3.png", 47300),
    GameEntry(GameType::BF4, "BF4", "Battlefield 4", ":/bf4/icons/bf4.png", 47200),
    GameEntry(GameType::Minecraft, "Minecraft", "Minecraft", ":/minecraft/icons/minecraft.png", 25575)
};

GameEntry GameManager::getGame(GameType gameType)
{
    return gameList.at(toInt(gameType));
}

QList<GameEntry> GameManager::getGames()
{
    return gameList;
}

Game* GameManager::getGameObject(ServerEntry *serverEntry)
{
    GameType gameType = serverEntry->gameType;
    Game *gameObject;

    switch (gameType) {
        case GameType::BFBC2:
            gameObject = new BFBC2Widget(serverEntry);
            break;

        case GameType::BF3:
            gameObject = new BF3Widget(serverEntry);
            break;

        case GameType::BF4:
            gameObject = new BF4Widget(serverEntry);
            break;

        case GameType::Minecraft:
            gameObject = new MinecraftWidget(serverEntry);
            break;

        default:
            qDebug() << tr("Unknown game specified, the id was: %1.").arg(toInt(gameType));
            break;
    }

    return gameObject;
}

int GameManager::toInt(GameType gameType)
{
    return static_cast<int>(gameType);
}

GameType GameManager::toGameType(int gameType)
{
    return static_cast<GameType>(gameType);
}
