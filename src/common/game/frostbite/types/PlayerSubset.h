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

#ifndef PLAYERSUBSET_H
#define PLAYERSUBSET_H

#include <QMetaType>

class QString;
template<class T>
class QList;
class QStringList;

enum class PlayerSubsetEnum {
    All,
    Team,
    Squad,
    Player,
    Unknown
};

class PlayerSubset
{
public:
    static PlayerSubsetEnum fromString(const QString &playerSubsetName);
    static QString toString(const PlayerSubsetEnum &playerSubset);
    static PlayerSubsetEnum fromInt(int playuerSubsetId);
    static int toInt(const PlayerSubsetEnum &playerSubset);
    static QList<PlayerSubsetEnum> asList();
    static QStringList asStringList();

private:
    static QList<PlayerSubsetEnum> list;
    static QStringList stringList;

};

// For use with QVariant
Q_DECLARE_METATYPE(PlayerSubsetEnum)

#endif // PLAYERSUBSET_H
