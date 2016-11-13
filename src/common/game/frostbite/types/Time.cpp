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

#include <QObject>
#include <QString>

#include "Time.h"

Time::Time(int weeks, int days, int hours, int minutes, int seconds) :
    weeks(weeks),
    days(days),
    hours(hours),
    minutes(minutes),
    seconds(seconds)
{

}

Time::~Time()
{

}

int Time::getWeeks() const
{
    return weeks;
}

int Time::getDays() const
{
    return days;
}

int Time::getHours() const
{
    return hours;
}

int Time::getMinutes() const
{
    return minutes;
}

int Time::getSeconds() const
{
    return seconds;
}

Time Time::fromSeconds(int elapsedSeconds)
{
    int weeks = elapsedSeconds / 60 / 60 / 24 / 7;
    int days = (elapsedSeconds / 60 / 60 / 24) % 7;
    int hours = (elapsedSeconds / 60 / 60) % 24;
    int minutes = (elapsedSeconds / 60) % 60;
    int seconds =  elapsedSeconds % 60;

    return Time(weeks, days, hours, minutes, seconds);
}

QString Time::toString() const
{
    QString timeString;

    if (weeks != 0) {
        timeString += weeks + " " + (weeks > 1 ? QObject::tr("Weeks") : QObject::tr("Week")) + " ";
    }

    if (days != 0) {
        timeString += days + " " + (days > 1 ? QObject::tr("Days") : QObject::tr("Day")) + " ";
    }

    if (hours != 0) {
        timeString += hours + " " + (hours > 1 ? QObject::tr("Hours") : QObject::tr("Hour")) + " ";
    }

    if (minutes != 0) {
        timeString += minutes + " " + (minutes > 1 ? QObject::tr("Minutes") : QObject::tr("Minute")) + " ";
    }

    if (seconds != 0) {
        timeString += seconds + " " + (seconds > 1 ? QObject::tr("Seconds") : QObject::tr("Second")) + " ";
    }

    return timeString;
}

QString Time::toShortString() const
{
    QString timeString;

    if (weeks != 0) {
        timeString += QString::number(weeks) + QObject::tr("w") + " ";
    }

    if (days != 0) {
        timeString += QString::number(days) + QObject::tr("d") + " ";
    }

    if (hours != 0) {
        timeString += QString::number(hours) + QObject::tr("h") + " ";
    }

    if (minutes != 0) {
        timeString += QString::number(minutes) + QObject::tr("m") + " ";
    }

    if (seconds != 0) {
        timeString += QString::number(seconds) + QObject::tr("s") + " ";
    }

    return timeString;
}
