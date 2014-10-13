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

class BFBC2ServerInfo : public ServerInfo
{
public:
    BFBC2ServerInfo(const QString &serverName,
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
                    int gameModId,
                    int mapPack,
                    const QString &externalGameIpAndPort);
    ~BFBC2ServerInfo();

    int getGameModId();
    int getMapPack();
    QString getExternalGameIpAndPort();

private:
    int gameModId;
    int mapPack;
    QString externalGameIpAndPort;

};

#endif // BFBC2SERVERINFO_H
