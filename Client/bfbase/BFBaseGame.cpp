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

#include "BFBaseGame.h"

BFBaseGame::BFBaseGame(const QString &host, const int &port, const QString &password) : Game(host, port, password)
{

}

BFBaseGame::~BFBaseGame()
{

}

QString BFBaseGame::getVersionFromBuild(const int &build)
{
    return versionMap.contains(build) ? versionMap.value(build) : QString::number(build);
}

QString BFBaseGame::getPlayerSubsetName(const int &playerSubset)
{
    QString playerSubsetName;

    switch (playerSubset) {
        case All:
            playerSubsetName = "All";
            break;

        case Team:
            playerSubsetName = "Team";
            break;

        case Squad:
            playerSubsetName = "Squad";
            break;

        case Player:
            playerSubsetName = "Player";
            break;
    }

    return playerSubsetName;
}

QString BFBaseGame::getSquadName(const int &squadId)
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
