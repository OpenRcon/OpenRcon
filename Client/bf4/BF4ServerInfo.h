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

#ifndef BF4SERVERINFO_H
#define BF4SERVERINFO_H

#include <QString>

#include "Frostbite2ServerInfo.h"

struct BF4ServerInfo : public Frostbite2ServerInfo {
    BF4ServerInfo(const QString &serverName,
               const int &playerCount,
               const int &maxPlayerCount,
               const QString &gameMode,
               const QString &currentMap,
               const int &roundsPlayed,
               const int &roundsTotal,
               const TeamScores &scores,
               const OnlineState &onlineState,
               const bool &ranked,
               const bool &punkBuster,
               const bool &hasGamePassword,
               const int &serverUpTime,
               const int &roundTime,
               const QString &gameIpAndPort,
               const QString &punkBusterVersion,
               const bool &joinQueueEnabled,
               const QString &region,
               const QString &closestPingSite,
               const QString &country,
               const bool &matchMakingEnabled,
               const int &blazePlayerCount,
               const QString &blazeGameState) :
        Frostbite2ServerInfo(serverName,
                             playerCount,
                             maxPlayerCount,
                             gameMode,
                             currentMap,
                             roundsPlayed,
                             roundsTotal,
                             scores,
                             onlineState,
                             ranked,
                             punkBuster,
                             hasGamePassword,
                             serverUpTime,
                             roundTime,
                             gameIpAndPort,
                             punkBusterVersion,
                             joinQueueEnabled,
                             region,
                             closestPingSite,
                             country,
                             matchMakingEnabled),
        blazePlayerCount(blazePlayerCount),
        blazeGameState(blazeGameState)
    {

    }

    int blazePlayerCount;
    QString blazeGameState;

};

#endif // BF4SERVERINFO_H
