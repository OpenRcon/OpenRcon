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

#ifndef BF3LEVELDICTIONARY_H
#define BF3LEVELDICTIONARY_H

#include "LevelDictionary.h"

typedef LevelDictionary<2, TeamEntry, LevelEntry, GameModeEntry> BF3LevelDictionary;

template<> QList<TeamEntry> BF3LevelDictionary::teamList;
template<> QString BF3LevelDictionary::imagePath;
template<> QList<LevelEntry> BF3LevelDictionary::levelList;
template<> QList<GameModeEntry> BF3LevelDictionary::gameModeList;
template<> QMultiHash<int, int> BF3LevelDictionary::levelMap;

#endif // BF3LEVELDICTIONARY_H
