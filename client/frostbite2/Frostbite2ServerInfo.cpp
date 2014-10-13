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

#include "Frostbite2ServerInfo.h"

Frostbite2ServerInfo::Frostbite2ServerInfo(const QString &serverName,
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
                                           bool matchMakingEnabled) :
    ServerInfo(serverName,
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
               roundTime),
    gameIpAndPort(gameIpAndPort),
    punkBusterVersion(punkBusterVersion),
    joinQueueEnabled(joinQueueEnabled),
    region(region),
    closestPingSite(closestPingSite),
    country(country),
    matchMakingEnabled(matchMakingEnabled)
{

}

Frostbite2ServerInfo::~Frostbite2ServerInfo()
{

}

QString Frostbite2ServerInfo::getGameIpAndPort()
{
    return gameIpAndPort;
}

QString Frostbite2ServerInfo::getPunkBusterVersion()
{
    return punkBusterVersion;
}

bool Frostbite2ServerInfo::getJoinQueueEnabled()
{
    return joinQueueEnabled;
}

QString Frostbite2ServerInfo::getRegion()
{
    return region;
}

QString Frostbite2ServerInfo::getClosestPingSite()
{
    return closestPingSite;
}

QString Frostbite2ServerInfo::getCountry()
{
    return country;
}

bool Frostbite2ServerInfo::getMatchMakingEnabled()
{
    return matchMakingEnabled;
}
