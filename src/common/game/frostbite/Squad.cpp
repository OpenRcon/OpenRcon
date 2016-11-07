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
#include "FrostbiteUtils.h"

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
    QString squadNameCamelCase = FrostbiteUtils::toCamelCase(squadName);
    SquadEnum squad = SquadEnum::None;

    if (squadNameCamelCase == "None") {
        squad = SquadEnum::None;
    } else if (squadNameCamelCase == "Alpha") {
        squad = SquadEnum::Alpha;
    } else if (squadNameCamelCase == "Bravo") {
        squad = SquadEnum::Bravo;
    } else if (squadNameCamelCase == "Charlie") {
        squad = SquadEnum::Charlie;
    } else if (squadNameCamelCase == "Delta") {
        squad = SquadEnum::Delta;
    } else if (squadNameCamelCase == "Echo") {
        squad = SquadEnum::Echo;
    } else if (squadNameCamelCase == "Foxtrot") {
        squad = SquadEnum::Foxtrot;
    } else if (squadNameCamelCase == "Golf") {
        squad = SquadEnum::Golf;
    } else if (squadNameCamelCase == "Hotel") {
        squad = SquadEnum::Hotel;
    } else if (squadNameCamelCase == "India") {
        squad = SquadEnum::India;
    } else if (squadNameCamelCase == "Juliet") {
        squad = SquadEnum::Juliet;
    } else if (squadNameCamelCase == "Kilo") {
        squad = SquadEnum::Kilo;
    } else if (squadNameCamelCase == "Lima") {
        squad = SquadEnum::Lima;
    } else if (squadNameCamelCase == "Mike") {
        squad = SquadEnum::Mike;
    } else if (squadNameCamelCase == "November") {
        squad = SquadEnum::November;
    } else if (squadNameCamelCase == "Oscar") {
        squad = SquadEnum::Oscar;
    } else if (squadNameCamelCase == "Papa") {
        squad = SquadEnum::Papa;
    } else if (squadNameCamelCase == "Quebec") {
        squad = SquadEnum::Quebec;
    } else if (squadNameCamelCase == "Romeo") {
        squad = SquadEnum::Romeo;
    } else if (squadNameCamelCase == "Sierra") {
        squad = SquadEnum::Sierra;
    } else if (squadNameCamelCase == "Tango") {
        squad = SquadEnum::Tango;
    } else if (squadNameCamelCase == "Uniform") {
        squad = SquadEnum::Uniform;
    } else if (squadNameCamelCase == "Victor") {
        squad = SquadEnum::Victor;
    } else if (squadNameCamelCase == "Whiskey") {
        squad = SquadEnum::Whiskey;
    } else if (squadNameCamelCase == "Xray") {
        squad = SquadEnum::Xray;
    } else if (squadNameCamelCase == "Yankee") {
        squad = SquadEnum::Yankee;
    } else if (squadNameCamelCase == "Zulu") {
        squad = SquadEnum::Zulu;
    } else if (squadNameCamelCase == "Haggard") {
        squad = SquadEnum::Haggard;
    } else if (squadNameCamelCase == "Sweetwater") {
        squad = SquadEnum::Sweetwater;
    } else if (squadNameCamelCase == "Preston") {
        squad = SquadEnum::Preston;
    } else if (squadNameCamelCase == "Redford") {
        squad = SquadEnum::Redford;
    } else if (squadNameCamelCase == "Faith") {
        squad = SquadEnum::Faith;
    } else if (squadNameCamelCase == "Celeste") {
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
