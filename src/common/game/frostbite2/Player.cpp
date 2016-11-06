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

#include "Player.h"

Player::Player(const QString &name,
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

Player::~Player()
{

}

QString Player::getName() const
{
    return name;
}

QString Player::getGuid() const
{
    return guid;
}

int Player::getTeamId() const
{
    return teamId;
}

int Player::getSquadId() const
{
    return squadId;
}

int Player::getKills() const
{
    return kills;
}

int Player::getDeaths() const
{
    return deaths;
}

int Player::getScore() const
{
    return score;
}

int Player::getRank() const
{
    return rank;
}

int Player::getPing() const
{
    return ping;
}
