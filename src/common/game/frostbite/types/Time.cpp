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
        timeString += (weeks > 1 ? QObject::tr("%1 Weeks").arg(weeks) : QObject::tr("%1 Week").arg(weeks)) + " ";
    }

    if (days != 0) {
        timeString += (days > 1 ? QObject::tr("%1 Days").arg(days) : QObject::tr("%1 Day").arg(days)) + " ";
    }

    if (hours != 0) {
        timeString += (hours > 1 ? QObject::tr("%1 Hours").arg(hours) : QObject::tr("%1 Hour").arg(hours)) + " ";;
    }

    if (minutes != 0) {
        timeString += (minutes > 1 ? QObject::tr("%1 Minutes").arg(minutes) : QObject::tr("%1 Minute").arg(minutes)) + " ";;
    }

    if (seconds != 0) {
        timeString += (seconds > 1 ? QObject::tr("%1 Seconds").arg(seconds) : QObject::tr("%1 Second").arg(seconds)) + " ";;
    }

    return timeString;
}

QString Time::toShortString() const
{
    QString timeString;

    if (weeks != 0) {
        timeString += QObject::tr("%1w").arg(weeks) + " ";;
    }

    if (days != 0) {
        timeString += QObject::tr("%1d").arg(days) + " ";;
    }

    if (hours != 0) {
        timeString += QObject::tr("%1h").arg(hours) + " ";;
    }

    if (minutes != 0) {
        timeString += QObject::tr("%1m").arg(minutes) + " ";;
    }

    if (seconds != 0) {
        timeString += QObject::tr("%1s").arg(seconds) + " ";;
    }

    return timeString;
}
