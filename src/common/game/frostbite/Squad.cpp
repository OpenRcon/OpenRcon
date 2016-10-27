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

SquadEnum Squad::fromString(const QString &squadName)
{
    SquadEnum squad = SquadEnum::None;

    if (squadName == "None") {
        squad = SquadEnum::None;
    } else if (squadName == "Alpha") {
        squad = SquadEnum::Alpha;
    } else if (squadName == "Bravo") {
        squad = SquadEnum::Bravo;
    } else if (squadName == "Charlie") {
        squad = SquadEnum::Charlie;
    } else if (squadName == "Delta") {
        squad = SquadEnum::Delta;
    } else if (squadName == "Echo") {
        squad = SquadEnum::Echo;
    } else if (squadName == "Foxtrot") {
        squad = SquadEnum::Foxtrot;
    } else if (squadName == "Golf") {
        squad = SquadEnum::Golf;
    } else if (squadName == "Hotel") {
        squad = SquadEnum::Hotel;
    } else if (squadName == "India") {
        squad = SquadEnum::India;
    } else if (squadName == "Juliet") {
        squad = SquadEnum::Juliet;
    } else if (squadName == "Kilo") {
        squad = SquadEnum::Kilo;
    } else if (squadName == "Lima") {
        squad = SquadEnum::Lima;
    } else if (squadName == "Mike") {
        squad = SquadEnum::Mike;
    } else if (squadName == "November") {
        squad = SquadEnum::November;
    } else if (squadName == "Oscar") {
        squad = SquadEnum::Oscar;
    } else if (squadName == "Papa") {
        squad = SquadEnum::Papa;
    } else if (squadName == "Quebec") {
        squad = SquadEnum::Quebec;
    } else if (squadName == "Romeo") {
        squad = SquadEnum::Romeo;
    } else if (squadName == "Sierra") {
        squad = SquadEnum::Sierra;
    } else if (squadName == "Tango") {
        squad = SquadEnum::Tango;
    } else if (squadName == "Uniform") {
        squad = SquadEnum::Uniform;
    } else if (squadName == "Victor") {
        squad = SquadEnum::Victor;
    } else if (squadName == "Whiskey") {
        squad = SquadEnum::Whiskey;
    } else if (squadName == "Xray") {
        squad = SquadEnum::Xray;
    } else if (squadName == "Yankee") {
        squad = SquadEnum::Yankee;
    } else if (squadName == "Zulu") {
        squad = SquadEnum::Zulu;
    } else if (squadName == "Haggard") {
        squad = SquadEnum::Haggard;
    } else if (squadName == "Sweetwater") {
        squad = SquadEnum::Sweetwater;
    } else if (squadName == "Preston") {
        squad = SquadEnum::Preston;
    } else if (squadName == "Redford") {
        squad = SquadEnum::Redford;
    } else if (squadName == "Faith") {
        squad = SquadEnum::Faith;
    } else if (squadName == "Celeste") {
        squad = SquadEnum::Celeste;
    }

    return squad;
}

QString Squad::toString(const SquadEnum &squad)
{
    return list.at(static_cast<int>(squad));
}

QStringList Squad::asList()
{
    return list;
}

