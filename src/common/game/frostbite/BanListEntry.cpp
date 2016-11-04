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

#include "BanListEntry.h"

BanListEntry::BanListEntry(const BanIdTypeEnum &idType,
                           const QString &id,
                           const BanTypeEnum &type,
                           int seconds,
                           int rounds,
                           const QString &reason) :
    idType(idType),
    id(id),
    type(type),
    seconds(seconds),
    rounds(rounds),
    reason(reason)
{

}

BanListEntry::~BanListEntry()
{

}

BanIdTypeEnum BanListEntry::getIdType()
{
    return idType;
}

QString BanListEntry::getId()
{
    return id;
}

BanTypeEnum BanListEntry::getType()
{
    return type;
}

int BanListEntry::getSeconds()
{
    return seconds;
}

int BanListEntry::getRounds()
{
    return rounds;
}

QString BanListEntry::getReason()
{
    return reason;
}
