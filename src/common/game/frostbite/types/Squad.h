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

#ifndef SQUAD_H
#define SQUAD_H

#include <QMetaType>

class QString;
class QStringList;

enum class SquadEnum {
    None,
    Alpha,
    Bravo,
    Charlie,
    Delta,
    Echo,
    Foxtrot,
    Golf,
    Hotel,
    India,
    Juliet,
    Kilo,
    Lima,
    Mike,
    November,
    Oscar,
    Papa,
    Quebec,
    Romeo,
    Sierra,
    Tango,
    Uniform,
    Victor,
    Whiskey,
    Xray,
    Yankee,
    Zulu,
    Haggard,
    Sweetwater,
    Preston,
    Redford,
    Faith,
    Celeste
};

class Squad
{
public:
    static SquadEnum fromString(const QString &squadName);
    static QString toString(const SquadEnum &squad);
    static QString toString(int squadId);
    static SquadEnum fromInt(int squadId);
    static int toInt(const SquadEnum &squad);
    static QStringList asList();

private:
    static QStringList list;

};

// For use with QVariant
Q_DECLARE_METATYPE(SquadEnum)

#endif // SQUAD_H
