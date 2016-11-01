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

#include <QStringList>

#include "GameType.h"

QStringList GameTypeUtils::list = {
    "BFBC2",
    "BF3",
    "BF4",
};

GameType GameTypeUtils::fromString(const QString &game)
{
    GameType gameType = GameType::Unsupported;

    if (game == "BFBC2") {
        gameType = GameType::BFBC2;
    } else if (game == "BF3") {
        gameType = GameType::BF3;
    } else if (game == "BF4") {
        gameType = GameType::BF4;
    }

    return gameType;
}

QString GameTypeUtils::toString(const GameType &gameType)
{
    return list.at(static_cast<int>(gameType));
}

QStringList GameTypeUtils::asList()
{
    return list;
}
