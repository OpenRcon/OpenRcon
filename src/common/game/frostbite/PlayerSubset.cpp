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
    "Unknown",
    "All",
    "Team",
    "Squad",
    "Player"
};

PlayerSubsetType PlayerSubset::fromString(const QString &playerSubset)
{
    PlayerSubsetType playerSubsetType = PlayerSubsetType::All;

    if (playerSubset == "Unknown") {
        playerSubsetType = PlayerSubsetType::Unknown;
    } else if (playerSubset == "All") {
        playerSubsetType = PlayerSubsetType::All;
    } else if (playerSubset == "Team") {
        playerSubsetType = PlayerSubsetType::Team;
    } else if (playerSubset == "Squad") {
        playerSubsetType = PlayerSubsetType::Squad;
    } else if (playerSubset == "Player") {
        playerSubsetType = PlayerSubsetType::Player;
    }

    return playerSubsetType;
}

QString PlayerSubset::toString(const PlayerSubsetType &playerSubsetType)
{
    return list.at(static_cast<int>(playerSubsetType));
}

QStringList PlayerSubset::asList()
{
    return list;
}
