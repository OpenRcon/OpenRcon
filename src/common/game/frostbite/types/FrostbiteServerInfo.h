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

#ifndef FROSTBITESERVERINFO_H
#define FROSTBITESERVERINFO_H

class QString;

class TeamScores;

class FrostbiteServerInfo
{
public:
    FrostbiteServerInfo(const QString &serverName,
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
                        int roundTime);
    virtual ~FrostbiteServerInfo();

    QString getServerName() const;
    int getPlayerCount() const;
    int getMaxPlayerCount() const;
    QString getGameMode() const;
    QString getCurrentMap() const;
    int getRoundsPlayed() const;
    int getRoundsTotal() const;
    TeamScores getScores() const;
    bool isRanked() const;
    bool hasPunkBuster() const;
    bool hasGamePassword() const;
    int getServerUpTime() const;
    int getRoundTime() const;

private:
    QString serverName;
    int playerCount;
    int maxPlayerCount;
    QString gameMode;
    QString currentMap;
    int roundsPlayed;
    int roundsTotal;
    TeamScores scores;
    bool ranked;
    bool punkBuster;
    bool gamePassword;
    int serverUpTime;
    int roundTime;

};

#endif // FROSTBITESERVERINFO_H
