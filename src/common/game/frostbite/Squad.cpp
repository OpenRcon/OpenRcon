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

#include <QString>
#include <QStringList>

#include "Squad.h"

QStringList Squad::list = {
    "None",
    "Alpha",
    "Bravo",
    "Charlie",
    "Delta",
    "Echo",
    "Foxtrot",
    "Golf",
    "Hotel",
    "India",
    "Juliet",
    "Kilo",
    "Lima",
    "Mike",
    "November",
    "Oscar",
    "Papa",
    "Quebec",
    "Romeo",
    "Sierra",
    "Tango",
    "Uniform",
    "Victor",
    "Whiskey",
    "Xray",
    "Yankee",
    "Zulu",
    "Haggard",
    "Sweetwater",
    "Preston",
    "Redford",
    "Faith",
    "Celeste"
};

EnumSquad Squad::fromString(const QString &squadName)
{
    EnumSquad squad = EnumSquad::None;

    if (squadName == "None") {
        squad = EnumSquad::None;
    } else if (squadName == "Alpha") {
        squad = EnumSquad::Alpha;
    } else if (squadName == "Bravo") {
        squad = EnumSquad::Bravo;
    } else if (squadName == "Charlie") {
        squad = EnumSquad::Charlie;
    } else if (squadName == "Delta") {
        squad = EnumSquad::Delta;
    } else if (squadName == "Echo") {
        squad = EnumSquad::Echo;
    } else if (squadName == "Foxtrot") {
        squad = EnumSquad::Foxtrot;
    } else if (squadName == "Golf") {
        squad = EnumSquad::Golf;
    } else if (squadName == "Hotel") {
        squad = EnumSquad::Hotel;
    } else if (squadName == "India") {
        squad = EnumSquad::India;
    } else if (squadName == "Juliet") {
        squad = EnumSquad::Juliet;
    } else if (squadName == "Kilo") {
        squad = EnumSquad::Kilo;
    } else if (squadName == "Lima") {
        squad = EnumSquad::Lima;
    } else if (squadName == "Mike") {
        squad = EnumSquad::Mike;
    } else if (squadName == "November") {
        squad = EnumSquad::November;
    } else if (squadName == "Oscar") {
        squad = EnumSquad::Oscar;
    } else if (squadName == "Papa") {
        squad = EnumSquad::Papa;
    } else if (squadName == "Quebec") {
        squad = EnumSquad::Quebec;
    } else if (squadName == "Romeo") {
        squad = EnumSquad::Romeo;
    } else if (squadName == "Sierra") {
        squad = EnumSquad::Sierra;
    } else if (squadName == "Tango") {
        squad = EnumSquad::Tango;
    } else if (squadName == "Uniform") {
        squad = EnumSquad::Uniform;
    } else if (squadName == "Victor") {
        squad = EnumSquad::Victor;
    } else if (squadName == "Whiskey") {
        squad = EnumSquad::Whiskey;
    } else if (squadName == "Xray") {
        squad = EnumSquad::Xray;
    } else if (squadName == "Yankee") {
        squad = EnumSquad::Yankee;
    } else if (squadName == "Zulu") {
        squad = EnumSquad::Zulu;
    } else if (squadName == "Haggard") {
        squad = EnumSquad::Haggard;
    } else if (squadName == "Sweetwater") {
        squad = EnumSquad::Sweetwater;
    } else if (squadName == "Preston") {
        squad = EnumSquad::Preston;
    } else if (squadName == "Redford") {
        squad = EnumSquad::Redford;
    } else if (squadName == "Faith") {
        squad = EnumSquad::Faith;
    } else if (squadName == "Celeste") {
        squad = EnumSquad::Celeste;
    }

    return squad;
}

QString Squad::toString(const EnumSquad &squad)
{
    return list.at(static_cast<int>(squad));
}

QStringList Squad::asList()
{
    return list;
}

