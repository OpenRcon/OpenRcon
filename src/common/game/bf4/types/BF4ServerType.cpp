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

#include <QStringList>
#include <QString>

#include "BF4ServerType.h"

#include "FrostbiteUtils.h"

QStringList BF4ServerType::list = {
    "Official",
    "Ranked",
    "Unranked",
    "Private",
    "Unknown"
};

BF4ServerTypeEnum BF4ServerType::fromString(const QString &serverTypeName)
{
    QString serverTypeNameCamelCase = FrostbiteUtils::toCamelCase(serverTypeName);
    BF4ServerTypeEnum serverType = BF4ServerTypeEnum::Unknown;

    if (serverTypeNameCamelCase == "Official") {
        serverType = BF4ServerTypeEnum::Official;
    } else if (serverTypeNameCamelCase == "Ranked") {
        serverType = BF4ServerTypeEnum::Ranked;
    } else if (serverTypeNameCamelCase == "Unranked") {
        serverType = BF4ServerTypeEnum::Unranked;
    } else if (serverTypeNameCamelCase == "Private") {
        serverType = BF4ServerTypeEnum::Private;
    }

    return serverType;
}

QString BF4ServerType::toString(const BF4ServerTypeEnum &serverType)
{
    return list.at(toInt(serverType));
}

BF4ServerTypeEnum BF4ServerType::fromInt(int serverTypeId)
{
    return static_cast<BF4ServerTypeEnum>(serverTypeId);
}

int BF4ServerType::toInt(const BF4ServerTypeEnum &serverType)
{
    return static_cast<int>(serverType);
}

QStringList BF4ServerType::asList()
{
    return list;
}
