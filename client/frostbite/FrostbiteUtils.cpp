/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#include <QApplication>

#include "FrostbiteUtils.h"
#include "Time.h"

int FrostbiteUtils::toInt(const QString &value)
{
    return value.toInt();
}

bool FrostbiteUtils::toBool(const QString &value)
{
    return value == "true";
}

QString FrostbiteUtils::toString(bool value)
{
    return value ? "true" : "false";
}

Time FrostbiteUtils::getTimeFromSeconds(int elapsedSeconds)
{
    int days = elapsedSeconds / 60 / 60 / 24;
    int hours = (elapsedSeconds / 60 / 60) % 24;
    int minutes = (elapsedSeconds / 60) % 60;
    int seconds = elapsedSeconds % 60;

    return Time(days, hours, minutes, seconds);
}

QString FrostbiteUtils::toString(Time time)
{
    QString timeString;

    if (time.days != 0) {
        timeString += " " + QApplication::tr("%1d").arg(time.days);
    }

    if (time.hours != 0) {
        timeString += " " + QApplication::tr("%1h").arg(time.hours);
    }

    if (time.minutes != 0) {
        timeString += " " + QApplication::tr("%1m").arg(time.minutes);
    }

    if (time.seconds != 0) {
        timeString += " " + QApplication::tr("%1s").arg(time.seconds);
    }

    return timeString;
}

QString FrostbiteUtils::getSquadName(Squad squad)
{
    switch (squad) {
    case Squad::Alpha:
        return "Alpha";
        break;

    case Squad::Bravo:
        return "Bravo";
        break;

    case Squad::Charlie:
        return "Charlie";
        break;

    case Squad::Delta:
        return "Delta";
        break;

    case Squad::Echo:
        return "Echo";
        break;

    case Squad::Foxtrot:
        return "Foxtrot";
        break;

    case Squad::Golf:
        return "Golf";
        break;

    case Squad::Hotel:
        return "Hotel";
        break;

    case Squad::India:
        return "India";
        break;

    case Squad::Juliet:
        return "Juliet";
        break;

    case Squad::Kilo:
        return "Kilo";
        break;

    case Squad::Lima:
        return "Lima";
        break;

    case Squad::Mike:
        return "Mike";
        break;

    case Squad::November:
        return "November";
        break;

    case Squad::Oscar:
        return "Oscar";
        break;

    case Squad::Papa:
        return "Papa";
        break;

    case Squad::Quebec:
        return "Quebec";
        break;

    case Squad::Romeo:
        return "Romeo";
        break;

    case Squad::Sierra:
        return "Sierra";
        break;

    case Squad::Tango:
        return "Tango";
        break;

    case Squad::Uniform:
        return "Uniform";
        break;

    case Squad::Victor:
        return "Victor";
        break;

    case Squad::Whiskey:
        return "Whiskey";
        break;

    case Squad::Xray:
        return "X-Ray";
        break;

    case Squad::Yankee:
        return "Yankee";
        break;

    case Squad::Zulu:
        return "Zulu";
        break;

    case Squad::Haggard:
        return "Haggard";
        break;

    case Squad::Sweetwater:
        return "Sweetwater";
        break;

    case Squad::Preston:
        return "Preston";
        break;

    case Squad::Redford:
        return "Redford";
        break;

    case Squad::Faith:
        return "Faith";
        break;

    case Squad::Celeste:
        return "Celeste";
        break;

    default:
        return "None";
    }
}

QString FrostbiteUtils::getSquadName(int squadId)
{
    return getSquadName(static_cast<Squad>(squadId));
}
