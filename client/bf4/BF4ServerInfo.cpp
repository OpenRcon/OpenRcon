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

#include "BF4ServerInfo.h"

BF4ServerInfo::BF4ServerInfo(const QString &serverName,
                             int playerCount,
                             int maxPlayerCount,
                             const QString &gameMode,
                             const QString &currentMap,
                             int roundsPlayed,
                             int roundsTotal,
                             const TeamScores &scores,
                             const OnlineState &onlineState,
                             bool ranked,
                             bool punkBuster,
                             bool hasGamePassword,
                             int serverUpTime,
                             int roundTime,
                             const QString &gameIpAndPort,
                             const QString &punkBusterVersion,
                             bool joinQueueEnabled,
                             const QString &region,
                             const QString &closestPingSite,
                             const QString &country,
                             bool matchMakingEnabled,
                             int blazePlayerCount,
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

BF4ServerInfo::~BF4ServerInfo()
{

}

int BF4ServerInfo::getBlazePlayerCount() const
{
    return blazePlayerCount;
}

QString BF4ServerInfo::getBlazeGameState() const
{
    return blazeGameState;
}
