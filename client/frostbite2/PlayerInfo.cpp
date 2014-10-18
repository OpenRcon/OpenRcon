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

QString PlayerInfo::getName()
{
    return name;
}

QString PlayerInfo::getGuid()
{
    return guid;
}

int PlayerInfo::getTeamId()
{
    return teamId;
}

int PlayerInfo::getSquadId()
{
    return squadId;
}

int PlayerInfo::getKills()
{
    return kills;
}

int PlayerInfo::getDeaths()
{
    return deaths;
}

int PlayerInfo::getScore()
{
    return score;
}

int PlayerInfo::getRank()
{
    return rank;
}

int PlayerInfo::getPing()
{
    return ping;
}
