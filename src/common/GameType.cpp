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
#include <QStringList>

#include "GameType.h"

QStringList GameType::list = {
    "BFBC2",
    "BF3",
    "BF4"
};

GameTypeEnum GameType::fromString(const QString &game)
{
    GameTypeEnum gameType = GameTypeEnum::Unsupported;

    if (game == "BFBC2") {
        gameType = GameTypeEnum::BFBC2;
    } else if (game == "BF3") {
        gameType = GameTypeEnum::BF3;
    } else if (game == "BF4") {
        gameType = GameTypeEnum::BF4;
    }

    return gameType;
}

QString GameType::toString(const GameTypeEnum &gameType)
{
    return list.at(toInt(gameType));
}

GameTypeEnum GameType::fromInt(int gameTypeId)
{
    return static_cast<GameTypeEnum>(gameTypeId);
}

int GameType::toInt(const GameTypeEnum &gameType)
{
    return static_cast<int>(gameType);
}

QStringList GameType::asList()
{
    return list;
}
