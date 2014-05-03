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

#ifndef BFBC2SERVERINFO_H
#define BFBC2SERVERINFO_H

#include "ServerInfo.h"

struct BFBC2ServerInfo : public ServerInfo {
    BFBC2ServerInfo(const QString &serverName,
               const int &playerCount,
               const int &maxPlayerCount,
               const QString &gameMode,
               const QString &currentMap,
               const int &roundsPlayed,
               const int &roundsTotal,
               const QString &scores,
               const OnlineState &onlineState,
               const bool &ranked,
               const bool &punkBuster,
               const bool &hasGamePassword,
               const int &serverUpTime,
               const int &roundTime,
               const int &gameModId,
               const int &mapPack,
               const QString &externalGameIpAndPort) :
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

    int gameModId;
    int mapPack;
    QString externalGameIpAndPort;

};

#endif // BFBC2SERVERINFO_H
