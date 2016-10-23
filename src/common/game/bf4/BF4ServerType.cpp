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

QStringList BF4Server::list = {
    "Official",
    "Ranked",
    "Unranked",
    "Private"
};

BF4ServerType BF4Server::fromString(const QString &server)
{
    BF4ServerType serverType = BF4ServerType::Official;

    if (server == "Official") {
        serverType = BF4ServerType::Official;
    } else if (server == "Ranked") {
        serverType = BF4ServerType::Ranked;
    } else if (server == "Unranked") {
        serverType = BF4ServerType::Unranked;
    } else if (server == "Private") {
        serverType = BF4ServerType::Private;
    }

    return serverType;
}

QString BF4Server::toString(const BF4ServerType &serverType)
{
    return list.at(static_cast<int>(serverType));
}

int BF4Server::toInt(const BF4ServerType &serverType)
{
    return static_cast<int>(serverType);
}

QStringList BF4Server::asList()
{
    return list;
}
