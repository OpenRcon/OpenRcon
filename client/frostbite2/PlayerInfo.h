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

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QString>

struct PlayerInfo
{
    PlayerInfo(const QString &name,
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

    QString name;
    QString guid;
    int teamId;
    int squadId;
    int kills;
    int deaths;
    int score;
    int rank;
    int ping;

};

#endif // PLAYERINFO_H
