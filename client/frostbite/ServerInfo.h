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

#include "TeamScores.h"
#include "OnlineState.h"

class ServerInfo
{
public:
    ServerInfo(const QString &serverName,
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
               int roundTime);
    ~ServerInfo();

    QString getServerName();
    int getPlayerCount();
    int getMaxPlayerCount();
    QString getGameMode();
    QString getCurrentMap();
    int getRoundsPlayed();
    int getRoundsTotal();
    TeamScores getScores();
    OnlineState getOnlineState();
    bool getRanked();
    bool getPunkBuster();
    bool getHasGamePassword();
    int getServerUpTime();
    int getRoundTime();

private:
    QString serverName;
    int playerCount;
    int maxPlayerCount;
    QString gameMode;
    QString currentMap;
    int roundsPlayed;
    int roundsTotal;
    TeamScores scores;
    OnlineState onlineState;
    bool ranked;
    bool punkBuster;
    bool hasGamePassword;
    int serverUpTime;
    int roundTime;

};

#endif // SERVERINFO_H
