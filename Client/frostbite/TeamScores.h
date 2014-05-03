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

#ifndef TEAMSCORES_H
#define TEAMSCORES_H

#include <QList>

// 2 65000 65000 0

//<number of entries : integer>
//N x <score : integer>
//<target score : integer>

struct TeamScores {
    TeamScores(const QList<int> &scores,
               const int &targetScore) :
        scores(scores),
        targetScore(targetScore)
    {

    }

    QList<int> scores;
    int targetScore;

};

#endif // TEAMSCORES_H
