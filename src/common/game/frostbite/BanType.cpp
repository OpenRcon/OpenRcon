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

#include "BanType.h"
#include "FrostbiteUtils.h"

QStringList BanType::list = {
    "Perm",
    "Rounds",
    "Seconds"
};

BanTypeEnum BanType::fromString(const QString &banTypeString)
{
    QString banTypeStringCamelCase = FrostbiteUtils::toCamelCase(banTypeString);
    BanTypeEnum banType = BanTypeEnum::Perm;

    if (banTypeStringCamelCase == "Perm") {
        banType = BanTypeEnum::Perm;
    } else if (banTypeStringCamelCase == "Rounds") {
        banType = BanTypeEnum::Rounds;
    } else if (banTypeStringCamelCase == "Seconds") {
        banType = BanTypeEnum::Seconds;
    }

    return banType;
}

QString BanType::toString(const BanTypeEnum &banType)
{
    return list.at(toInt(banType));
}

int BanType::toInt(const BanTypeEnum &banType)
{
    return static_cast<int>(banType);
}

QStringList BanType::asList()
{
    return list;
}
