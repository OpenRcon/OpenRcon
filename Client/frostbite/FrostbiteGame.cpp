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

#include "FrostbiteGame.h"

FrostbiteGame::FrostbiteGame(ServerEntry *serverEntry) : Game(serverEntry)
{

}

FrostbiteGame::~FrostbiteGame()
{

}

QString FrostbiteGame::getVersionFromBuild(const int &build)
{
    return versionMap.contains(build) ? versionMap.value(build) : QString::number(build);
}

TimeEntry FrostbiteGame::getTimeFromSeconds(const int &elapsedSeconds)
{
    int days = elapsedSeconds / 60 / 60 / 24;
    int hours = (elapsedSeconds / 60 / 60) % 24;
    int minutes = (elapsedSeconds / 60) % 60;
    int seconds = elapsedSeconds % 60;

    return TimeEntry(days, hours, minutes, seconds);
}

QString FrostbiteGame::getSquadName(const int &squadId)
{
    QString squadName;

    switch (squadId) {
        case Alpha:
            squadName = "Alpha";
            break;

        case Bravo:
            squadName = "Bravo";
            break;

        case Charlie:
            squadName = "Charlie";
            break;

        case Delta:
            squadName = "Delta";
            break;

        case Echo:
            squadName = "Echo";
            break;

        case Foxtrot:
            squadName = "Foxtrot";
            break;

        case Golf:
            squadName = "Golf";
        break;

        case Hotel:
            squadName = "Hotel";
            break;

    }

    return squadName;
}
