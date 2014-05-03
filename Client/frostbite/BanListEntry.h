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

#ifndef BANLISTENTRY_H
#define BANLISTENTRY_H

#include <QString>

struct BanListEntry {
    BanListEntry(const QString &idType,
                 const QString &id,
                 const QString &banType,
                 const int &seconds,
                 const int &rounds,
                 const QString &reason) :
        idType(idType),
        id(id),
        banType(banType),
        seconds(seconds),
        rounds(rounds),
        reason(reason)
    {

    }

    QString idType;
    QString id;
    QString banType;
    int seconds;
    int rounds;
    QString reason;

};

#endif // BANLISTENTRY_H
