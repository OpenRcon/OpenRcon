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

#ifndef PLAYERSUBSET_H
#define PLAYERSUBSET_H

#include <QString>
#include <QStringList>

enum class PlayerSubsetType {
    Unknown,
    All,
    Team,
    Squad,
    Player
};

class PlayerSubset
{
public:
    static PlayerSubsetType fromString(const QString &playerSubset);
    static QString toString(const PlayerSubsetType &playerSubsetType);
    static int toInt(const PlayerSubsetType &playerSubsetType);
    static QStringList asList();

private:
    static QStringList list;

};

#endif // PLAYERSUBSET_H
