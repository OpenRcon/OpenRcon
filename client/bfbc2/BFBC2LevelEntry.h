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

#ifndef BFBC2LEVELENTRY_H
#define BFBC2LEVELENTRY_H

#include "LevelEntry.h"
#include "BFBC2Mod.h"

struct BFBC2LevelEntry : public LevelEntry
{
    BFBC2LevelEntry()
    {

    }

    BFBC2LevelEntry(const QString &engineName,
                    const QString &name,
                    const QList<int> &teams,
                    const QString &image,
                    BFBC2Mod mod) :
        LevelEntry(engineName,
                   name,
                   teams,
                   image),
        mod(mod)
    {

    }

    BFBC2Mod mod;

};

#endif // BFBC2LEVELENTRY_H