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

#ifndef GAMEMODEENTRY_H
#define GAMEMODEENTRY_H

#include <QString>

class GameModeEntry
{
public:
    GameModeEntry(const QString &engineName, const QString &name, int players);
    GameModeEntry();
    ~GameModeEntry();

    QString getEngineName();
    QString getName();
    int getPlayers();

private:
    QString engineName;
    QString name;
    int players;

};

#endif // GAMEMODEENTRY_H
