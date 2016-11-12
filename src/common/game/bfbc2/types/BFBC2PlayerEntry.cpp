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

#include "BFBC2PlayerEntry.h"

BFBC2PlayerEntry::BFBC2PlayerEntry(const QString &name,
                                   const QString &guid,
                                   int teamId,
                                   int squadId,
                                   int kills,
                                   int deaths,
                                   int score,
                                   int ping) :
    FrostbitePlayerEntry(name,
                         guid,
                         teamId,
                         squadId,
                         kills,
                         deaths,
                         score),
    ping(ping)
{

}

BFBC2PlayerEntry::~BFBC2PlayerEntry()
{

}

int BFBC2PlayerEntry::getPing() const
{
    return ping;
}
