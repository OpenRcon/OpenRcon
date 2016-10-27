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

#ifndef TEAMSCORES_H
#define TEAMSCORES_H

#include <QList>

class TeamScores
{
public:
    TeamScores(const QList<int> &scores, int targetScore = 0);
    ~TeamScores();

    QList<int> getScores();
    int getTargetScore();

private:
    QList<int> scores;
    int targetScore;

};

#endif // TEAMSCORES_H
