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

#ifndef BFBC2PLAYERENTRY_H
#define BFBC2PLAYERENTRY_H

#include "FrostbitePlayerEntry.h"

class BFBC2PlayerEntry : public FrostbitePlayerEntry
{
public:
    BFBC2PlayerEntry(const QString &name,
                     const QString &guid,
                     int teamId,
                     int squadId,
                     int kills,
                     int deaths,
                     int score,
                     int ping);
    ~BFBC2PlayerEntry();

    int getPing() const;

private:
    int ping;

};

#endif // BFBC2PLAYERENTRY_H
