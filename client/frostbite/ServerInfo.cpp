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

#include "ServerInfo.h"

ServerInfo::ServerInfo(const QString &serverName,
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
           int roundTime) :
    serverName(serverName),
    playerCount(playerCount),
    maxPlayerCount(maxPlayerCount),
    gameMode(gameMode),
    currentMap(currentMap),
    roundsPlayed(roundsPlayed),
    roundsTotal(roundsTotal),
    scores(scores),
    onlineState(onlineState),
    ranked(ranked),
    punkBuster(punkBuster),
    hasGamePassword(hasGamePassword),
    serverUpTime(serverUpTime),
    roundTime(roundTime)
{

}

ServerInfo::~ServerInfo()
{

}

QString ServerInfo::getServerName()
{
    return serverName;
}

int ServerInfo::getPlayerCount()
{
    return playerCount;
}

int ServerInfo::getMaxPlayerCount()
{
    return maxPlayerCount;
}

QString ServerInfo::getGameMode()
{
    return gameMode;
}

QString ServerInfo::getCurrentMap()
{
    return currentMap;
}

int ServerInfo::getRoundsPlayed()
{
    return roundsPlayed;
}

int ServerInfo::getRoundsTotal()
{
    return roundsTotal;
}

TeamScores ServerInfo::getScores()
{
    return scores;
}

OnlineState ServerInfo::getOnlineState()
{
    return onlineState;
}

bool ServerInfo::getRanked()
{
    return ranked;
}

bool ServerInfo::getPunkBuster()
{
    return punkBuster;
}

bool ServerInfo::getHasGamePassword()
{
    return hasGamePassword;
}

int ServerInfo::getServerUpTime()
{
    return serverUpTime;
}

int ServerInfo::getRoundTime()
{
    return roundTime;
}
