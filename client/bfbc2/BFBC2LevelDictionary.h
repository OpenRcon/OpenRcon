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

#ifndef BFBC2LEVELDICTIONARY_H
#define BFBC2LEVELDICTIONARY_H

#include "LevelDictionary.h"
#include "BFBC2LevelEntry.h"

typedef LevelDictionary<1, TeamEntry, BFBC2LevelEntry, GameModeEntry> BFBC2LevelDictionary;

template<> QList<TeamEntry> BFBC2LevelDictionary::teamList;
template<> QList<BFBC2LevelEntry> BFBC2LevelDictionary::levelList;
template<> QList<GameModeEntry> BFBC2LevelDictionary::gameModeList;
template<> QMultiHash<int, int> BFBC2LevelDictionary::levelMap;

#endif // BFBC2LEVELDICTIONARY_H
