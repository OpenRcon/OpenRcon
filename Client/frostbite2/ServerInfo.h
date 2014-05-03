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

#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QString>

struct ServerInfo {
    ServerInfo(const QString &serverName,
               const int &playerCount,
               const int &maxPlayerCount,
               const QString &gameMode,
               const QString &currentMap,
               const int &roundsPlayed,
               const int &roundsTotal,
               const QString &scores,
               const QString &onlineState,
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
        roundTime(roundTime),
        gameIpAndPort(gameIpAndPort),
        punkBusterVersion(punkBusterVersion),
        joinQueueEnabled(joinQueueEnabled),
        region(region),
        closestPingSite(closestPingSite),
        country(country),
        matchMakingEnabled(matchMakingEnabled),
        blazePlayerCount(blazePlayerCount),
        blazeGameState(blazeGameState)
    {

    }

    QString serverName;
    int playerCount;
    int maxPlayerCount;
    QString gameMode;
    QString currentMap;
    int roundsPlayed;
    int roundsTotal;
    QString scores;
    QString onlineState;
    bool ranked;
    bool punkBuster;
    bool hasGamePassword;
    int serverUpTime;
    int roundTime;
    QString gameIpAndPort;
    QString punkBusterVersion;
    bool joinQueueEnabled;
    QString region;
    QString closestPingSite;
    QString country;
    bool matchMakingEnabled;
    int blazePlayerCount;
    QString blazeGameState;

};

#endif // SERVERINFO_H
