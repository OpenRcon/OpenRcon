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

// Adds all games to the list.
QList<GameEntry> GameManager::gameList = { GameEntry(GameType::BFBC2, "BFBC2", "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png"),
                                           GameEntry(GameType::BF3, "BF3", "Battlefield 3", ":/bf3/icons/bf3.png"),
                                           GameEntry(GameType::BF4, "BF4", "Battlefield 4", ":/bf4/icons/bf4.png"),
                                           GameEntry(GameType::Minecraft, "Minecraft", "Minecraft", ":/minecraft/icons/minecraft.png") };

GameEntry GameManager::getGame(GameType gameType)
{
    return gameList.at(static_cast<int>(gameType));
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
            qDebug() << tr("Unknown game specified, the id was: %1.").arg(static_cast<int>(gameType));
            break;
    }

    return gameObject;
}
