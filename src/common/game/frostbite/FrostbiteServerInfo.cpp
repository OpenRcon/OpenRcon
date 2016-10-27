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

#include "FrostbiteServerInfo.h"
#include "TeamScores.h"

FrostbiteServerInfo::FrostbiteServerInfo(const QString &serverName,
                                         int playerCount,
                                         int maxPlayerCount,
                                         const QString &gameMode,
                                         const QString &currentMap,
                                         int roundsPlayed,
                                         int roundsTotal,
                                         const TeamScores &scores,
                                         bool ranked,
                                         bool punkBuster,
                                         bool gamePassword,
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
    ranked(ranked),
    punkBuster(punkBuster),
    gamePassword(gamePassword),
    serverUpTime(serverUpTime),
    roundTime(roundTime)
{

}

FrostbiteServerInfo::~FrostbiteServerInfo()
{

}

QString FrostbiteServerInfo::getServerName() const
{
    return serverName;
}

int FrostbiteServerInfo::getPlayerCount() const
{
    return playerCount;
}

int FrostbiteServerInfo::getMaxPlayerCount() const
{
    return maxPlayerCount;
}

QString FrostbiteServerInfo::getGameMode() const
{
    return gameMode;
}

QString FrostbiteServerInfo::getCurrentMap() const
{
    return currentMap;
}

int FrostbiteServerInfo::getRoundsPlayed() const
{
    return roundsPlayed;
}

int FrostbiteServerInfo::getRoundsTotal() const
{
    return roundsTotal;
}

TeamScores FrostbiteServerInfo::getScores() const
{
    return scores;
}

bool FrostbiteServerInfo::isRanked() const
{
    return ranked;
}

bool FrostbiteServerInfo::hasPunkBuster() const
{
    return punkBuster;
}

bool FrostbiteServerInfo::hasGamePassword() const
{
    return gamePassword;
}

int FrostbiteServerInfo::getServerUpTime() const
{
    return serverUpTime;
}

int FrostbiteServerInfo::getRoundTime() const
{
    return roundTime;
}
