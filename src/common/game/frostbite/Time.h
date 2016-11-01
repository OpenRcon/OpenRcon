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

#ifndef TIME_H
#define TIME_H

class Time
{
public:
    Time(int weeks, int days, int hours, int minutes, int seconds);
    ~Time();

    int getWeeks() const;
    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;

private:
    int weeks;
    int days;
    int hours;
    int minutes;
    int seconds;

};

#endif // TIME_H
