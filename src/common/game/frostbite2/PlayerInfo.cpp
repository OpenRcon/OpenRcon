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

#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(const QString &name,
                       const QString &guid,
                       int teamId,
                       int squadId,
                       int kills,
                       int deaths,
                       int score,
                       int rank,
                       int ping) :
    name(name),
    guid(guid),
    teamId(teamId),
    squadId(squadId),
    kills(kills),
    deaths(deaths),
    score(score),
    rank(rank),
    ping(ping)
{

}

PlayerInfo::~PlayerInfo()
{

}

QString PlayerInfo::getName() const
{
    return name;
}

QString PlayerInfo::getGuid() const
{
    return guid;
}

int PlayerInfo::getTeamId() const
{
    return teamId;
}

int PlayerInfo::getSquadId() const
{
    return squadId;
}

int PlayerInfo::getKills() const
{
    return kills;
}

int PlayerInfo::getDeaths() const
{
    return deaths;
}

int PlayerInfo::getScore() const
{
    return score;
}

int PlayerInfo::getRank() const
{
    return rank;
}

int PlayerInfo::getPing() const
{
    return ping;
}
