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

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    // Adds all games to the list.
    gameList.append(GameEntry(0, "BFBC2", "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png"));
    gameList.append(GameEntry(1, "BF3", "Battlefield 3", ":/bf3/icons/bf3.png"));
    gameList.append(GameEntry(2, "BF4", "Battlefield 4", ":/bf4/icons/bf4.png"));
    gameList.append(GameEntry(3, "MC", "Minecraft", ":/minecraft/icons/minecraft.png"));
}

GameManager::~GameManager()
{

}

GameEntry GameManager::getGame(const int &index)
{
    return gameList.at(index);
}

QList<GameEntry> GameManager::getGames()
{
    return gameList;
}
