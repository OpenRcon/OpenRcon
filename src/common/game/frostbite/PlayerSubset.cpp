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

#include "PlayerSubset.h"

QStringList PlayerSubset::list = {
    "All",
    "Team",
    "Squad",
    "Player",
    "Unknown"
};

PlayerSubsetEnum PlayerSubset::fromString(const QString &playerSubsetName)
{
    PlayerSubsetEnum playerSubset = PlayerSubsetEnum::Unknown;

    if (playerSubsetName == "Unknown") {
        playerSubset = PlayerSubsetEnum::Unknown;
    } else if (playerSubsetName == "All") {
        playerSubset = PlayerSubsetEnum::All;
    } else if (playerSubsetName == "Team") {
        playerSubset = PlayerSubsetEnum::Team;
    } else if (playerSubsetName == "Squad") {
        playerSubset = PlayerSubsetEnum::Squad;
    } else if (playerSubsetName == "Player") {
        playerSubset = PlayerSubsetEnum::Player;
    }

    return playerSubset;
}

QString PlayerSubset::toString(const PlayerSubsetEnum &playerSubset)
{
    return list.at(static_cast<int>(playerSubset));
}

QStringList PlayerSubset::asList()
{
    return list;
}
