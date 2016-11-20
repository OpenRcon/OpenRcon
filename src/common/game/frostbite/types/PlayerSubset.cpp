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
#include <QStringList>

#include "PlayerSubset.h"

#include "FrostbiteUtils.h"

QList<PlayerSubsetEnum> PlayerSubset::list = {
    PlayerSubsetEnum::All,
    PlayerSubsetEnum::Team,
    PlayerSubsetEnum::Squad,
    PlayerSubsetEnum::Player,
    PlayerSubsetEnum::Unknown
};

QStringList PlayerSubset::stringList = {
    "All",
    "Team",
    "Squad",
    "Player",
    "Unknown"
};

PlayerSubsetEnum PlayerSubset::fromString(const QString &playerSubsetName)
{
    QString playerSubsetNameCamelCase = FrostbiteUtils::toCamelCase(playerSubsetName);
    PlayerSubsetEnum playerSubset = PlayerSubsetEnum::Unknown;

    if (playerSubsetNameCamelCase == "All") {
        playerSubset = PlayerSubsetEnum::All;
    } else if (playerSubsetNameCamelCase == "Team") {
        playerSubset = PlayerSubsetEnum::Team;
    } else if (playerSubsetNameCamelCase == "Squad") {
        playerSubset = PlayerSubsetEnum::Squad;
    } else if (playerSubsetNameCamelCase == "Player") {
        playerSubset = PlayerSubsetEnum::Player;
    }

    return playerSubset;
}

QString PlayerSubset::toString(const PlayerSubsetEnum &playerSubset)
{
    return stringList.at(toInt(playerSubset));
}

PlayerSubsetEnum PlayerSubset::fromInt(int playuerSubsetId)
{
    return static_cast<PlayerSubsetEnum>(playuerSubsetId);
}

int PlayerSubset::toInt(const PlayerSubsetEnum &playerSubset)
{
    return static_cast<int>(playerSubset);
}

QList<PlayerSubsetEnum> PlayerSubset::asList()
{
    return list;
}

QStringList PlayerSubset::asStringList()
{
    return stringList;
}
