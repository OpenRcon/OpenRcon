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

#ifndef BF4GAMEMODEENTRY_H
#define BF4GAMEMODEENTRY_H

#include "GameModeEntry.h"

class BF4GameModeEntry : public GameModeEntry
{
public:
    BF4GameModeEntry(const QString &engineName, const QString &name, int players, int commanders, int spectators);
    BF4GameModeEntry();
    ~BF4GameModeEntry();

    int getCommanders();
    int getSpectators();

private:
    int commanders;
    int spectators;

};

#endif // BF4GAMEMODEENTRY_H
