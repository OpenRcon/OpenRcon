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

#include "BanIdType.h"
#include "FrostbiteUtils.h"

QStringList BanIdType::list = {
    "Name",
    "IP",
    "GUID"
};

BanIdTypeEnum BanIdType::fromString(const QString &banIdTypeString)
{
    QString banIdTypeStringCamelCase = FrostbiteUtils::toCamelCase(banIdTypeString);
    BanIdTypeEnum banIdType = BanIdTypeEnum::Name;

    if (banIdTypeStringCamelCase == "Name") {
        banIdType = BanIdTypeEnum::Name;
    } else if (banIdTypeStringCamelCase == "IP") {
        banIdType = BanIdTypeEnum::IP;
    } else if (banIdTypeStringCamelCase == "GUID") {
        banIdType = BanIdTypeEnum::GUID;
    }

    return banIdType;
}

QString BanIdType::toString(const BanIdTypeEnum &banIdType)
{
    return list.at(toInt(banIdType));
}

int BanIdType::toInt(const BanIdTypeEnum &banIdType)
{
    return static_cast<int>(banIdType);
}

QStringList BanIdType::asList()
{
    return list;
}
