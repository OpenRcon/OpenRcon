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

#ifndef BF4PLAYERENTRY_H
#define BF4PLAYERENTRY_H

#include "Frostbite2PlayerEntry.h"

class BF4PlayerEntry : public Frostbite2PlayerEntry
{
public:
    BF4PlayerEntry(const QString &name,
                   const QString &guid,
                   int teamId,
                   int squadId,
                   int kills,
                   int deaths,
                   int score,
                   int rank,
                   int ping,
                   int type);
    ~BF4PlayerEntry();

    int getPing() const;
    int getType() const;

private:
    int ping;
    int type;

};

#endif // BF4PLAYERENTRY_H
